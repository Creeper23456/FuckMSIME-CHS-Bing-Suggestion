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

// ---------------------------------------------------------------- ar-SA ----

static const wchar_t* const kStrings_arSA[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"تثبيت خدمة النظام",
    /* STR_UI_INSTALL_CONFIRM  */ L"سيتم تثبيت هذا البرنامج كخدمة Windows:\n\n"
        L"  · الموقع: Program Files\n"
        L"  · يبدأ تلقائيًا عند إقلاع النظام\n"
        L"  · يعمل بصلاحية SYSTEM ويشمل جميع المستخدمين\n"
        L"  · يُبقي اقتراحات السحابة في Microsoft Pinyin مطفأة نهائيًا\n\n"
        L"هل تريد المتابعة؟",
    /* STR_UI_FOUND_INSTALLED  */ L"تم اكتشاف تثبيت سابق",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"الخدمة مثبتة بالفعل.\n\n"
        L"«ترقية» — استبدال النسخة المثبتة بهذا الإصدار وإعادة تشغيل الخدمة\n"
        L"«إزالة الخدمة» — إيقاف الخدمة وإزالتها (تبقى ملفات البرنامج والسجلات كما هي)",
    /* STR_UI_BTN_UPGRADE      */ L"ترقية",
    /* STR_UI_BTN_UNINSTALL    */ L"إزالة الخدمة",
    /* STR_UI_BTN_CANCEL       */ L"إلغاء",
    /* STR_UI_INSTALL_DONE     */ L"تم التثبيت وبدأت الخدمة العمل.\n\n"
        L"من الآن فصاعدًا ستُفرض إعدادات اقتراحات السحابة في Microsoft Pinyin على وضع الإيقاف لجميع المستخدمين (ويستمر ذلك بعد إعادة التشغيل).",
    /* STR_UI_UPGRADE_DONE     */ L"اكتملت الترقية وأُعيد تشغيل الخدمة بالإصدار الجديد.",
    /* STR_UI_UNINSTALL_DONE   */ L"تم إيقاف الخدمة وإزالتها.\n\n"
        L"تبقى ملفات البرنامج والسجلات في مكانها ويمكن حذفها يدويًا.",
    /* STR_UI_OP_FAILED_FMT    */ L"فشلت العملية (رمز الخطأ %lu).\n\nتأكد من تشغيل البرنامج كمسؤول.",
    /* STR_UI_CANCELLED        */ L"تم الإلغاء. لم يطرأ أي تغيير.",
    /* STR_USAGE               */ L"الاستخدام:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    تثبيت الخدمة وبدء تشغيلها (يتطلب صلاحيات المسؤول)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  إيقاف الخدمة وإزالتها (يتطلب صلاحيات المسؤول)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      وضع التصحيح في وحدة التحكم\n"
        L"عند التشغيل بدون وسيطات تُفتح معالج التثبيت/الترقية/الإزالة الرسومي.",
};

// ---------------------------------------------------------------- fr-FR ----

static const wchar_t* const kStrings_frFR[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"Installer le service système",
    /* STR_UI_INSTALL_CONFIRM  */ L"Ce programme sera installé en tant que service Windows :\n\n"
        L"  · Emplacement : Program Files\n"
        L"  · Démarrage automatique au démarrage du système\n"
        L"  · S'exécute en tant que SYSTEM, pour TOUS les utilisateurs\n"
        L"  · Maintient définitivement désactivées les suggestions cloud de Microsoft Pinyin\n\n"
        L"Continuer ?",
    /* STR_UI_FOUND_INSTALLED  */ L"Installation détectée",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"Le service est déjà installé.\n\n"
        L"« Mettre à niveau » — remplace la copie installée par cette version et redémarre le service\n"
        L"« Supprimer le service » — arrête et supprime le service (fichiers du programme et journaux conservés)",
    /* STR_UI_BTN_UPGRADE      */ L"Mettre à niveau",
    /* STR_UI_BTN_UNINSTALL    */ L"Supprimer le service",
    /* STR_UI_BTN_CANCEL       */ L"Annuler",
    /* STR_UI_INSTALL_DONE     */ L"Installation terminée. Le service est en cours d'exécution.\n\n"
        L"Désormais, les paramètres de suggestion cloud de Microsoft Pinyin restent désactivés pour tous les utilisateurs (y compris après redémarrage).",
    /* STR_UI_UPGRADE_DONE     */ L"Mise à niveau terminée. Le service a été redémarré avec la nouvelle version.",
    /* STR_UI_UNINSTALL_DONE   */ L"Le service a été arrêté et supprimé.\n\n"
        L"Les fichiers du programme et les journaux restent en place et peuvent être supprimés manuellement.",
    /* STR_UI_OP_FAILED_FMT    */ L"Échec de l'opération (erreur %lu).\n\nAssurez-vous d'exécuter le programme en tant qu'administrateur.",
    /* STR_UI_CANCELLED        */ L"Annulé. Aucune modification n'a été effectuée.",
    /* STR_USAGE               */ L"Utilisation :\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    installe et démarre le service (élévé)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  arrête et supprime le service (élévé)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      mode débogage console\n"
        L"Sans argument : ouverture de l'assistant graphique d'installation/mise à niveau/suppression.",
};

// ---------------------------------------------------------------- ru-RU ----

static const wchar_t* const kStrings_ruRU[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"Установка системной службы",
    /* STR_UI_INSTALL_CONFIRM  */ L"Программа будет установлена как служба Windows:\n\n"
        L"  · Расположение: Program Files\n"
        L"  · Автозапуск при загрузке системы\n"
        L"  · Работает от имени SYSTEM, действует для ВСЕХ пользователей\n"
        L"  · Навсегда отключает облачные подсказки Microsoft Pinyin\n\n"
        L"Продолжить?",
    /* STR_UI_FOUND_INSTALLED  */ L"Обнаружена установка",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"Служба уже установлена.\n\n"
        L"«Обновить» — заменяет установленную копию этой сборкой и перезапускает службу\n"
        L"«Удалить службу» — останавливает и удаляет службу (файлы программы и журналы сохраняются)",
    /* STR_UI_BTN_UPGRADE      */ L"Обновить",
    /* STR_UI_BTN_UNINSTALL    */ L"Удалить службу",
    /* STR_UI_BTN_CANCEL       */ L"Отмена",
    /* STR_UI_INSTALL_DONE     */ L"Установка завершена, служба запущена.\n\n"
        L"Теперь облачные настройки Microsoft Pinyin будут принудительно отключены для всех пользователей (сохраняется после перезагрузки).",
    /* STR_UI_UPGRADE_DONE     */ L"Обновление завершено, служба перезапущена с новой версией.",
    /* STR_UI_UNINSTALL_DONE   */ L"Служба остановлена и удалена.\n\n"
        L"Файлы программы и журналы остаются на месте, их можно удалить вручную.",
    /* STR_UI_OP_FAILED_FMT    */ L"Не удалось выполнить операцию (ошибка %lu).\n\nУбедитесь, что программа запущена от имени администратора.",
    /* STR_UI_CANCELLED        */ L"Отменено. Никаких изменений не внесено.",
    /* STR_USAGE               */ L"Использование:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    установить и запустить службу (нужны права администратора)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  остановить и удалить службу (нужны права администратора)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      режим отладки в консоли\n"
        L"Без аргументов запускается графический мастер установки/обновления/удаления.",
};

// ---------------------------------------------------------------- es-ES ----

static const wchar_t* const kStrings_esES[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"Instalar el servicio del sistema",
    /* STR_UI_INSTALL_CONFIRM  */ L"Esto instalará el programa como un servicio de Windows:\n\n"
        L"  · Ubicación: Program Files\n"
        L"  · Se inicia automáticamente al arrancar el sistema\n"
        L"  · Se ejecuta como SYSTEM y afecta a TODOS los usuarios\n"
        L"  · Mantiene desactivadas permanentemente las sugerencias en la nube de Microsoft Pinyin\n\n"
        L"¿Continuar?",
    /* STR_UI_FOUND_INSTALLED  */ L"Instalación detectada",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"El servicio ya está instalado.\n\n"
        L"«Actualizar» — reemplaza la copia instalada por esta versión y reinicia el servicio\n"
        L"«Quitar el servicio» — detiene y elimina el servicio (se conservan los archivos del programa y los registros)",
    /* STR_UI_BTN_UPGRADE      */ L"Actualizar",
    /* STR_UI_BTN_UNINSTALL    */ L"Quitar el servicio",
    /* STR_UI_BTN_CANCEL       */ L"Cancelar",
    /* STR_UI_INSTALL_DONE     */ L"Instalación completada; el servicio ya está en ejecución.\n\n"
        L"A partir de ahora, la configuración de nube de Microsoft Pinyin permanecerá desactivada para todos los usuarios (también tras reiniciar).",
    /* STR_UI_UPGRADE_DONE     */ L"Actualización completada; el servicio se ha reiniciado con la nueva versión.",
    /* STR_UI_UNINSTALL_DONE   */ L"El servicio se ha detenido y eliminado.\n\n"
        L"Los archivos del programa y los registros se conservan en su lugar y pueden borrarse manualmente.",
    /* STR_UI_OP_FAILED_FMT    */ L"Error en la operación (código %lu).\n\nAsegúrese de ejecutar el programa como administrador.",
    /* STR_UI_CANCELLED        */ L"Cancelado. No se realizó ningún cambio.",
    /* STR_USAGE               */ L"Uso:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    instala e inicia el servicio (requiere administrador)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  detiene y elimina el servicio (requiere administrador)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      modo de depuración en consola\n"
        L"Sin argumentos se abre el asistente gráfico de instalación/actualización/eliminación.",
};

// ---------------------------------------------------------------- picker ----

struct LocaleEntry {
    LANGID lang;
    const wchar_t* const* table;
};

static const LocaleEntry kLocales[] = {
    { 0x0804, kStrings_zhCN },   // zh-CN  Chinese (Simplified)
    { 0x0409, kStrings_enUS },   // en-US  English (United States)
    { 0x0401, kStrings_arSA },   // ar-SA  Arabic
    { 0x040C, kStrings_frFR },   // fr-FR  French
    { 0x0419, kStrings_ruRU },   // ru-RU  Russian
    { 0x0C0A, kStrings_esES },   // es-ES  Spanish (Modern Sort)
};

inline const wchar_t* L(StrId id) {
    static const wchar_t* const* table = [] {
        const LANGID ui = GetUserDefaultUILanguage();
        for (const auto& e : kLocales)                  // exact locale match
            if (e.lang == ui) return e.table;
        const LANGID prim = PRIMARYLANGID(ui);
        for (const auto& e : kLocales)                  // same base language:
            if (PRIMARYLANGID(e.lang) == prim)          // en-GB -> en-US etc.
                return e.table;
        return kStrings_enUS;   // fallback
    }();
    return table[id];
}
