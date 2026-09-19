// ==WindhawkMod==
// @id              msime-chs-cloud-pin
// @name            MSIME CHS: pin cloud-suggestion settings
// @description     Blocks TextInputHost.exe from re-enabling "Enable Cloud Candidate" / "AutoShowCloudSuggestion"; other settings writes are untouched, so the Settings app keeps working.
// @version         0.1.0
// @author          klp
// @include         C:\Windows\SystemApps\MicrosoftWindows.Client.CBS_cw5n1h2txyewy\TextInputHost.exe
// @architecture    x86-64
// ==/WindhawkMod==

#include <windows.h>

using RegSetValueExW_t = LONG(WINAPI*)(HKEY, LPCWSTR, DWORD, DWORD, const BYTE*, DWORD);
using RegSetValueExA_t = LONG(WINAPI*)(HKEY, LPCSTR, DWORD, DWORD, const BYTE*, DWORD);

RegSetValueExW_t RegSetValueExW_Orig = nullptr;
RegSetValueExA_t RegSetValueExA_Orig = nullptr;

static volatile LONG g_blockedCount = 0;

static bool IsPinnedValueW(LPCWSTR name) {
    if (!name) return false;
    return wcscmp(name, L"Enable Cloud Candidate") == 0 ||
           wcscmp(name, L"AutoShowCloudSuggestion") == 0;
}

static bool IsPinnedValueA(LPCSTR name) {
    if (!name) return false;
    return strcmp(name, "Enable Cloud Candidate") == 0 ||
           strcmp(name, "AutoShowCloudSuggestion") == 0;
}

LONG WINAPI RegSetValueExW_Hook(HKEY hKey, LPCWSTR valueName, DWORD reserved,
                                DWORD type, const BYTE* data, DWORD size) {
    if (IsPinnedValueW(valueName)) {
        LONG n = InterlockedIncrement(&g_blockedCount);
        if (n <= 10) Wh_Log(L"BLOCKED RegSetValueExW: %s (total=%ld)", valueName, n);
        return ERROR_ACCESS_DENIED;
    }
    return RegSetValueExW_Orig(hKey, valueName, reserved, type, data, size);
}

LONG WINAPI RegSetValueExA_Hook(HKEY hKey, LPCSTR valueName, DWORD reserved,
                                DWORD type, const BYTE* data, DWORD size) {
    if (IsPinnedValueA(valueName)) {
        LONG n = InterlockedIncrement(&g_blockedCount);
        if (n <= 10) Wh_Log(L"BLOCKED RegSetValueExA: %S (total=%ld)", valueName, n);
        return ERROR_ACCESS_DENIED;
    }
    return RegSetValueExA_Orig(hKey, valueName, reserved, type, data, size);
}

BOOL Wh_ModInit() {
    if (!Wh_SetFunctionHook((void*)RegSetValueExW, (void*)RegSetValueExW_Hook,
                            (void**)&RegSetValueExW_Orig)) {
        Wh_Log(L"Failed to hook RegSetValueExW");
        return FALSE;
    }
    if (!Wh_SetFunctionHook((void*)RegSetValueExA, (void*)RegSetValueExA_Hook,
                            (void**)&RegSetValueExA_Orig)) {
        Wh_Log(L"Failed to hook RegSetValueExA");
        return FALSE;
    }
    Wh_Log(L"msime-chs-cloud-pin initialized");
    return TRUE;
}

void Wh_ModUninit() {
    Wh_Log(L"msime-chs-cloud-pin unloaded");
}
