# 安全策略 / Security Policy

## 受支持版本 / Supported Versions

| 版本 | 支持情况 |
| --- | --- |
| 最新 tag（`v*` Release） | ✅ 安全修复 |
| `main` 分支 | ✅ 开发中 |
| 更早的 tag / commit | ❌ 请升级 |

## 如何报告漏洞 / Reporting a Vulnerability

**请勿使用公开 issue 报告安全问题。**

请通过 GitHub 的私密漏洞报告通道提交：
仓库页 → **Security** → **Report a vulnerability**，
或直接联系仓库维护者（私下渠道）。

报告请尽量包含：

- 受影响的版本 / commit（Release 附件请附其 SHA-256）
- 环境信息：Windows 版本/构建号、是否域环境、账户类型
- 复现步骤或 PoC（最小化最好）
- 影响评估：谁能利用、能造成什么后果

### 响应目标

| 阶段 | 目标时长 |
| --- | --- |
| 确认收到 | 72 小时内 |
| 初步评估（是否有效、严重级别） | 7 天内 |
| 修复发布 | 随下一个 patch tag；高危加快 |
| 公开披露 | 与修复同步，协调披露窗口 90 天 |

## 范围界定 / Scope

本项目是一个**以 SYSTEM 身份运行的服务**，安装与控制均要求管理员批准。
以下属于**设计行为，不视为漏洞**：

- 双击触发 UAC（`requireAdministrator` 清单）、SCM 操作需要高权限——这是前提而非缺陷；
- 服务以 SYSTEM 身份读写 `HKU\<SID>\...\Settings\CHS` 下的两个注册表值、
  在 `ProgramData` 写日志——这就是本程序的功能本体；
- 服务停止/移除不删除程序文件与日志（向导文案与 README 已明确说明）；
- 防护是反应式的：内核通知到回写之间存在毫秒级窗口（见 README「已知边界」）。

### 历史加固记录

外部评审提出的 Low/hardening 项均已修复，可作为「已知已处理」参考：

- 升级逻辑只覆盖规范化安装路径，不信任 SCM 中的可变 ImagePath
  （commit `90e9900`）
- 服务 ImagePath 解析容忍带参、无引号、损坏引号（commit `91079b6`）
- 超过 WFMO 等待集上限的用户 hive 由 5 秒轮询兜底（commit `f9ac0d0`）

## 供应链 / Supply Chain

Release 产物由 GitHub Actions 在 tag 上构建，附带：

- `*.sha256` — sha256sum 格式校验文件
- `*.cdx.json` — CycloneDX SBOM
- **SLSA 构建来源证明**与 **SBOM attestation**（存于仓库 attestation store）

验证方式：

```sh
# 校验摘要
sha256sum -c FuckMSIME-CHS-Bing-Suggestion.exe.sha256

# 校验 attestation（需要 gh CLI，登录后离线可验）
gh attestation verify FuckMSIME-CHS-Bing-Suggestion.exe \
    -R Creeper23456/FuckMSIME-CHS-Bing-Suggestion
```

安全扫描：CodeQL（`security-extended` 查询集，每次 push/PR + 每周定时）
结果见仓库 **Security** 标签页；Actions 依赖由 Dependabot 每周跟进更新。
