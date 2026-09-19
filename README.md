# FuckMSIME-CHS-Bing-Suggestion

[![CI](https://github.com/Creeper23456/FuckMSIME-CHS-Bing-Suggestion/actions/workflows/ci.yml/badge.svg)](https://github.com/Creeper23456/FuckMSIME-CHS-Bing-Suggestion/actions/workflows/ci.yml)
[![CodeQL](https://github.com/Creeper23456/FuckMSIME-CHS-Bing-Suggestion/actions/workflows/codeql.yml/badge.svg)](https://github.com/Creeper23456/FuckMSIME-CHS-Bing-Suggestion/actions/workflows/codeql.yml)

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
注意 `build.bat` 固定传 `/utf-8`：源码与字符串表均为 UTF-8，缺了这个参数
cl 会按系统 ANSI 代码页（GBK 等）解码源文件，**编译期**就把所有非 ASCII
界面文案变成乱码（这正是「英文界面也乱码」的根因——英文表里的 `—`、`·`）。

## 使用

**双击即用**：程序内嵌 requireAdministrator 清单，双击必过 UAC——

- 未安装：弹窗确认「即将安装系统服务…是否继续？」→ 确认后复制自身到
  `Program Files`，注册为自动启动服务并立即启动
- 已安装：弹出向导「检测到已安装」，可选 **升级**（用当前程序替换已装版本
  并重启服务）或 **移除服务**（停止并移除，**不删**程序文件与日志，可手动清理）

命令行模式同样可用：

```bat
FuckMSIME-CHS-Bing-Suggestion.exe install     :: 安装 + 启动（需管理员）
FuckMSIME-CHS-Bing-Suggestion.exe uninstall   :: 停止 + 移除（需管理员）
FuckMSIME-CHS-Bing-Suggestion.exe debug       :: 控制台调试模式（Ctrl+C 退出）
```

服务以 SYSTEM 身份运行，保护作用于**所有用户**；新用户首次登录自动建键钉死默认值。
服务停止/卸载即完全还原（不删任何东西）。

日志：`C:\ProgramData\FuckMSIME-CHS-Bing-Suggestion\FuckMSIME-CHS-Bing-Suggestion.log`

## 国际化

界面文案全部集中在 [`src/strings.h`](src/strings.h)（键值映射表，main.cpp 只引用
`STR_*` 键）。语言选择逻辑：先精确匹配用户 UI 语言的 LANGID，再回退到同主语言
（如 en-GB → en-US、uz-Latn → uz 表），最后英文兕底。

当前覆盖 29 个 locale / 27 种语言、28 张文案表：

- **联合国官方语言**：简体中文、英语、阿拉伯语、法语、俄语、西班牙语
- **东亚/南亚/东南亚/亚太**：繁体中文、日语、韩语、泰语、越南语、印尼语、马来语、
  菲律宾语（他加禄）、印地语、孟加拉语、乌尔都语、尼泊尔语、僧伽罗语、缅甸语、
  高棉语、老挝语
- **中亚**：哈萨克语、吉尔吉斯语、塔吉克语、土库曼语、乌兹别克语（西里尔/拉丁双注册）、
  蒙古语（西里尔）

新增语言 = 加一张表（14 个 `STR_*` 条目）+ 在 `kLocales` 里注册一行 LANGID。
构建必须带 `/utf-8`（`build.bat` 已固定传入），否则非 ASCII 文案在编译期就会乱码。

## CI / CD 与供应链

- **CI**（[`.github/workflows/ci.yml`](.github/workflows/ci.yml)）：push/PR 到 main 时在
  `windows-latest` 上用 `build.bat` 构建 → 计算 SHA-256 → 冒烟检查
  （x64 PE + requireAdministrator 清单内嵌）→ 上传 artifact
- **Release**（[`.github/workflows/release.yml`](.github/workflows/release.yml)）：推 `v*` tag 时构建并发布 Release，
  产物附 `sha256` 校验文件、CycloneDX SBOM（syft）、SLSA 构建来源证明与
  SBOM attestation（存于仓库 attestation store）

  ```sh
  gh attestation verify FuckMSIME-CHS-Bing-Suggestion.exe \
      -R Creeper23456/FuckMSIME-CHS-Bing-Suggestion
  ```

- **CodeQL**（[`.github/workflows/codeql.yml`](.github/workflows/codeql.yml)）：`security-extended`
  查询集，push/PR + 每周定时，结果在 Security 标签页
- **Dependabot**：每周跟进 workflow 内 Actions 版本
- 漏洞报告请走私密渠道，详见 [SECURITY.md](SECURITY.md)

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
