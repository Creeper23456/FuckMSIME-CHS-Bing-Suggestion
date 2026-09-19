# FuckMSIME-CHS-Bing-Suggestion

**Windows 服务：让微软拼音（CHS IME）的 Bing 云候选永久保持关闭，开机自启，全员生效。**

## 背景

Windows 11 24H2 上，`TextInputHost.exe`（Windows 输入体验）会在推广弹窗触发时把
`HKCU\Software\Microsoft\InputMethod\Settings\CHS` 下的
`Enable Cloud Candidate` 与 `AutoShowCloudSuggestion` 直接改回 `1`——
绕过设置页开关，也绕过组策略（注册表审计 4657 已实锤，见 `test` 分支取证记录）。

本服务以 SYSTEM 身份常驻，监视所有已加载用户配置单元（HKU）中的该键，
通过 `RegNotifyChangeKeyValue` 的**内核推送通知**在值被改写的瞬间摁回 `0`。
开机自启、多用户通吃、CPU 占用趋近于零。

## 构建

需要 MSVC（本机为 `E:\Program Files\Microsoft Visual Studio\18\Community`）：

```bat
build.bat
```

产物：`build\FuckMSIME-CHS-Bing-Suggestion.exe`（静态链接 /MT，单文件可部署）。

## 使用（需管理员）

```bat
FuckMSIME-CHS-Bing-Suggestion.exe install     :: 安装为自动启动服务并立即启动
FuckMSIME-CHS-Bing-Suggestion.exe uninstall   :: 停止并卸载服务
FuckMSIME-CHS-Bing-Suggestion.exe debug       :: 控制台调试模式（Ctrl+C 退出）
```

日志：`C:\ProgramData\FuckMSIME-CHS-Bing-Suggestion\FuckMSIME-CHS-Bing-Suggestion.log`

## 工作原理

```text
用户登录 → 配置单元加载 → 服务 5s 内发现并挂 RegNotifyChangeKeyValue
TextInputHost 写 Enable Cloud Candidate = 1
        ↓ 内核通知（毫秒级）
服务回写 0（日志记录）
```

- 只监视/改写两个值名，其他设置一概不碰
- 新用户首次登录自动建键并钉死默认值
- 服务停止/卸载即完全还原（不删任何东西）

## 已知边界

- 反应式防护：从写入到回写存在毫秒级窗口，极端情况下当次组字可能闪现云候选
- 不拦截云建议的网络请求本体（静态分析确认其走 `ChsProxyDS.dll` 的 WinHTTP；
  如需断网级保证，叠加防火墙规则或 `test` 分支的 Windhawk hook 方案）
- Windows 大版本更新可能改变 IME 组件结构，需回归验证

## 分支说明

- `main`：本项目（正式服务）
- `test`：侦察过程全记录——静态逆向、4657 注册表审计取证、Windhawk
  NtSetValueKey hook 原型及其 13 连拒实录

## 许可证

本项目以 [GPL-3.0](LICENSE) 授权发布。
