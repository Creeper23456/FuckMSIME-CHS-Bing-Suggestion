// ==WindhawkMod==
// @id              msime-chs-cloud-pin
// @name            MSIME CHS: pin cloud-suggestion settings
// @description     Blocks TextInputHost.exe from re-enabling "Enable Cloud Candidate" / "AutoShowCloudSuggestion" (ntdll-level, case-insensitive); other writes untouched.
// @version         0.2.0
// @author          klp
// @include         C:\Windows\SystemApps\MicrosoftWindows.Client.CBS_cw5n1h2txyewy\TextInputHost.exe
// @architecture    x86-64
// ==/WindhawkMod==

#include <windows.h>

typedef LONG NTSTATUS;

typedef struct _MS_UNI {
    USHORT Length;
    USHORT MaximumLength;
    PWSTR  Buffer;
} MS_UNI;

using RegSetValueExW_t = LONG(WINAPI*)(HKEY, LPCWSTR, DWORD, DWORD, const BYTE*, DWORD);
using RegSetValueExA_t = LONG(WINAPI*)(HKEY, LPCSTR, DWORD, DWORD, const BYTE*, DWORD);
using RegSetKeyValueW_t = LONG(WINAPI*)(HKEY, LPCWSTR, LPCWSTR, DWORD, const BYTE*, DWORD);
using NtSetValueKey_t = NTSTATUS(NTAPI*)(HANDLE, MS_UNI*, ULONG, ULONG, void*, ULONG);

RegSetValueExW_t  RegSetValueExW_Orig  = nullptr;
RegSetValueExA_t  RegSetValueExA_Orig  = nullptr;
RegSetKeyValueW_t RegSetKeyValueW_Orig = nullptr;
NtSetValueKey_t   NtSetValueKey_Orig   = nullptr;

static volatile LONG g_blocked = 0;
static volatile LONG g_logged  = 0;

static bool PinnedW(const wchar_t* name) {
    if (!name) return false;
    return _wcsicmp(name, L"Enable Cloud Candidate") == 0 ||
           _wcsicmp(name, L"AutoShowCloudSuggestion") == 0;
}

static bool PinnedA(const char* name) {
    if (!name) return false;
    return _stricmp(name, "Enable Cloud Candidate") == 0 ||
           _stricmp(name, "AutoShowCloudSuggestion") == 0;
}

static bool PinnedUni(const MS_UNI* u) {
    if (!u || !u->Buffer || u->Length == 0) return false;
    size_t n = u->Length / sizeof(wchar_t);
    if (n == 22 && _wcsnicmp(u->Buffer, L"Enable Cloud Candidate", 22) == 0) return true;
    if (n == 23 && _wcsnicmp(u->Buffer, L"AutoShowCloudSuggestion", 23) == 0) return true;
    return false;
}

LONG WINAPI RegSetValueExW_Hook(HKEY hk, LPCWSTR name, DWORD res, DWORD type, const BYTE* data, DWORD size) {
    if (PinnedW(name)) {
        LONG n = InterlockedIncrement(&g_blocked);
        Wh_Log(L"BLOCKED RegSetValueExW: %s (total=%ld)", name, n);
        return ERROR_ACCESS_DENIED;
    }
    return RegSetValueExW_Orig(hk, name, res, type, data, size);
}

LONG WINAPI RegSetValueExA_Hook(HKEY hk, LPCSTR name, DWORD res, DWORD type, const BYTE* data, DWORD size) {
    if (PinnedA(name)) {
        LONG n = InterlockedIncrement(&g_blocked);
        Wh_Log(L"BLOCKED RegSetValueExA: %S (total=%ld)", name, n);
        return ERROR_ACCESS_DENIED;
    }
    return RegSetValueExA_Orig(hk, name, res, type, data, size);
}

LONG WINAPI RegSetKeyValueW_Hook(HKEY hk, LPCWSTR sub, LPCWSTR name, DWORD type, const BYTE* data, DWORD size) {
    if (PinnedW(name)) {
        LONG n = InterlockedIncrement(&g_blocked);
        Wh_Log(L"BLOCKED RegSetKeyValueW: %s (total=%ld)", name, n);
        return ERROR_ACCESS_DENIED;
    }
    return RegSetKeyValueW_Orig(hk, sub, name, type, data, size);
}

NTSTATUS NTAPI NtSetValueKey_Hook(HANDLE key, MS_UNI* name, ULONG idx, ULONG type, void* data, ULONG size) {
    if (PinnedUni(name)) {
        LONG n = InterlockedIncrement(&g_blocked);
        Wh_Log(L"BLOCKED NtSetValueKey: %.*s (total=%ld)", (int)(name->Length / sizeof(wchar_t)), name->Buffer, n);
        return (NTSTATUS)0xC0000022; // STATUS_ACCESS_DENIED
    }
    // diagnostics: log the first 60 set-value names flowing through this process
    LONG m = InterlockedIncrement(&g_logged);
    if (m <= 60 && name && name->Buffer && name->Length) {
        Wh_Log(L"[diag %ld] NtSetValueKey: %.*s", m, (int)(name->Length / sizeof(wchar_t)), name->Buffer);
    }
    return NtSetValueKey_Orig(key, name, idx, type, data, size);
}

BOOL Wh_ModInit() {
    HMODULE ntdll = GetModuleHandleW(L"ntdll.dll");

    if (!Wh_SetFunctionHook((void*)RegSetValueExW, (void*)RegSetValueExW_Hook, (void**)&RegSetValueExW_Orig))
        Wh_Log(L"hook failed: RegSetValueExW");
    if (!Wh_SetFunctionHook((void*)RegSetValueExA, (void*)RegSetValueExA_Hook, (void**)&RegSetValueExA_Orig))
        Wh_Log(L"hook failed: RegSetValueExA");

    FARPROC pSetKeyValue = GetProcAddress(GetModuleHandleW(L"advapi32.dll"), "RegSetKeyValueW");
    if (pSetKeyValue && !Wh_SetFunctionHook(pSetKeyValue, (void*)RegSetKeyValueW_Hook, (void**)&RegSetKeyValueW_Orig))
        Wh_Log(L"hook failed: RegSetKeyValueW");

    if (ntdll) {
        FARPROC pNtSet = GetProcAddress(ntdll, "NtSetValueKey");
        if (pNtSet) {
            if (!Wh_SetFunctionHook(pNtSet, (void*)NtSetValueKey_Hook, (void**)&NtSetValueKey_Orig))
                Wh_Log(L"hook failed: NtSetValueKey");
        } else {
            Wh_Log(L"NtSetValueKey export not found");
        }
    }

    Wh_Log(L"msime-chs-cloud-pin v0.2.0 initialized (ntdll-level)");
    return TRUE;
}

void Wh_ModUninit() {
    Wh_Log(L"msime-chs-cloud-pin unloaded (blocked total=%ld)", g_blocked);
}
