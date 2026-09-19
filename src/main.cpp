// ============================================================================
//  FuckMSIME-CHS-Bing-Suggestion — pins Microsoft Pinyin (CHS IME) cloud
//  suggestion settings OFF for every user on the machine.
//
//  Background: on Windows 11, TextInputHost.exe (Windows Input Experience)
//  writes HKCU\Software\Microsoft\InputMethod\Settings\CHS values
//  "Enable Cloud Candidate" and "AutoShowCloudSuggestion" back to 1 whenever
//  its promotion popup fires (verified via 4657 registry auditing).
//
//  The service watches every loaded user hive under HKEY_USERS and reverts
//  those two values to 0 the moment they change (RegNotifyChangeKeyValue,
//  kernel-pushed notifications, ~zero cost). Runs as SYSTEM, auto start,
//  so the pin applies to ALL users.
//
//  Usage:
//    (double-click)             graphical install / upgrade / uninstall wizard
//    ... install                install into Program Files, register + start
//    ... uninstall              stop and remove the service
//    ... debug                  console debug run
//    (SCM starts the binary)    runs the watchdog service
//
//  The binary embeds a requireAdministrator manifest: double-click always
//  goes through UAC. When SCM launches the same binary as a service the
//  manifest is ignored (services run under their configured account).
// ============================================================================

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <commctrl.h>
#include <shlobj.h>

#include <cstdio>
#include <cwchar>
#include <memory>
#include <string>
#include <vector>

#include "strings.h"

#pragma comment(lib, "advapi32.lib")
#pragma comment(lib, "comctl32.lib")
#pragma comment(lib, "shell32.lib")
#pragma comment(lib, "user32.lib")

namespace {

constexpr wchar_t kServiceName[] = L"FuckMSIME-CHS-Bing-Suggestion";
constexpr wchar_t kServiceDesc[] =
    L"Pins Microsoft Pinyin cloud-suggestion settings to OFF for every user, "
    L"reverting writes made by TextInputHost.exe.";
constexpr wchar_t kChsPath[] = L"Software\\Microsoft\\InputMethod\\Settings\\CHS";
constexpr wchar_t kValCloud[] = L"Enable Cloud Candidate";
constexpr wchar_t kValAuto[] = L"AutoShowCloudSuggestion";
constexpr wchar_t kLogDir[] = L"C:\\ProgramData\\FuckMSIME-CHS-Bing-Suggestion";
constexpr wchar_t kLogFile[] =
    L"C:\\ProgramData\\FuckMSIME-CHS-Bing-Suggestion\\FuckMSIME-CHS-Bing-Suggestion.log";

constexpr DWORD kRescanMs = 5000;   // picks up hives loading at logon
constexpr DWORD kMaxWfmo = 60;      // WaitForMultipleObjects practical cap
constexpr UINT kIdUpgrade = 1001;   // task-dialog button ids
constexpr UINT kIdUninstall = 1002;

SERVICE_STATUS g_status = {};
SERVICE_STATUS_HANDLE g_statusHandle = nullptr;
HANDLE g_stopEvent = nullptr;

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

    OutputDebugStringW((std::wstring(L"[FuckMSIME] ") + msg).c_str());

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

// ------------------------------------------------------------- watchdog ----

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
        // Watches that didn't fit into the WFMO wait set are polled below on
        // every rescan tick, so their worst-case latency degrades to
        // kRescanMs instead of staying "armed but never waited on" (matters
        // on RDS / terminal hosts with more users than the wait-set cap).
        const size_t polledFrom = handles.size() - 1;

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
        } else if (wait == WAIT_TIMEOUT) {
            for (size_t i = polledFrom; i < g_watches.size(); ++i)
                EnforceKey(g_watches[i].key, g_watches[i].sid.c_str());
        }
        // otherwise: loop back to ScanHives() (catches logon/logoff)
    }
}

// ------------------------------------------------------- service plumbing --

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

// ------------------------------------------------- install / uninstall core --

std::wstring SelfPath() {
    wchar_t buf[MAX_PATH];
    GetModuleFileNameW(nullptr, buf, MAX_PATH);
    return buf;
}

std::wstring InstallDir() {
    wchar_t prog[MAX_PATH];
    if (SUCCEEDED(SHGetFolderPathW(nullptr, CSIDL_PROGRAM_FILES, nullptr,
                                   SHGFP_TYPE_CURRENT, prog)))
        return std::wstring(prog) + L"\\" + kServiceName;
    return std::wstring(L"C:\\Program Files\\") + kServiceName;
}

std::wstring InstallTarget() {
    return InstallDir() + L"\\" + kServiceName + L".exe";
}

// Extract the executable path from a service ImagePath, tolerating
// arguments, unquoted "Program Files" paths, and damaged quoting.
// Mirrors how the SCM itself resolves unquoted ambiguity: try successively
// longer space-joined prefixes and keep the longest one ending in ".exe".
std::wstring ExtractImageApp(const wchar_t* raw) {
    std::wstring p = raw ? raw : L"";
    const size_t s = p.find_first_not_of(L" \t");
    if (s == std::wstring::npos) return L"";
    p = p.substr(s);

    if (p.front() == L'"') {
        const size_t close = p.find(L'"', 1);
        if (close == std::wstring::npos) return p.substr(1);   // damaged: unterminated
        return p.substr(1, close - 1);                         // args after " ignored
    }

    std::wstring best;
    for (size_t start = 0;;) {
        const size_t sp = p.find(L' ', start);
        const std::wstring cand =
            p.substr(0, sp == std::wstring::npos ? p.size() : sp);
        if (cand.size() >= 4 &&
            _wcsicmp(cand.c_str() + cand.size() - 4, L".exe") == 0)
            best = cand;
        if (sp == std::wstring::npos) break;
        start = sp + 1;
    }
    if (!best.empty()) return best;
    const size_t sp = p.find(L' ');   // fallback: first whitespace token
    return sp == std::wstring::npos ? p : p.substr(0, sp);
}

// If the service exists, fetch the executable its ImagePath points at.
bool GetServiceBinary(std::wstring* path) {
    SC_HANDLE scm = OpenSCManagerW(nullptr, nullptr,
                                   SERVICE_QUERY_STATUS | SERVICE_QUERY_CONFIG);
    if (!scm) return false;
    SC_HANDLE svc = OpenServiceW(scm, kServiceName, SERVICE_QUERY_CONFIG);
    if (!svc) { CloseServiceHandle(scm); return false; }

    bool ok = false;
    DWORD need = 0;
    QueryServiceConfigW(svc, nullptr, 0, &need);
    if (GetLastError() == ERROR_INSUFFICIENT_BUFFER) {
        auto buf = std::make_unique<BYTE[]>(need);
        auto cfg = reinterpret_cast<QUERY_SERVICE_CONFIGW*>(buf.get());
        if (QueryServiceConfigW(svc, cfg, need, &need)) {
            *path = ExtractImageApp(cfg->lpBinaryPathName);
            ok = true;
        }
    }
    CloseServiceHandle(svc);
    CloseServiceHandle(scm);
    return ok;
}

bool StopSvc() {
    SC_HANDLE scm = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_CONNECT);
    if (!scm) return false;
    SC_HANDLE svc = OpenServiceW(scm, kServiceName,
                                 SERVICE_STOP | SERVICE_QUERY_STATUS);
    if (!svc) { CloseServiceHandle(scm); return true; }   // not there = stopped

    SERVICE_STATUS st = {};
    ControlService(svc, SERVICE_CONTROL_STOP, &st);
    for (int i = 0; i < 50 && QueryServiceStatus(svc, &st) &&
                    st.dwCurrentState != SERVICE_STOPPED; ++i)
        Sleep(200);
    bool stopped = st.dwCurrentState == SERVICE_STOPPED;
    CloseServiceHandle(svc);
    CloseServiceHandle(scm);
    return stopped;
}

bool StartSvc() {
    SC_HANDLE scm = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_CONNECT);
    if (!scm) return false;
    SC_HANDLE svc = OpenServiceW(scm, kServiceName, SERVICE_START);
    bool ok = svc && StartServiceW(svc, 0, nullptr);
    if (svc) CloseServiceHandle(svc);
    CloseServiceHandle(scm);
    return ok;
}

// Copy self into Program Files, register as auto-start service, start it.
DWORD InstallService() {
    const std::wstring target = InstallTarget();
    const std::wstring self = SelfPath();

    if (_wcsicmp(self.c_str(), target.c_str()) != 0) {   // skip if already in place
        CreateDirectoryW(InstallDir().c_str(), nullptr);
        if (!CopyFileW(self.c_str(), target.c_str(), FALSE))
            return GetLastError();
    }

    SC_HANDLE scm = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if (!scm) return GetLastError();

    const std::wstring cmd = L"\"" + target + L"\"";
    SC_HANDLE svc = CreateServiceW(scm, kServiceName, kServiceName,
                                   SERVICE_ALL_ACCESS, SERVICE_WIN32_OWN_PROCESS,
                                   SERVICE_AUTO_START, SERVICE_ERROR_NORMAL,
                                   cmd.c_str(), nullptr, nullptr, nullptr,
                                   nullptr, nullptr);
    if (!svc && GetLastError() == ERROR_SERVICE_EXISTS)
        svc = OpenServiceW(scm, kServiceName,
                           SERVICE_START | SERVICE_CHANGE_CONFIG | SERVICE_STOP);
    if (!svc) {
        DWORD e = GetLastError();
        CloseServiceHandle(scm);
        return e;
    }

    SERVICE_DESCRIPTIONW desc;
    desc.lpDescription = const_cast<wchar_t*>(kServiceDesc);
    ChangeServiceConfig2W(svc, SERVICE_CONFIG_DESCRIPTION, &desc);

    bool started = StartServiceW(svc, 0, nullptr);
    DWORD err = started ? ERROR_SUCCESS : GetLastError();
    CloseServiceHandle(svc);
    CloseServiceHandle(scm);

    if (started) Log(L"service installed at %s", target.c_str());
    return err;
}

// Stop (if running) and delete the service.
DWORD RemoveService() {
    SC_HANDLE scm = OpenSCManagerW(nullptr, nullptr, SC_MANAGER_ALL_ACCESS);
    if (!scm) return GetLastError();
    SC_HANDLE svc = OpenServiceW(scm, kServiceName,
                                 SERVICE_STOP | DELETE | SERVICE_QUERY_STATUS);
    if (!svc) {
        DWORD e = GetLastError();
        CloseServiceHandle(scm);
        return e == ERROR_SERVICE_DOES_NOT_EXIST ? ERROR_SUCCESS : e;
    }

    SERVICE_STATUS st = {};
    ControlService(svc, SERVICE_CONTROL_STOP, &st);
    for (int i = 0; i < 50 && QueryServiceStatus(svc, &st) &&
                    st.dwCurrentState != SERVICE_STOPPED; ++i)
        Sleep(200);

    bool deleted = DeleteService(svc);
    DWORD err = deleted ? ERROR_SUCCESS : GetLastError();
    CloseServiceHandle(svc);
    CloseServiceHandle(scm);
    if (deleted) Log(L"service removed");
    return err;
}

// -------------------------------------------------------- interactive GUI --

void InfoBox(const wchar_t* text, UINT icon) {
    MessageBoxW(nullptr, text, L(STR_APP_NAME), MB_OK | icon);
}

void FailBox(DWORD err) {
    wchar_t msg[512];
    _snwprintf_s(msg, _countof(msg), _TRUNCATE, L(STR_UI_OP_FAILED_FMT), err);
    InfoBox(msg, MB_ICONERROR);
}

// Returns kIdUpgrade / kIdUninstall / IDCANCEL.
int AskUpgradeOrRemove() {
    TASKDIALOG_BUTTON buttons[3] = {
        { kIdUpgrade,   L(STR_UI_BTN_UPGRADE) },
        { kIdUninstall, L(STR_UI_BTN_UNINSTALL) },
        { IDCANCEL,     L(STR_UI_BTN_CANCEL) },
    };
    TASKDIALOGCONFIG cfg = {};
    cfg.cbSize = sizeof(cfg);
    cfg.dwFlags = TDF_USE_COMMAND_LINKS;
    cfg.pszWindowTitle = L(STR_APP_NAME);
    cfg.pszMainInstruction = L(STR_UI_FOUND_INSTALLED);
    cfg.pszContent = L(STR_UI_UPGRADE_OR_REMOVE);
    cfg.pButtons = buttons;
    cfg.cButtons = 3;
    int sel = 0;
    if (SUCCEEDED(TaskDialogIndirect(&cfg, &sel, nullptr, nullptr)) && sel)
        return sel;

    // fallback: stock message box
    int mb = MessageBoxW(nullptr, L(STR_UI_UPGRADE_OR_REMOVE), L(STR_APP_NAME),
                         MB_YESNOCANCEL | MB_ICONQUESTION);
    return mb == IDYES ? kIdUpgrade : mb == IDNO ? kIdUninstall : IDCANCEL;
}

int RunInteractive() {
    std::wstring svcPath;
    if (GetServiceBinary(&svcPath)) {
        int sel = AskUpgradeOrRemove();
        if (sel == kIdUpgrade) {
            StopSvc();
            if (_wcsicmp(SelfPath().c_str(), svcPath.c_str()) != 0 &&
                !CopyFileW(SelfPath().c_str(), svcPath.c_str(), FALSE)) {
                FailBox(GetLastError());
                return 1;
            }
            if (!StartSvc()) { FailBox(GetLastError()); return 1; }
            InfoBox(L(STR_UI_UPGRADE_DONE), MB_ICONINFORMATION);
        } else if (sel == kIdUninstall) {
            DWORD err = RemoveService();
            if (err != ERROR_SUCCESS) { FailBox(err); return 1; }
            InfoBox(L(STR_UI_UNINSTALL_DONE), MB_ICONINFORMATION);
        } else {
            InfoBox(L(STR_UI_CANCELLED), MB_ICONINFORMATION);
        }
        return 0;
    }

    if (MessageBoxW(nullptr, L(STR_UI_INSTALL_CONFIRM), L(STR_APP_NAME),
                    MB_YESNO | MB_ICONQUESTION) != IDYES) {
        InfoBox(L(STR_UI_CANCELLED), MB_ICONINFORMATION);
        return 0;
    }
    DWORD err = InstallService();
    if (err != ERROR_SUCCESS) { FailBox(err); return 1; }
    InfoBox(L(STR_UI_INSTALL_DONE), MB_ICONINFORMATION);
    return 0;
}

// ------------------------------------------------------------ CLI modes --

int CmdInstall() {
    DWORD err = InstallService();
    if (err == ERROR_SERVICE_ALREADY_RUNNING) {
        Log(L"service already installed and running");
        return 0;
    }
    if (err != ERROR_SUCCESS) FailBox(err);
    else Log(L"service installed and started");
    return err != ERROR_SUCCESS ? 1 : 0;
}

int CmdUninstall() {
    DWORD err = RemoveService();
    if (err != ERROR_SUCCESS) FailBox(err);
    else Log(L"service uninstalled");
    return err != ERROR_SUCCESS ? 1 : 0;
}

// ------------------------------------------------------------------- main --

}  // namespace

int wmain(int argc, wchar_t** argv) {
    if (argc >= 2 && wcscmp(argv[1], L"install") == 0) return CmdInstall();
    if (argc >= 2 && wcscmp(argv[1], L"uninstall") == 0) return CmdUninstall();

    if (argc >= 2 && wcscmp(argv[1], L"debug") == 0) {
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
        if (GetLastError() == ERROR_FAILED_SERVICE_CONTROLLER_CONNECT)
            return RunInteractive();          // launched by a user double-click
        fwprintf(stderr, L"%s\n", L(STR_USAGE));
        return 1;
    }
    return 0;
}
