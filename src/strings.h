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

// ---------------------------------------------------------------- zh-TW ----

static const wchar_t* const kStrings_zhTW[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"安裝系統服務",
    /* STR_UI_INSTALL_CONFIRM  */ L"即將把本程式安裝為系統服務：\n\n"
        L"  · 安裝位置：Program Files\n"
        L"  · 開機自動啟動\n"
        L"  · 以 SYSTEM 權限執行，作用於所有使用者\n"
        L"  · 將微軟拼音的雲端候選/自動顯示建議永久保持關閉\n\n"
        L"是否繼續？",
    /* STR_UI_FOUND_INSTALLED  */ L"偵測到已安裝",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"本服務已安裝在系統中。\n\n"
        L"「升級」—— 用目前程式取代已安裝版本並重新啟動服務\n"
        L"「移除服務」—— 停止並移除服務（不會刪除程式檔案與記錄檔）",
    /* STR_UI_BTN_UPGRADE      */ L"升級",
    /* STR_UI_BTN_UNINSTALL    */ L"移除服務",
    /* STR_UI_BTN_CANCEL       */ L"取消",
    /* STR_UI_INSTALL_DONE     */ L"安裝完成，服務已啟動。\n\n"
        L"從現在起，所有使用者的微軟拼音雲端候選設定都會被強制保持關閉（開機自動生效）。",
    /* STR_UI_UPGRADE_DONE     */ L"升級完成，服務已以新版本重新啟動。",
    /* STR_UI_UNINSTALL_DONE   */ L"服務已停止並移除。\n\n"
        L"程式檔案與記錄檔仍保留在原處，可手動刪除。",
    /* STR_UI_OP_FAILED_FMT    */ L"操作失敗（錯誤碼 %lu）。\n\n請確認以系統管理員身分執行。",
    /* STR_UI_CANCELLED        */ L"已取消，未做任何變更。",
    /* STR_USAGE               */ L"用法:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    安裝並啟動服務（需系統管理員）\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  停止並移除服務（需系統管理員）\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      主控台偵錯模式\n"
        L"直接執行（不帶參數）會進入圖形安裝/升級/移除服務精靈。",
};

// ---------------------------------------------------------------- ja-JP ----

static const wchar_t* const kStrings_jaJP[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"システムサービスのインストール",
    /* STR_UI_INSTALL_CONFIRM  */ L"このプログラムを Windows サービスとしてインストールします：\n\n"
        L"  · 場所：Program Files\n"
        L"  · システム起動時に自動開始\n"
        L"  · SYSTEM 権限で実行し、すべてのユーザーに適用\n"
        L"  · Microsoft Pinyin のクラウド候補を完全にオフに固定\n\n"
        L"続行しますか？",
    /* STR_UI_FOUND_INSTALLED  */ L"インストール済みを検出",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"このサービスはすでにインストールされています。\n\n"
        L"「アップグレード」— 現在のビルドでインストール済みコピーを置き換え、サービスを再起動します\n"
        L"「サービスの削除」— サービスを停止・削除します（プログラムファイルとログは保持されます）",
    /* STR_UI_BTN_UPGRADE      */ L"アップグレード",
    /* STR_UI_BTN_UNINSTALL    */ L"サービスの削除",
    /* STR_UI_BTN_CANCEL       */ L"キャンセル",
    /* STR_UI_INSTALL_DONE     */ L"インストールが完了し、サービスが開始されました。\n\n"
        L"今後、すべてのユーザーの Microsoft Pinyin クラウド候補設定は強制的にオフに保たれます（再起動後も有効）。",
    /* STR_UI_UPGRADE_DONE     */ L"アップグレードが完了し、新しいビルドでサービスを再起動しました。",
    /* STR_UI_UNINSTALL_DONE   */ L"サービスを停止・削除しました。\n\n"
        L"プログラムファイルとログは元の場所に残ります。手動で削除できます。",
    /* STR_UI_OP_FAILED_FMT    */ L"操作に失敗しました（エラー %lu）。\n\n管理者として実行していることを確認してください。",
    /* STR_UI_CANCELLED        */ L"キャンセルされました。変更はありません。",
    /* STR_USAGE               */ L"使い方:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    サービスをインストールして開始（管理者権限）\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  サービスを停止して削除（管理者権限）\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      コンソールデバッグモード\n"
        L"引数なしで実行すると、GUI のインストール/アップグレード/削除ウィザードが起動します。",
};

// ---------------------------------------------------------------- ko-KR ----

static const wchar_t* const kStrings_koKR[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"시스템 서비스 설치",
    /* STR_UI_INSTALL_CONFIRM  */ L"이 프로그램을 Windows 서비스로 설치합니다:\n\n"
        L"  · 위치: Program Files\n"
        L"  · 시스템 부팅 시 자동 시작\n"
        L"  · SYSTEM 권한으로 실행되며 모든 사용자에게 적용\n"
        L"  · Microsoft Pinyin 클라우드 추천을 영구적으로 끔\n\n"
        L"계속하시겠습니까?",
    /* STR_UI_FOUND_INSTALLED  */ L"설치됨 감지",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"이 서비스는 이미 설치되어 있습니다.\n\n"
        L"「업그레이드」— 설치된 복사본을 이 빌드로 교체하고 서비스를 다시 시작합니다\n"
        L"「서비스 제거」— 서비스를 중지하고 제거합니다 (프로그램 파일과 로그는 유지됨)",
    /* STR_UI_BTN_UPGRADE      */ L"업그레이드",
    /* STR_UI_BTN_UNINSTALL    */ L"서비스 제거",
    /* STR_UI_BTN_CANCEL       */ L"취소",
    /* STR_UI_INSTALL_DONE     */ L"설치 완료, 서비스가 시작되었습니다.\n\n"
        L"이제부터 모든 사용자의 Microsoft Pinyin 클라우드 추천 설정이 강제로 꺼진 상태로 유지됩니다 (재부팅 후에도).",
    /* STR_UI_UPGRADE_DONE     */ L"업그레이드 완료, 새 빌드로 서비스를 다시 시작했습니다.",
    /* STR_UI_UNINSTALL_DONE   */ L"서비스가 중지되고 제거되었습니다.\n\n"
        L"프로그램 파일과 로그는 원래 위치에 유지되며 수동으로 삭제할 수 있습니다.",
    /* STR_UI_OP_FAILED_FMT    */ L"작업 실패 (오류 %lu).\n\n관리자 권한으로 실행 중인지 확인하세요.",
    /* STR_UI_CANCELLED        */ L"취소되었습니다. 변경된 내용이 없습니다.",
    /* STR_USAGE               */ L"사용법:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    서비스 설치 후 시작 (관리자 권한)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  서비스 중지 후 제거 (관리자 권한)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      콘솔 디버그 모드\n"
        L"인수 없이 실행하면 그래픽 설치/업그레이드/제거 마법사가 열립니다.",
};

// ---------------------------------------------------------------- hi-IN ----

static const wchar_t* const kStrings_hiIN[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"सिस्टम सेवा इंस्टॉल करें",
    /* STR_UI_INSTALL_CONFIRM  */ L"यह प्रोग्राम Windows सेवा के रूप में इंस्टॉल होगा:\n\n"
        L"  · स्थान: Program Files\n"
        L"  · सिस्टम बूट पर स्वतः शुरू\n"
        L"  · SYSTEM विशेषाधिकार के साथ चलता है, सभी उपयोगकर्ताओं पर लागू\n"
        L"  · Microsoft Pinyin के क्लाउड सुझाव स्थायी रूप से बंद रखता है\n\n"
        L"जारी रखें?",
    /* STR_UI_FOUND_INSTALLED  */ L"इंस्टॉलेशन पाया गया",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"यह सेवा पहले से इंस्टॉल है।\n\n"
        L"「अपग्रेड」— इंस्टॉल की गई कॉपी को इस बिल्ड से बदलकर सेवा पुनः आरंभ करता है\n"
        L"「सेवा हटाएँ」— सेवा को रोककर हटा देता है (प्रोग्राम फ़ाइलें और लॉग बने रहते हैं)",
    /* STR_UI_BTN_UPGRADE      */ L"अपग्रेड",
    /* STR_UI_BTN_UNINSTALL    */ L"सेवा हटाएँ",
    /* STR_UI_BTN_CANCEL       */ L"रद्द करें",
    /* STR_UI_INSTALL_DONE     */ L"इंस्टॉल पूर्ण, सेवा चालू है।\n\n"
        L"अब से सभी उपयोगकर्ताओं के लिए Microsoft Pinyin की क्लाउड सेटिंग्स बंद रहेंगी (रीबूट के बाद भी)।",
    /* STR_UI_UPGRADE_DONE     */ L"अपग्रेड पूर्ण, सेवा नए बिल्ड से पुनः आरंभ हुई।",
    /* STR_UI_UNINSTALL_DONE   */ L"सेवा रोकी और हटा दी गई।\n\n"
        L"प्रोग्राम फ़ाइलें और लॉग अपने स्थान पर बने रहते हैं, इन्हें मैन्युअल रूप से हटाया जा सकता है।",
    /* STR_UI_OP_FAILED_FMT    */ L"ऑपरेशन विफल (त्रुटि %lu)।\n\nकृपया सुनिश्चित करें कि आप व्यवस्थापक के रूप में चला रहे हैं।",
    /* STR_UI_CANCELLED        */ L"रद्द किया गया। कोई बदलाव नहीं किया गया।",
    /* STR_USAGE               */ L"उपयोग:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    सेवा इंस्टॉल और प्रारंभ (एडमिन आवश्यक)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  सेवा रोकें और हटाएँ (एडमिन आवश्यक)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      कंसोल डिबग मोड\n"
        L"बिना आर्ग्युमेंट चलाने पर ग्राफ़िकल इंस्टॉल/अपग्रेड/सेवा-हटाने विज़ार्ड खुलता है।",
};

// ---------------------------------------------------------------- th-TH ----

static const wchar_t* const kStrings_thTH[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"ติดตั้งบริการระบบ",
    /* STR_UI_INSTALL_CONFIRM  */ L"โปรแกรมนี้จะถูกติดตั้งเป็นบริการของ Windows:\n\n"
        L"  · ตำแหน่ง: Program Files\n"
        L"  · เริ่มทำงานอัตโนมัติเมื่อบูตเครื่อง\n"
        L"  · ทำงานด้วยสิทธิ์ SYSTEM ครอบคลุมผู้ใช้ทุกคน\n"
        L"  · บังคับปิดข้อเสนอคลาวด์ของ Microsoft Pinyin อย่างถาวร\n\n"
        L"ต้องการดำเนินการต่อหรือไม่?",
    /* STR_UI_FOUND_INSTALLED  */ L"พบการติดตั้งอยู่แล้ว",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"บริการนี้ติดตั้งอยู่แล้ว\n\n"
        L"「อัปเกรด」— แทนที่สำเนาที่ติดตั้งไว้ด้วยรุ่นนี้แล้วรีสตาร์ทบริการ\n"
        L"「ถอนการติดตั้งบริการ」— หยุดและถอนบริการออก (ไฟล์โปรแกรมและไฟล์บันทึกจะถูกเก็บไว้)",
    /* STR_UI_BTN_UPGRADE      */ L"อัปเกรด",
    /* STR_UI_BTN_UNINSTALL    */ L"ถอนการติดตั้งบริการ",
    /* STR_UI_BTN_CANCEL       */ L"ยกเลิก",
    /* STR_UI_INSTALL_DONE     */ L"ติดตั้งเสร็จ บริการเริ่มทำงานแล้ว\n\n"
        L"จากนี้ไปการตั้งค่าคลาวด์ของ Microsoft Pinyin ของผู้ใช้ทุกคนจะถูกบังคับให้ปิดอยู่เสมอ (รวมทั้งหลังรีบูต)",
    /* STR_UI_UPGRADE_DONE     */ L"อัปเกรดเสร็จ บริการรีสตาร์ทด้วยรุ่นใหม่แล้ว",
    /* STR_UI_UNINSTALL_DONE   */ L"หยุดและถอนบริการออกแล้ว\n\n"
        L"ไฟล์โปรแกรมและไฟล์บันทึกยังอยู่ที่เดิม สามารถลบด้วยตนเองได้",
    /* STR_UI_OP_FAILED_FMT    */ L"การทำงานล้มเหลว (รหัสข้อผิดพลาด %lu)\n\nโปรดตรวจสอบว่ากำลังรันในฐานะผู้ดูแลระบบ",
    /* STR_UI_CANCELLED        */ L"ยกเลิกแล้ว ไม่มีการเปลี่ยนแปลงใดๆ",
    /* STR_USAGE               */ L"วิธีใช้:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    ติดตั้งและเริ่มบริการ (ต้องมีสิทธิ์ผู้ดูแลระบบ)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  หยุดและถอนบริการ (ต้องมีสิทธิ์ผู้ดูแลระบบ)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      โหมดดีบักแบบคอนโซล\n"
        L"หากรันโดยไม่ใส่อาร์กิวเมนต์ จะเปิดตัวช่วยติดตั้ง/อัปเกรด/ถอนการติดตั้งแบบกราฟิก",
};

// ---------------------------------------------------------------- vi-VN ----

static const wchar_t* const kStrings_viVN[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"Cài đặt dịch vụ hệ thống",
    /* STR_UI_INSTALL_CONFIRM  */ L"Chương trình này sẽ được cài đặt như một dịch vụ Windows:\n\n"
        L"  · Vị trí: Program Files\n"
        L"  · Tự khởi động khi bật máy\n"
        L"  · Chạy với quyền SYSTEM, áp dụng cho TẤT CẢ người dùng\n"
        L"  · Giữ vĩnh viễn chế độ tắt gợi ý đám mây của Microsoft Pinyin\n\n"
        L"Tiếp tục?",
    /* STR_UI_FOUND_INSTALLED  */ L"Phát hiện đã cài đặt",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"Dịch vụ này đã được cài đặt.\n\n"
        L"「Nâng cấp」— thay bản đã cài bằng bản build này rồi khởi động lại dịch vụ\n"
        L"「Gỡ dịch vụ」— dừng và gỡ bỏ dịch vụ (giữ nguyên tệp chương trình và nhật ký)",
    /* STR_UI_BTN_UPGRADE      */ L"Nâng cấp",
    /* STR_UI_BTN_UNINSTALL    */ L"Gỡ dịch vụ",
    /* STR_UI_BTN_CANCEL       */ L"Hủy bỏ",
    /* STR_UI_INSTALL_DONE     */ L"Đã cài đặt xong, dịch vụ đang chạy.\n\n"
        L"Từ giờ, cài đặt đám mây của Microsoft Pinyin sẽ luôn bị ép tắt với mọi người dùng (kể cả sau khi khởi động lại).",
    /* STR_UI_UPGRADE_DONE     */ L"Đã nâng cấp xong, dịch vụ đã khởi động lại bằng bản mới.",
    /* STR_UI_UNINSTALL_DONE   */ L"Đã dừng và gỡ bỏ dịch vụ.\n\n"
        L"Tệp chương trình và nhật ký vẫn được giữ nguyên, có thể xóa thủ công.",
    /* STR_UI_OP_FAILED_FMT    */ L"Thao tác thất bại (mã lỗi %lu).\n\nHãy chắc chắn rằng bạn đang chạy với quyền quản trị viên.",
    /* STR_UI_CANCELLED        */ L"Đã hủy. Không có gì thay đổi.",
    /* STR_USAGE               */ L"Cách dùng:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    cài đặt và khởi động dịch vụ (cần quyền admin)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  dừng và gỡ dịch vụ (cần quyền admin)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      chế độ gỡ lỗi console\n"
        L"Chạy không đối số sẽ mở trình hướng dẫn cài đặt/nâng cấp/gỡ dịch vụ bằng giao diện đồ họa.",
};

// ---------------------------------------------------------------- id-ID ----

static const wchar_t* const kStrings_idID[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"Pasang layanan sistem",
    /* STR_UI_INSTALL_CONFIRM  */ L"Program ini akan dipasang sebagai layanan Windows:\n\n"
        L"  · Lokasi: Program Files\n"
        L"  · Mulai otomatis saat komputer dinyalakan\n"
        L"  · Berjalan sebagai SYSTEM, berlaku untuk SEMUA pengguna\n"
        L"  · Menjaga saran cloud Microsoft Pinyin tetap nonaktif permanen\n\n"
        L"Lanjutkan?",
    /* STR_UI_FOUND_INSTALLED  */ L"Instalasi terdeteksi",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"Layanan ini sudah terpasang.\n\n"
        L"「Tingkatkan」— mengganti salinan terpasang dengan build ini lalu memulai ulang layanan\n"
        L"「Hapus layanan」— menghentikan dan menghapus layanan (berkas program dan log tetap disimpan)",
    /* STR_UI_BTN_UPGRADE      */ L"Tingkatkan",
    /* STR_UI_BTN_UNINSTALL    */ L"Hapus layanan",
    /* STR_UI_BTN_CANCEL       */ L"Batal",
    /* STR_UI_INSTALL_DONE     */ L"Terpasang. Layanan kini berjalan.\n\n"
        L"Mulai sekarang pengaturan cloud Microsoft Pinyin akan dipaksa nonaktif untuk semua pengguna (bertahan setelah reboot).",
    /* STR_UI_UPGRADE_DONE     */ L"Peningkatan selesai. Layanan telah dimulai ulang dengan build baru.",
    /* STR_UI_UNINSTALL_DONE   */ L"Layanan telah dihentikan dan dihapus.\n\n"
        L"Berkas program dan log tetap ada di tempatnya dan dapat dihapus manual.",
    /* STR_UI_OP_FAILED_FMT    */ L"Operasi gagal (kesalahan %lu).\n\nPastikan Anda menjalankan sebagai administrator.",
    /* STR_UI_CANCELLED        */ L"Dibatalkan. Tidak ada perubahan.",
    /* STR_USAGE               */ L"Penggunaan:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    pasang + mulai layanan (butuh admin)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  hentikan + hapus layanan (butuh admin)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      mode debug konsol\n"
        L"Tanpa argumen akan membuka wizard grafis pasang/tingkatkan/hapus layanan.",
};

// ---------------------------------------------------------------- ms-MY ----

static const wchar_t* const kStrings_msMY[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"Pasang perkhidmatan sistem",
    /* STR_UI_INSTALL_CONFIRM  */ L"Program ini akan dipasang sebagai perkhidmatan Windows:\n\n"
        L"  · Lokasi: Program Files\n"
        L"  · Bermula secara automatik semasa but\n"
        L"  · Berjalan sebagai SYSTEM, meliputi SEMUA pengguna\n"
        L"  · Mengekalkan cadangan awan Microsoft Pinyin kekal dimatikan\n\n"
        L"Teruskan?",
    /* STR_UI_FOUND_INSTALLED  */ L"Pemasangan dikesan",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"Perkhidmatan ini telah dipasang.\n\n"
        L"「Naik taraf」— ganti salinan terpasang dengan binaan ini dan mulakan semula perkhidmatan\n"
        L"「Buang perkhidmatan」— hentikan dan buang perkhidmatan (fail program dan log dikekalkan)",
    /* STR_UI_BTN_UPGRADE      */ L"Naik taraf",
    /* STR_UI_BTN_UNINSTALL    */ L"Buang perkhidmatan",
    /* STR_UI_BTN_CANCEL       */ L"Batal",
    /* STR_UI_INSTALL_DONE     */ L"Dipasang. Perkhidmatan kini berjalan.\n\n"
        L"Mulai sekarang tetapan awan Microsoft Pinyin akan dipaksa dimatikan untuk semua pengguna (kekal selepas but semula).",
    /* STR_UI_UPGRADE_DONE     */ L"Naik taraf selesai. Perkhidmatan telah dimulakan semula dengan binaan baharu.",
    /* STR_UI_UNINSTALL_DONE   */ L"Perkhidmatan telah dihentikan dan dibuang.\n\n"
        L"Fail program dan log kekal di tempatnya dan boleh dipadam secara manual.",
    /* STR_UI_OP_FAILED_FMT    */ L"Operasi gagal (ralat %lu).\n\nPastikan anda menjalankan sebagai pentadbir.",
    /* STR_UI_CANCELLED        */ L"Dibatalkan. Tiada perubahan dibuat.",
    /* STR_USAGE               */ L"Penggunaan:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    pasang + mulakan perkhidmatan (perlu pentadbir)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  hentikan + buang perkhidmatan (perlu pentadbir)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      mod nyahpepijat konsol\n"
        L"Tanpa hujah akan membuka wizard grafik pasang/naik taraf/buang perkhidmatan.",
};

// ---------------------------------------------------------------- fil-PH ----

static const wchar_t* const kStrings_filPH[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"Mag-install ng system service",
    /* STR_UI_INSTALL_CONFIRM  */ L"I-install ang program bilang Windows service:\n\n"
        L"  · Lokasyon: Program Files\n"
        L"  · Awtomatikong sisimula sa boot\n"
        L"  · Tumatakbo bilang SYSTEM, saklaw ang LAHAT ng user\n"
        L"  · Pinananatiling OFF nang permanente ang cloud suggestions ng Microsoft Pinyin\n\n"
        L"Ituloy?",
    /* STR_UI_FOUND_INSTALLED  */ L"Nakita ang naka-install",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"Naka-install na ang service.\n\n"
        L"「I-upgrade」— papalitan ang naka-install na kopya ng build na ito at ire-restart ang service\n"
        L"「Alisin ang service」— pipihintin at aalisin ang service (mananatili ang program files at logs)",
    /* STR_UI_BTN_UPGRADE      */ L"I-upgrade",
    /* STR_UI_BTN_UNINSTALL    */ L"Alisin ang service",
    /* STR_UI_BTN_CANCEL       */ L"Kanselahin",
    /* STR_UI_INSTALL_DONE     */ L"Naka-install na. Tumatakbo na ang service.\n\n"
        L"Mula ngayon, mananatiling OFF ang cloud-suggestion settings ng Microsoft Pinyin para sa lahat ng user (kahit mag-reboot).",
    /* STR_UI_UPGRADE_DONE     */ L"Na-upgrade na. Na-restart ang service gamit ang bagong build.",
    /* STR_UI_UNINSTALL_DONE   */ L"Nahinto at inalis na ang service.\n\n"
        L"Nananatili sa kinalalagyan ang program files at logs; maaari mo silang burahin nang mano-mano.",
    /* STR_UI_OP_FAILED_FMT    */ L"Nabigo ang operasyon (error %lu).\n\nSiguraduhing tumatakbo bilang administrator.",
    /* STR_UI_CANCELLED        */ L"Kinansela. Walang nabago.",
    /* STR_USAGE               */ L"Paggamit:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    i-install at simulan ang service (kailangan ng admin)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  ihinto at alisin ang service (kailangan ng admin)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      console debug mode\n"
        L"Kapag walang argumento, bubuksan ang graphical install/upgrade/service-removal wizard.",
};

// ---------------------------------------------------------------- bn-BD ----

static const wchar_t* const kStrings_bnBD[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"সিস্টেম সার্ভিস ইনস্টল করুন",
    /* STR_UI_INSTALL_CONFIRM  */ L"এই প্রোগ্রামটি Windows সার্ভিস হিসেবে ইনস্টল হবে:\n\n"
        L"  · অবস্থান: Program Files\n"
        L"  · বুটের সময় স্বয়ংক্রিয়ভাবে শুরু হবে\n"
        L"  · SYSTEM অনুমতি নিয়ে চলবে, সব ব্যবহারকারীর জন্য প্রযোজ্য\n"
        L"  · Microsoft Pinyin-এর ক্লাউড পরামর্শ স্থায়ীভাবে বন্ধ রাখবে\n\n"
        L"চালিয়ে যাবেন?",
    /* STR_UI_FOUND_INSTALLED  */ L"ইনস্টল করা পাওয়া গেছে",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"এই সার্ভিসটি ইতিমধ্যেই ইনস্টল করা আছে।\n\n"
        L"「আপগ্রেড」— ইনস্টল করা কপিটি এই বিল্ড দিয়ে বদলে সার্ভিস পুনরায় চালু করবে\n"
        L"「সার্ভিস সরান」— সার্ভিস বন্ধ করে সরিয়ে দেবে (প্রোগ্রাম ফাইল ও লগ রাখা হবে)",
    /* STR_UI_BTN_UPGRADE      */ L"আপগ্রেড",
    /* STR_UI_BTN_UNINSTALL    */ L"সার্ভিস সরান",
    /* STR_UI_BTN_CANCEL       */ L"বাতিল",
    /* STR_UI_INSTALL_DONE     */ L"ইনস্টল সম্পন্ন, সার্ভিস চালু আছে।\n\n"
        L"এখন থেকে সব ব্যবহারকারীর জন্য Microsoft Pinyin-এর ক্লাউড সেটিং বন্ধ থাকবে (রিবুটের পরেও)।",
    /* STR_UI_UPGRADE_DONE     */ L"আপগ্রেড সম্পন্ন, নতুন বিল্ড দিয়ে সার্ভিস পুনরায় চালু হয়েছে।",
    /* STR_UI_UNINSTALL_DONE   */ L"সার্ভিস বন্ধ ও সরানো হয়েছে।\n\n"
        L"প্রোগ্রাম ফাইল ও লগ জায়গামতো থেকে যাবে, ম্যানুয়ালি মুছে ফেলা যাবে।",
    /* STR_UI_OP_FAILED_FMT    */ L"কাজটি ব্যর্থ হয়েছে (ত্রুটি %lu)।\n\nনিশ্চিত করুন যে আপনি অ্যাডমিনিস্ট্রেটর হিসেবে চালাচ্ছেন।",
    /* STR_UI_CANCELLED        */ L"বাতিল করা হয়েছে। কিছুই পরিবর্তন হয়নি।",
    /* STR_USAGE               */ L"ব্যবহার:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    সার্ভিস ইনস্টল করে চালু করবে (অ্যাডমিন লাগবে)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  সার্ভিস বন্ধ করে সরাবে (অ্যাডমিন লাগবে)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      কনসোল ডিবাগ মোড\n"
        L"আর্গুমেন্ট ছাড়া চালালে গ্রাফিক্যাল ইনস্টল/আপগ্রেড/সার্ভিস-অপসারণ উইজার্ড খুলবে।",
};

// ---------------------------------------------------------------- ur-PK ----

static const wchar_t* const kStrings_urPK[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"سسٹم سروس انسٹال کریں",
    /* STR_UI_INSTALL_CONFIRM  */ L"یہ پروگرام Windows سروس کے طور پر انسٹال ہوگا:\n\n"
        L"  · مقام: Program Files\n"
        L"  · بوت پر خودکار شروع ہوگا\n"
        L"  · SYSTEM اجازت کے ساتھ چلے گا، تمام صارفین پر لاگو ہوگا\n"
        L"  · Microsoft Pinyin کی کلاؤڈ تجاویز ہمیشہ کے لیے بند رکھے گا\n\n"
        L"جاری رکھیں؟",
    /* STR_UI_FOUND_INSTALLED  */ L"انسٹیلیشن کا پتہ چلا",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"یہ سروس پہلے سے انسٹال ہے۔\n\n"
        L"«اپ گریڈ»— موجودہ کاپی کو اس بلڈ سے بدل کر سروس دوبارہ شروع کرے گا\n"
        L"«سروس ہٹائیں»— سروس کو روک کر ہٹا دے گا (پروگرام فائلیں اور لاگ محفوظ رہیں گے)",
    /* STR_UI_BTN_UPGRADE      */ L"اپ گریڈ",
    /* STR_UI_BTN_UNINSTALL    */ L"سروس ہٹائیں",
    /* STR_UI_BTN_CANCEL       */ L"منسوخ کریں",
    /* STR_UI_INSTALL_DONE     */ L"انسٹال مکمل، سروس شروع ہے۔\n\n"
        L"اب سے تمام صارفین کے لیے Microsoft Pinyin کی کلاؤڈ ترتیبات بند رہیں گی (ریبوٹ کے بعد بھی)۔",
    /* STR_UI_UPGRADE_DONE     */ L"اپ گریڈ مکمل، سروس نئے بلڈ کے ساتھ دوبارہ شروع ہوئی۔",
    /* STR_UI_UNINSTALL_DONE   */ L"سروس روک کر ہٹا دی گئی۔\n\n"
        L"پروگرام فائلیں اور لاگ اپنی جگہ محفوظ رہیں گے، انہیں دستی طور پر حذف کیا جا سکتا ہے۔",
    /* STR_UI_OP_FAILED_FMT    */ L"عمل ناکام رہا (خرابی %lu)۔\n\nبراہ کرم یقینی بنائیں کہ آپ ایڈمنسٹریٹر کے طور پر چلا رہے ہیں۔",
    /* STR_UI_CANCELLED        */ L"منسوخ کر دیا گیا۔ کوئی تبدیلی نہیں کی گئی۔",
    /* STR_USAGE               */ L"استعمال:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    سروس انسٹال کر کے شروع کرے گا (ایڈمن ضروری)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  سروس روک کر ہٹائے گا (ایڈمن ضروری)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      کنسول ڈیبگ موڈ\n"
        L"بغیر آرگیومنٹ کے چلانے پر گرافیکل انسٹال/اپ گریڈ/سروس ہٹانے کا وزرڈ کھلے گا۔",
};

// ---------------------------------------------------------------- ne-NP ----

static const wchar_t* const kStrings_neNP[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"सिस्टम सेवा स्थापना गर्नुहोस्",
    /* STR_UI_INSTALL_CONFIRM  */ L"यो प्रोग्राम Windows सेवाका रूपमा स्थापना हुनेछ:\n\n"
        L"  · स्थान: Program Files\n"
        L"  · सिस्टम बुट हुँदा स्वतः सुरु हुन्छ\n"
        L"  · SYSTEM अधिकारसँग चल्छ, सबै प्रयोगकर्तामा लागू हुन्छ\n"
        L"  · Microsoft Pinyin का क्लाउड सुझाव सधैँ बन्द राख्छ\n\n"
        L"जारी राख्ने?",
    /* STR_UI_FOUND_INSTALLED  */ L"स्थापना भेटियो",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"यो सेवा पहिले नै स्थापित छ।\n\n"
        L"「अपग्रेड」— स्थापित प्रतिलिपि यसै बिल्डले बदलेर सेवा पुनः सुरु गर्छ\n"
        L"「सेवा हटाउनुहोस्」— सेवा रोकी हटाउँछ (प्रोग्राम फाइल र लग राखिन्छ)",
    /* STR_UI_BTN_UPGRADE      */ L"अपग्रेड",
    /* STR_UI_BTN_UNINSTALL    */ L"सेवा हटाउनुहोस्",
    /* STR_UI_BTN_CANCEL       */ L"रद्द गर्नुहोस्",
    /* STR_UI_INSTALL_DONE     */ L"स्थापना भयो, सेवा चालु छ।\n\n"
        L"अबदेखि सबै प्रयोगकर्ताका लागि Microsoft Pinyin का क्लाउड सेटिङ बन्दै रहने छ (रिबुटपछि पनि)।",
    /* STR_UI_UPGRADE_DONE     */ L"अपग्रेड भयो, सेवा नयाँ बिल्डसँग पुनः सुरु भयो।",
    /* STR_UI_UNINSTALL_DONE   */ L"सेवा रोकी हटाइयो।\n\n"
        L"प्रोग्राम फाइल र लग ठाउँमै रहन्छन्, म्यानुअल रूपमा मेट्न सकिन्छ।",
    /* STR_UI_OP_FAILED_FMT    */ L"कारबाही असफल (त्रुटि %lu)।\n\nप्रशासकका रूपमा चलाइरहेको सुनिश्चित गर्नुहोस्।",
    /* STR_UI_CANCELLED        */ L"रद्द गरियो। कुनै परिवर्तन गरिएन।",
    /* STR_USAGE               */ L"प्रयोग:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    सेवा स्थापना गरी सुरु गर्ने (एडमिन चाहिन्छ)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  सेवा रोकी हटाउने (एडमिन चाहिन्छ)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      कन्सोल डिबग मोड\n"
        L"आर्गुमेन्टबिना चलाउँदा ग्राफिकल स्थापना/अपग्रेड/सेवा-हटाउने विज़ार्ड खुल्छ।",
};

// ---------------------------------------------------------------- si-LK ----

static const wchar_t* const kStrings_siLK[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"පද්ධති සේවාව ස්ථාපනය කරන්න",
    /* STR_UI_INSTALL_CONFIRM  */ L"මෙම වැඩසටහම Windows සේවාවක් ලෙස ස්ථාපනය වේ:\n\n"
        L"  · ස්ථානය: Program Files\n"
        L"  · බූට් වීමේදී ස්වයංක්‍රීයව ආරම්භ වේ\n"
        L"  · SYSTEM අවසරය සමඟ ක්‍රියාත්මක වේ, සියලුම පරිශීලකයන්ට බලපාය\n"
        L"  · Microsoft Pinyin හි ක්ලවුඩ් යෝජනා ස්ථිරව අක්‍රීයව තබයි\n\n"
        L"දිගටම කරද්දැ?",
    /* STR_UI_FOUND_INSTALLED  */ L"ස්ථාපිත බව හමුවිය",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"මෙම සේවාව දැනටමත් ස්ථාපිතයි.\n\n"
        L"「උපග්‍රේඩ්」— ස්ථාපිත පිටපත මෙම බිල්ඩ් එකෙන් ප්‍රතිස්ථාපනය කර සේවාව නැවත ආරම්භ කරයි\n"
        L"「සේවාව ඉවත් කරන්න」— සේවාව නවතා ඉවත් කරයි (වැඩසටහමේ ගොනු සහ ලොග් තබා ගනී)",
    /* STR_UI_BTN_UPGRADE      */ L"උපග්‍රේඩ්",
    /* STR_UI_BTN_UNINSTALL    */ L"සේවාව ඉවත් කරන්න",
    /* STR_UI_BTN_CANCEL       */ L"අවලංගු කරන්න",
    /* STR_UI_INSTALL_DONE     */ L"ස්ථාපනය විය, සේවාව ක්‍රියාත්මකයි.\n\n"
        L"දැන් සිට සියලුම පරිශීලකයන් සඳහා Microsoft Pinyin හි ක්ලවුඩ් සැකසුම් අක්‍රීයව තබා ගනී (රීබූට් වූ පසුද).",
    /* STR_UI_UPGRADE_DONE     */ L"උපග්‍රේඩ් විය, සේවාව නව බිල්ඩ් එකෙන් නැවත ආරම්භ විය.",
    /* STR_UI_UNINSTALL_DONE   */ L"සේවාව නවතා ඉවත් කරන ලදී.\n\n"
        L"වැඩසටහමේ ගොනු සහ ලොග් තැනේම තිබී අතින් මකා දැමිය හැක.",
    /* STR_UI_OP_FAILED_FMT    */ L"මෙහෙයුම අසාර්ථක විය (දෝෂය %lu).\n\nපරිපාලක ලෙස ක්‍රියාත්මක වන බව සහතික කරන්න.",
    /* STR_UI_CANCELLED        */ L"අවලංගු කරන ලදී. කිසිවක් වෙනස් කර නොමැත.",
    /* STR_USAGE               */ L"භාවිතය:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    සේවාව ස්ථාපනය කර ආරම්භ කරයි (admin අවශ්‍යයි)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  සේවාව නවතා ඉවත් කරයි (admin අවශ්‍යයි)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      කොන්සෝල් ඩීබග් ප්‍රකාරය\n"
        L"විකල්ප නොමැතිව ධාවනය කළොත් ග්‍රැෆික් ස්ථාපන/උපග්‍රේඩ්/සේවාව-ඉවත් කිරීමේ මායාකාරිය විවෘත වේ.",
};

// ---------------------------------------------------------------- my-MM ----

static const wchar_t* const kStrings_myMM[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"စနစ် ဝန်ဆောင်မှု ထည့်သွင်းခြင်း",
    /* STR_UI_INSTALL_CONFIRM  */ L"ဤပရိုဂရမ်ကို Windows ဝန်ဆောင်မှု အဖြစ် ထည့်သွင်းမည်:\n\n"
        L"  · တည်နေရာ: Program Files\n"
        L"  · ကွန်ပျူတာ စတင်ချိန်တွင် အလိုအလျောက် စတင်သည်\n"
        L"  · SYSTEM ခွင့်ပြုချက်ဖြင့် လည်ပတ်ပြီး အသုံးပြုသူ အားလုံးကို သက်ရောက်သည်\n"
        L"  · Microsoft Pinyin ၏ cloud အကြံပြုချက်များကို အမြဲပိတ်ထားသည်\n\n"
        L"ဆက်လက် လုပ်ဆောင်မလား?",
    /* STR_UI_FOUND_INSTALLED  */ L"ထည့်သွင်းထားသည်ကို တွေ့ရှိသည်",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"ဤဝန်ဆောင်မှုကို ထည့်သွင်းထားပြီးဖြစ်သည်။\n\n"
        L"「မွမ်းမံ」— ထည့်သွင်းထားသော မိတ္တူကို ဤဗားရှင်းဖြင့် အစားထိုးပြီး ဝန်ဆောင်မှုကို ပြန်စမည်\n"
        L"「ဝန်ဆောင်မှု ဖယ်ရှား」— ဝန်ဆောင်မှုကို ရပ်တန့်ပြီး ဖယ်ရှားမည် (ပရိုဂရမ်ဖိုင်များနှင့် log များကို ထားရှိမည်)",
    /* STR_UI_BTN_UPGRADE      */ L"မွမ်းမံ",
    /* STR_UI_BTN_UNINSTALL    */ L"ဝန်ဆောင်မှု ဖယ်ရှား",
    /* STR_UI_BTN_CANCEL       */ L"ပယ်ဖျက်",
    /* STR_UI_INSTALL_DONE     */ L"ထည့်သွင်းပြီး၊ ဝန်ဆောင်မှု စတင်နေပြီ။\n\n"
        L"ယခုမှစ၍ အသုံးပြုသူ အားလုံးအတွက် Microsoft Pinyin ၏ cloud ဆက်တင်များကို ပိတ်အတိုင်း တင်းကျပ်ထားမည် (ပြန်စတင်ပြီးနောက်လည်း)။",
    /* STR_UI_UPGRADE_DONE     */ L"မွမ်းမံပြီး၊ ဝန်ဆောင်မှုကို ဗားရှင်းအသစ်ဖြင့် ပြန်စခဲ့သည်။",
    /* STR_UI_UNINSTALL_DONE   */ L"ဝန်ဆောင်မှုကို ရပ်တန့်ပြီး ဖယ်ရှားပြီး။\n\n"
        L"ပရိုဂရမ်ဖိုင်များနှင့် log များသည် မူလနေရာတွင် ကျန်ရှိနေမည်၊ လက်ဖြင့် ဖျက်နိုင်သည်။",
    /* STR_UI_OP_FAILED_FMT    */ L"လုပ်ဆောင်မှု မအောင်မြင်ပါ (အမှား %lu)။\n\nစီမံခန့်ခွဲသူ အဖြစ် လည်ပတ်နေကြောင်း သေချာအောင် လုပ်ပါ။",
    /* STR_UI_CANCELLED        */ L"ပယ်ဖျက်လိုက်သည်။ မည်သည့်အပြောင်းအလဲမှ မရှိခဲ့ပါ။",
    /* STR_USAGE               */ L"အသုံးပြုပုံ:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    ဝန်ဆောင်မှုကို ထည့်သွင်းပြီး စတင်သည် (admin လိုအပ်)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  ဝန်ဆောင်မှုကို ရပ်တန့်ပြီး ဖယ်ရှားသည် (admin လိုအပ်)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      console debug မုဒ်\n"
        L"အာဂျူမင့်မပါ လည်ပတ်ပါက ဂရာဖစ် ထည့်သွင်း/မွမ်းမံ/ဝန်ဆောင်မှု-ဖယ်ရှား လမ်းညွှန် ပွင့်လာမည်",
};

// ---------------------------------------------------------------- km-KH ----

static const wchar_t* const kStrings_kmKH[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"ដំឡើងសេវាប្រព័ន្ធ",
    /* STR_UI_INSTALL_CONFIRM  */ L"កម្មវិធីនេះនឹងត្រូវបានដំឡើងជាសេវាកម្ម Windows៖\n\n"
        L"  · ទីតាំង៖ Program Files\n"
        L"  · ចាប់ផ្តើមស្វ័យប្រវត្តិពេលបើកគ្រឿង\n"
        L"  · ដំណើរការដោយសិទ្ធិ SYSTEM អនុវត្តចំពោះអ្នកប្រើប្រាស់ទាំងអស់\n"
        L"  · បិទមិនឲ្យដំណើរការការណែនាំពពករបស់ Microsoft Pinyin ជារៀងរហូត\n\n"
        L"បន្តទេ?",
    /* STR_UI_FOUND_INSTALLED  */ L"រកឃើញការដំឡើងរួច",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"សេវាកម្មនេះត្រូវបានដំឡើងរួចហើយ។\n\n"
        L"「ធ្វើបច្ចុប្បន្នភាព」— ជំនួសចម្លងដែលបានដំឡើងដោយកំណែនេះ រួចចាប់ផ្តើមសេវាកម្មឡើងវិញ\n"
        L"「ដកសេវាកម្មចេញ」— បញ្ឈប់ និងដកសេវាកម្មចេញ (រក្សាទុកឯកសារកម្មវិធី និង log)",
    /* STR_UI_BTN_UPGRADE      */ L"ធ្វើបច្ចុប្បន្នភាព",
    /* STR_UI_BTN_UNINSTALL    */ L"ដកសេវាកម្មចេញ",
    /* STR_UI_BTN_CANCEL       */ L"បោះបង់",
    /* STR_UI_INSTALL_DONE     */ L"ដំឡើងរួចរាល់ សេវាកម្មកំពុងដំណើរការ។\n\n"
        L"ចាប់ពីពេលនេះតទៅ ការកំណត់ពពករបស់ Microsoft Pinyin នឹងត្រូវបានបង្ខំឲ្យបិទសម្រាប់អ្នកប្រើប្រាស់ទាំងអស់ (រួមទាំងបន្ទាប់ពីចាប់ផ្តើមឡើងវិញ)។",
    /* STR_UI_UPGRADE_DONE     */ L"ធ្វើបច្ចុប្បន្នភាពរួចរាល់ សេវាកម្មត្រូវបានចាប់ផ្តើមឡើងវិញដោយកំណែថ្មី។",
    /* STR_UI_UNINSTALL_DONE   */ L"សេវាកម្មត្រូវបានបញ្ឈប់ និងដកចេញ។\n\n"
        L"ឯកសារកម្មវិធី និង log នៅដដែល អាចលប់ដោយខ្លួនឯងបាន។",
    /* STR_UI_OP_FAILED_FMT    */ L"បរាជ័យ (កំហុស %lu)។\n\nសូមបញ្ជាក់ថាអ្នកកំពុងដំណើរការជាអ្នកគ្រប់គ្រង។",
    /* STR_UI_CANCELLED        */ L"បានបោះបង់។ មិនមានការផ្លាស់ប្តូរអ្វីទេ។",
    /* STR_USAGE               */ L"ការប្រើប្រាស់៖\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    ដំឡើង និងចាប់ផ្តើមសេវាកម្ម (ត្រូវការ admin)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  បញ្ឈប់ និងដកសេវាកម្មចេញ (ត្រូវការ admin)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      មុខងារ debug ក្នុង console\n"
        L"បើដំណើរការដោយគ្មានអាគុយម៉ង់ នឹងបើកជំនួយក្រាហ្វិកដំឡើង/ធ្វើបច្ចុប្បន្នភាព/ដកសេវាកម្មចេញ។",
};

// ---------------------------------------------------------------- lo-LA ----

static const wchar_t* const kStrings_loLA[STR_COUNT] = {
    /* STR_APP_NAME            */ L"FuckMSIME-CHS-Bing-Suggestion",
    /* STR_UI_INSTALL_TITLE    */ L"ຕິດຕັ້ງບໍລິການລະບົບ",
    /* STR_UI_INSTALL_CONFIRM  */ L"ໂປຣແກຣມນີ້ຈະຖືກຕິດຕັ້ງເປັນບໍລິການຂອງ Windows:\n\n"
        L"  · ຕຳແໜ່ງ: Program Files\n"
        L"  · ເມື່ອເປີດເຄື່ອງຈະເລີ່ມເອງອັດຕະໂນມັດ\n"
        L"  · ເຮັດວຽກດ້ວຍສິດ SYSTEM ກວມເອົາຜູ້ໃຊ້ທຸກຄົນ\n"
        L"  · ບັງຄັບປິດຄຳແນະນຳຄລາວຂອງ Microsoft Pinyin ຖາວອນ\n\n"
        L"ສືບຕໍ່ບໍ?",
    /* STR_UI_FOUND_INSTALLED  */ L"ພົບການຕິດຕັ້ງຢູ່ແລ້ວ",
    /* STR_UI_UPGRADE_OR_REMOVE */ L"ບໍລິການນີ້ຕິດຕັ້ງຢູ່ແລ້ວ.\n\n"
        L"「ອັບເກດ」— ປ່ຽນສະບັບທີ່ຕິດຕັ້ງໄວ້ດ້ວຍສະບັບນີ້ແລ້ວຣີສະຕາດບໍລິການ\n"
        L"「ຖອນບໍລິການ」— ຢຸດ ແລະ ຖອນບໍລິການອອກ (ໄຟລ໌ໂປຣແກຣມ ແລະ log ຈະຖືກເກັບໄວ້)",
    /* STR_UI_BTN_UPGRADE      */ L"ອັບເກດ",
    /* STR_UI_BTN_UNINSTALL    */ L"ຖອນບໍລິການ",
    /* STR_UI_BTN_CANCEL       */ L"ຍົກເລີກ",
    /* STR_UI_INSTALL_DONE     */ L"ຕິດຕັ້ງສຳເລັດ ບໍລິການເລີ່ມເຮັດວຽກແລ້ວ.\n\n"
        L"ຈາກນີ້ໄປ ການຕັ້ງຄ່າຄລາວຂອງ Microsoft Pinyin ຂອງຜູ້ໃຊ້ທຸກຄົນຈະຖືກບັງຄັບໃຫ້ປິດຢູ່ສະເໝີ (ລວມທັງຫຼັງຣີບູດ).",
    /* STR_UI_UPGRADE_DONE     */ L"ອັບເກດສຳເລັດ ບໍລິການໄດ້ຣີສະຕາດດ້ວຍສະບັບໃໝ່ແລ້ວ.",
    /* STR_UI_UNINSTALL_DONE   */ L"ຢຸດ ແລະ ຖອນບໍລິການອອກແລ້ວ.\n\n"
        L"ໄຟລ໌ໂປຣແກຣມ ແລະ log ຍັງຢູ່ບ່ອນດຽວກັນ ສາມາດລຶບດ້ວຍຕົນເອງໄດ້.",
    /* STR_UI_OP_FAILED_FMT    */ L"ການດຳເນີນການລົ້ມເຫຼວ (ຂໍ້ຜິດພາດ %lu).\n\nກະລຸນາກວດສອບວ່າກຳລັງເຮັດວຽກໃນຖານະຜູ້ດູແລລະບົບ.",
    /* STR_UI_CANCELLED        */ L"ຍົກເລີກແລ້ວ ບໍ່ມີການປ່ຽນແປງໃດໆ.",
    /* STR_USAGE               */ L"ວິທີໃຊ້:\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe install    ຕິດຕັ້ງ ແລະ ເລີ່ມບໍລິການ (ຕ້ອງມີສິດ admin)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe uninstall  ຢຸດ ແລະ ຖອນບໍລິການ (ຕ້ອງມີສິດ admin)\n"
        L"  FuckMSIME-CHS-Bing-Suggestion.exe debug      ໂໝດ debug ແບບ console\n"
        L"ຖ້າເຮັດວຽກໂດຍບໍ່ໃສ່ອາກິວເມັນ ຈະເປີດຕົວຊ່ວຍຕິດຕັ້ງ/ອັບເກດ/ຖອນບໍລິການແບບກາຟຟິກ.",
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
    { 0x0404, kStrings_zhTW },   // zh-TW  Chinese (Traditional)
    { 0x0411, kStrings_jaJP },   // ja-JP  Japanese
    { 0x0412, kStrings_koKR },   // ko-KR  Korean
    { 0x0439, kStrings_hiIN },   // hi-IN  Hindi
    { 0x0445, kStrings_bnBD },   // bn-BD  Bengali
    { 0x0420, kStrings_urPK },   // ur-PK  Urdu
    { 0x0461, kStrings_neNP },   // ne-NP  Nepali
    { 0x045B, kStrings_siLK },   // si-LK  Sinhala
    { 0x041E, kStrings_thTH },   // th-TH  Thai
    { 0x042A, kStrings_viVN },   // vi-VN  Vietnamese
    { 0x0421, kStrings_idID },   // id-ID  Indonesian
    { 0x043E, kStrings_msMY },   // ms-MY  Malay
    { 0x0464, kStrings_filPH },  // fil-PH Filipino
    { 0x0455, kStrings_myMM },   // my-MM  Burmese
    { 0x0453, kStrings_kmKH },   // km-KH  Khmer
    { 0x0454, kStrings_loLA },   // lo-LA  Lao
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
