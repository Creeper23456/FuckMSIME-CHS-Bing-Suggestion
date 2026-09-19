// ============================================================================
//  strings.h — FuckMSIME-CHS-Bing-Suggestion i18n table
//
//  Single-header string mapping. main.cpp only references STR_* keys via L().
//  To add a language: append an array + one entry in kLocales.
// ============================================================================

#pragma once

enum StrId {
    STR_APP_NAME = 0,
    STR_UI_INSTALL_TITLE,
    STR_UI_INSTALL_CONFIRM,
    STR_UI_FOUND_INSTALLED,
    STR_UI_UPGRADE_OR_REMOVE,
    STR_UI_BTN_UPGRADE,
    STR_UI_BTN_UNINSTALL,
    STR_UI_BTN_CANCEL,
    STR_UI_INSTALL_DONE,
    STR_UI_UPGRADE_DONE,
    STR_UI_UNINSTALL_DONE,
    STR_UI_OP_FAILED_FMT,   // one %lu
    STR_UI_CANCELLED,
    STR_USAGE,
    STR_COUNT
};

// ---------------------------------------------------------------- zh-CN ----

static const wchar_t* const kStrings_zhCN[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"安装系统服务",
    /* STR_UI_INSTALL_CONFIRM  */ L"即将把本程序安装为系统服务：\n\n"
        L"  · 安装位置：Program Files\n"
        L"  · 开机自动启动\n"
        L"  · 以 SYSTEM 权限运行，作用于所有用户\n"
        L"  · 将微软拼音云候选/自动展开建议永久保持关闭\n\n"
        L"是否继续？",
    /* STR_UI_FOUND_INSTALLED  */ L"检测到已安装",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"本服务已安装在系统中。\n\n"
        L"「升级」—— 用当前程序替换已安装版本并重启服务\n"
        L"「移除服务」—— 停止并移除服务（不删除程序文件与日志）",
    /* STR_UI_BTN_UPGRADE      */ L"升级",
    /* STR_UI_BTN_UNINSTALL    */ L"移除服务",
    /* STR_UI_BTN_CANCEL       */ L"取消",
    /* STR_UI_INSTALL_DONE     */ L"安装完成，服务已启动。\n\n"
        L"从现在起，所有用户的微软拼音云候选设置都会被强制保持关闭（开机自动生效）。",
    /* STR_UI_UPGRADE_DONE     */ L"升级完成，服务已用新版本重启。",
    /* STR_UI_UNINSTALL_DONE   */ L"服务已停止并移除。\n\n"
        L"程序文件与日志仍保留在原处，可手动删除。",
    /* STR_UI_OP_FAILED_FMT    */ L"操作失败（错误码 %lu）。\n\n请确认以管理员身份运行。",
    /* STR_UI_CANCELLED        */ L"已取消，未做任何更改。",
    /* STR_USAGE               */ L"用法:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    安装并启动服务（需管理员）\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  停止并移除服务（需管理员）\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      控制台调试模式\n"
        L"不带参数直接运行则进入图形安装/升级/移除服务向导。",
};

// ---------------------------------------------------------------- en-US ----

static const wchar_t* const kStrings_enUS[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"Install system service",
    /* STR_UI_INSTALL_CONFIRM  */ L"This will install the program as a Windows service:\n\n"
        L"  · Location: Program Files\n"
        L"  · Starts automatically at boot\n"
        L"  · Runs as SYSTEM, covering ALL users\n"
        L"  · Keeps Microsoft Pinyin cloud suggestions permanently OFF\n\n"
        L"Continue?",
    /* STR_UI_FOUND_INSTALLED  */ L"Installation detected",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"The service is already installed.\n\n"
        L"Upgrade — replace the installed copy with this build and restart the service\n"
        L"Remove service — stop and remove the service (program files and logs are kept)",
    /* STR_UI_BTN_UPGRADE      */ L"Upgrade",
    /* STR_UI_BTN_UNINSTALL    */ L"Remove service",
    /* STR_UI_BTN_CANCEL       */ L"Cancel",
    /* STR_UI_INSTALL_DONE     */ L"Installed. The service is now running.\n\n"
        L"From now on the Microsoft Pinyin cloud-suggestion settings are kept OFF for every user (survives reboots).",
    /* STR_UI_UPGRADE_DONE     */ L"Upgraded. The service has been restarted with the new build.",
    /* STR_UI_UNINSTALL_DONE   */ L"The service has been stopped and removed.\n\n"
        L"Program files and logs are kept in place and can be deleted manually.",
    /* STR_UI_OP_FAILED_FMT    */ L"Operation failed (error %lu).\n\nMake sure you are running as administrator.",
    /* STR_UI_CANCELLED        */ L"Cancelled. Nothing was changed.",
    /* STR_USAGE               */ L"Usage:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    install + start service (elevated)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  stop + remove service (elevated)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      console debug mode\n"
        L"Run without arguments for the graphical install/upgrade/service-removal wizard.",
};

// ---------------------------------------------------------------- picker ----

struct LocaleEntry {
    LANGID lang;
    const wchar_t* const* table;
};

static const LocaleEntry kLocales[] = {
    { MAKELANGID(LANG_CHINESE, SUBLANG_CHINESE_SIMPLIFIED), kStrings_zhCN },
    { MAKELANGID(LANG_ENGLISH, SUBLANG_ENGLISH_US),         kStrings_enUS },
};

inline const wchar_t* L(StrId id) {
    static const wchar_t* const* table = [] {
        LANGID ui = GetUserDefaultUILanguage();
        for (const auto& e : kLocales)
            if (e.lang == ui) return e.table;
        return kStrings_enUS;   // fallback
    }();
    return table[id];
}
