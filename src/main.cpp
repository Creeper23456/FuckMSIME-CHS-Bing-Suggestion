// ============================================================================
//  ChsCloudPin — pins Microsoft Pinyin (CHS IME) cloud-suggestion settings OFF
//
//  Background: on Windows 11, TextInputHost.exe (Windows Input Experience)
//  writes HKCU\Software\Microsoft\InputMethod\Settings\CHS values
//  "Enable Cloud Candidate" and "AutoShowCloudSuggestion" back to 1 whenever
//  its promotion popup fires (verified via 4657 registry auditing).
//
//  This service watches every loaded user hive under HKEY_USERS and reverts
//  those two values to 0 the moment they change (RegNotifyChangeKeyValue,
//  kernel-pushed notifications, ~zero cost). Runs as LocalSystem, auto start.
//
//  Usage:
//    ChsCloudPin.exe install    install as auto-start service and start it
//    ChsCloudPin.exe uninstall  stop and remove the service
//    ChsCloudPin.exe debug      run in console for development
//    ChsCloudPin.exe            (default) run as a service via SCM
// ============================================================================

#define WIN32_LEAN_AND_MEAN
#include <windows.h>

#include <cstdio>
#include <cwchar>
#include <string>
#include <vector>

#pragma comment(lib, "advapi32.lib")

namespace {

constexpr wchar_t kServiceName[] = L"ChsCloudPin";
constexpr wchar_t kServiceDisplay[] = L"CHS IME Cloud Suggestion Pin";
constexpr wchar_t kServiceDesc[] =
    L"Pins Microsoft Pinyin cloud-suggestion settings to OFF for every user, "
    L"reverting writes made by TextInputHost.exe.";
constexpr wchar_t kChsPath[] = L"Software\\Microsoft\\InputMethod\\Settings\\CHS";
constexpr wchar_t kValCloud[] = L"Enable Cloud Candidate";
constexpr wchar_t kValAuto[] = L"AutoShowCloudSuggestion";
constexpr wchar_t kLogDir[] = L"C:\\ProgramData\\ChsCloudPin";
constexpr wchar_t kLogFile[] = L"C:\\ProgramData\\ChsCloudPin\\ChsCloudPin.log";

constexpr DWORD kRescanMs = 5000;   // picks up hives loading at logon
constexpr DWORD kMaxWfmo = 60;      // WaitForMultipleObjects practical cap

SERVICE_STATUS g_status = {};
SERVICE_STATUS_HANDLE g_statusHandle = nullptr;
HANDLE g_stopEvent = nullptr;
bool g_debugMode = false;

struct Watch {
    std::wstring sid;
    HKEY key = nullptr;
    HANDLE event = nullptr;
};
std::vector<Watch> g_watches;

// ---------------------------------------------------------------- logging --

void Log(const wchar_t* fmt, ...) {
    wchar_t msg[1024];
    va_list args;
    va_start(args, fmt);
    _vsnwprintf_s(msg, _countof(msg), _TRUNCATE, fmt, args);
    va_end(args);

    OutputDebugStringW((std::wstring(L"[ChsCloudPin] ") + msg).c_str());

    CreateDirectoryW(kLogDir, nullptr);
    FILE* f = nullptr;
    if (_wfopen_s(&f, kLogFile, L"a, ccs=UTF-8") == 0 && f) {
        SYSTEMTIME st;
        GetLocalTime(&st);
        fwprintf(f, L"[%04u-%02u-%02u %02u:%02u:%02u] %s\n",
                 st.wYear, st.wMonth, st.wDay,
                 st.wHour, st.wMinute, st.wSecond, msg);
        fclose(f);
    }
}

// ------------------------------------------------------------- enforcment --

bool IsUserHiveName(const wchar_t* name) {
    if (wcsncmp(name, L"S-1-5-21-", 9) != 0) return false;   // real accounts only
    if (wcsstr(name, L"_Classes")) return false;              // per-hive classes
    return true;
}

// Ensures both pinned values exist and are zero. Returns fixes applied.
int EnforceKey(HKEY hChs, const wchar_t* sid) {
    int fixes = 0;
    const wchar_t* names[2] = { kValCloud, kValAuto };
    for (const wchar_t* name : names) {
        DWORD value = 0, size = sizeof(value), type = 0;
        LONG r = RegQueryValueExW(hChs, name, nullptr, &type,
                                  reinterpret_cast<BYTE*>(&value), &size);
        if (r == ERROR_FILE_NOT_FOUND) {
            value = 0;
            if (RegSetValueExW(hChs, name, 0, REG_DWORD,
                               reinterpret_cast<const BYTE*>(&value),
                               sizeof(value)) == ERROR_SUCCESS) {
                Log(L"[%s] created '%s' = 0", sid, name);
                ++fixes;
            }
        } else if (r == ERROR_SUCCESS && type == REG_DWORD && value != 0) {
            value = 0;
            if (RegSetValueExW(hChs, name, 0, REG_DWORD,
                               reinterpret_cast<const BYTE*>(&value),
                               sizeof(value)) == ERROR_SUCCESS) {
                Log(L"[%s] reverted '%s' 1 -> 0", sid, name);
                ++fixes;
            }
        }
    }
    return fixes;
}

bool ArmNotify(HANDLE event, HKEY key) {
    return RegNotifyChangeKeyValue(key, FALSE, REG_NOTIFY_CHANGE_LAST_SET,
                                   event, TRUE) == ERROR_SUCCESS;
}

// Reconcile the watch table against currently loaded user hives.
void ScanHives() {
    std::vector<std::wstring> hives;
    wchar_t name[256];
    for (DWORD i = 0;; ++i) {
        DWORD len = _countof(name);
        LONG r = RegEnumKeyExW(HKEY_USERS, i, name, &len, nullptr,
                               nullptr, nullptr, nullptr);
        if (r == ERROR_NO_MORE_ITEMS) break;
        if (r != ERROR_SUCCESS) continue;
        if (IsUserHiveName(name)) hives.emplace_back(name);
    }

    // drop watches whose hive/key is gone
    for (auto it = g_watches.begin(); it != g_watches.end();) {
        HKEY probe = nullptr;
        bool alive = RegOpenKeyExW(HKEY_USERS, it->sid.c_str(), 0, KEY_READ,
                                   &probe) == ERROR_SUCCESS;
        if (alive) {
            RegCloseKey(probe);
            HKEY chs = nullptr;
            alive = RegOpenKeyExW(HKEY_USERS,
                                  (it->sid + L"\\" + kChsPath).c_str(), 0,
                                  KEY_READ, &chs) == ERROR_SUCCESS;
            if (alive) RegCloseKey(chs);
        }
        if (alive) { ++it; continue; }
        CloseHandle(it->event);
        RegCloseKey(it->key);
        Log(L"[%s] hive unloaded, watch removed", it->sid.c_str());
        it = g_watches.erase(it);
    }

    // add watches for new hives
    for (const auto& sid : hives) {
        bool known = false;
        for (const auto& w : g_watches)
            if (w.sid == sid) { known = true; break; }
        if (known) continue;

        HKEY hHive = nullptr;
        if (RegOpenKeyExW(HKEY_USERS, sid.c_str(), 0,
                          KEY_READ | KEY_CREATE_SUB_KEY, &hHive) != ERROR_SUCCESS) {
            Log(L"[%s] hive not openable (yet)", sid.c_str());
            continue;
        }
        HKEY hChs = nullptr;
        DWORD disp = 0;
        LONG r = RegCreateKeyExW(hHive, kChsPath, 0, nullptr,
                                 REG_OPTION_NON_VOLATILE,
                                 KEY_READ | KEY_SET_VALUE | KEY_NOTIFY,
                                 nullptr, &hChs, &disp);
        RegCloseKey(hHive);
        if (r != ERROR_SUCCESS) {
            Log(L"[%s] cannot open/create CHS key (err %ld)", sid.c_str(), r);
            continue;
        }

        Watch w;
        w.sid = sid;
        w.key = hChs;
        w.event = CreateEventW(nullptr, FALSE, FALSE, nullptr);
        if (!w.event || !ArmNotify(w.event, hChs)) {
            Log(L"[%s] notify arm failed (err %lu)", sid.c_str(), GetLastError());
            if (w.event) CloseHandle(w.event);
            RegCloseKey(hChs);
            continue;
        }

        EnforceKey(hChs, sid.c_str());
        g_watches.push_back(w);
        Log(L"[%s] watch armed (%s)", sid.c_str(),
            disp == REG_CREATED_NEW_KEY ? L"key created" : L"key exists");
    }
}

// One supervision pass: wait for change notifications / stop / rescan tick.
// Returns when the service should stop.
void SuperviseLoop() {
    for (;;) {
        ScanHives();

        std::vector<HANDLE> handles;
        handles.push_back(g_stopEvent);
        for (const auto& w : g_watches) {
            if (handles.size() >= kMaxWfmo) break;
            handles.push_back(w.event);
        }

        DWORD wait = WaitForMultipleObjects((DWORD)handles.size(),
                                            handles.data(), FALSE, kRescanMs);
        if (wait >= WAIT_OBJECT_0 && wait < WAIT_OBJECT_0 + handles.size()) {
            HANDLE fired = handles[wait - WAIT_OBJECT_0];
            if (fired == g_stopEvent) return;

            for (auto& w : g_watches) {
                if (w.event != fired) continue;
                EnforceKey(w.key, w.sid.c_str());
                ArmNotify(w.event, w.key);   // one-shot: re-arm
                break;
            }
        }
        // timeout path: loop back to ScanHives() (catches logon/logoff)
    }
}

// ------------------------------------------------------------ SCM plumbing --

void WINAPI ServiceMain(DWORD, LPWSTR*) {
    g_statusHandle = RegisterServiceCtrlHandlerW(kServiceName,
                                                 [](DWORD code) {
        if (code == SERVICE_CONTROL_STOP || code == SERVICE_CONTROL_SHUTDOWN) {
            if (g_stopEvent) SetEvent(g_stopEvent);
            g_status.dwCurrentState = SERVICE_STOP_PENDING;
            SetServiceStatus(g_statusHandle, &g_status);
        }
    });
    if (!g_statusHandle) return;

    g_status.dwServiceType = SERVICE_WIN32_OWN_PROCESS;
    g_status.dwCurrentState = SERVICE_START_PENDING;
    g_status.dwControlsAccepted = SERVICE_ACCEPT_STOP | SERVICE_ACCEPT_SHUTDOWN;
    SetServiceStatus(g_statusHandle, &g_status);

    g_stopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
    Log(L"service starting");

    g_status.dwCurrentState = SERVICE_RUNNING;
    SetServiceStatus(g_statusHandle, &g_status);

    SuperviseLoop();

    Log(L"service stopped");
    g_status.dwCurrentState = SERVICE_STOPPED;
    SetServiceStatus(g_statusHandle, &g_status);
}

BOOL WINAPI ConsoleCtrlHandler(DWORD type) {
    if (type == CTRL_C_EVENT || type == CTRL_BREAK_EVENT || type == CTRL_CLOSE_EVENT) {
        if (g_stopEvent) SetEvent(g_stopEvent);
        return TRUE;
    }
    return FALSE;
}

// ---------------------------------------------------------------- install --

std::wstring SelfPath() {
    wchar_t buf[MAX_PATH];
    GetModuleFileNameW(nullptr, buf, MAX_PATH);
    return buf;
}

int CmdInstall() {
    SC_HANDLE scm = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if (!scm) { Log(L"OpenSCManager failed (err %lu) - run elevated", GetLastError()); return 1; }

    const std::wstring path = L"\"" + SelfPath() + L"\"";
    SC_HANDLE svc = CreateServiceW(scm, kServiceName, kServiceDisplay,
                                   SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
                                   SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
                                   path.c_str(), nullptr, nullptr, nullptr,
                                   nullptr, nullptr);
    if (!svc && GetLastError() == ERROR_SERVICE_EXISTS) {
        Log(L"service already installed");
        svc = OpenServiceW(scm, kServiceName, SERVICE_START | SERVICE_CHANGE_CONFIG);
    }
    if (!svc) { Log(L"CreateService failed (err %lu)", GetLastError()); CloseServiceHandle(scm); return 1; }

    SERVICE_DESCRIPTIONW desc;
    desc.lpDescription = const_cast<wchar_t*>(kServiceDesc);
    ChangeServiceConfig2W(svc, SERVICE_CONFIG_DESCRIPTION, &desc);

    if (!StartServiceW(svc, 0, nullptr))
        Log(L"StartService: err %lu (may already be running)", GetLastError());
    else
        Log(L"service installed and started");

    CloseServiceHandle(svc);
    CloseServiceHandle(scm);
    return 0;
}

int CmdUninstall() {
    SC_HANDLE scm = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if (!scm) { Log(L"OpenSCManager failed (err %lu) - run elevated", GetLastError()); return 1; }
    SC_HANDLE svc = OpenServiceW(scm, kServiceName,
                                 SERVICE_STOP | DELETE | SERVICE_QUERY_STATUS);
    if (!svc) { Log(L"service not found"); CloseServiceHandle(scm); return 1; }

    SERVICE_STATUS st = {};
    ControlService(svc, SERVICE_CONTROL_STOP, &st);
    for (int i = 0; i < 20 && QueryServiceStatus(svc, &st) &&
                    st.dwCurrentState != SERVICE_STOPPED; ++i)
        Sleep(200);
    DeleteService(svc);
    Log(L"service uninstalled");
    CloseServiceHandle(svc);
    CloseServiceHandle(scm);
    return 0;
}

// ------------------------------------------------------------------- main --

}  // namespace

int wmain(int argc, wchar_t** argv) {
    if (argc >= 2 && wcscmp(argv[1], L"install") == 0) return CmdInstall();
    if (argc >= 2 && wcscmp(argv[1], L"uninstall") == 0) return CmdUninstall();

    if (argc >= 2 && wcscmp(argv[1], L"debug") == 0) {
        g_debugMode = true;
        SetConsoleCtrlHandler(ConsoleCtrlHandler, TRUE);
        g_stopEvent = CreateEventW(nullptr, TRUE, FALSE, nullptr);
        Log(L"debug run - Ctrl+C to stop");
        SuperviseLoop();
        Log(L"debug run ended");
        return 0;
    }

    SERVICE_TABLE_ENTRYW table[] = {
        { const_cast<wchar_t*>(kServiceName), ServiceMain },
        { nullptr, nullptr },
    };
    if (!StartServiceCtrlDispatcherW(table)) {
        fwprintf(stderr, L"Usage:\n"
                         L"  %s install    install + start service (elevated)\n"
                         L"  %s uninstall  stop + remove service (elevated)\n"
                         L"  %s debug      run in console\n",
                 argv[0], argv[0], argv[0]);
        return 1;
    }
    return 0;
}
