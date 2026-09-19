# 状态层侦察发现 — CHS IME 云建议/弹窗开关

系统: Windows 11 24H2 build 26100.9457
模块版本: ChsIME 全家桶 10.0.26100.9278

## 核心开关（实测值）

```reg
[HKEY_CURRENT_USER\Software\Microsoft\InputMethod\Settings\CHS]
"Enable Dynamic Candidate Ranking"=REG_DWORD 0x1
"Enable Cloud Candidate"=REG_DWORD 0x1        ; 云候选总开关 → 目标 0
"EnableExtraDomainType"=REG_DWORD 0x1
"SmartFuzzyPairTriggerCount"=REG_SZ (统计,勿动)
"Enable self-learning"=REG_DWORD 0x1
"EnableSmartSelfLearning"=REG_DWORD 0x1
"EnableLiveSticker"=REG_DWORD 0x0
"Enable EUDP"=REG_DWORD 0x1                   ; 含义待查(疑上传协议) → 观察
"AutoShowCloudSuggestion"=REG_DWORD 0x1       ; 自动展开云建议/弹窗驱动 → 目标 0
```

## 处置记录

- 2025-XX-XX: `Enable Cloud Candidate` 与 `AutoShowCloudSuggestion` 已置 0（原值均为 0x1，备份即本文档）
- 待验证: 用户打字触发 → (a) 弹窗是否仍现 (b) 值是否被翻回
- 若翻回: 对键 `HKCU\Software\Microsoft\InputMethod\Settings\CHS` 加 Deny SetValue ACE（用户 SID）
  - 副作用边界: 仅键内统计值(SmartFuzzyPairTriggerCount)无法持久化；自学习数据在文件侧不受影响
  - 回滚: 移除 ACE

## 其他相关键

- `HKCU\Software\Microsoft\InputMethod\Siuf\*` — 候选选中计数遥测，无关紧要
- `HKLM\SOFTWARE\Policies\Microsoft\Input` — 不存在（无现成策略落点）
- `HKCU\Software\Microsoft\Input\tsf\tsf3override\{CLSID}` — TSF profile 覆盖，含 ChsIME GUID 系
- CBS(TextInputHost) 侧弹窗状态若涉入，查 `%LocalAppData%\Packages\MicrosoftWindows.Client.CBS_cw5n1h2txyewy\Settings\settings.dat`

## 关联事实（来自静态侦察）

- 云建议网络调用链: ChsProxyDS.dll（WinHTTP: cn.bing.com, cloudsuggestion.chinacloudsites.cn）
- ChsIME 实例模型: 常驻服务实例(不联网) + 短命组字实例(联网, 受保护, 附着困难)
- 组字实例孵化时机与 7576 被冻结相关；健康状态下未见孵化

## 决定性证据（4657 审计，2025-09-19 19:50-19:52）

```
19:50:09  TextInputHost.exe (SystemApps\MicrosoftWindows.Client.CBS) 把 Enable Cloud Candidate 0→1
19:51:09  SystemSettings.exe (ImmersiveControlPanel)              把 Enable Cloud Candidate 1→0
19:52:06  TextInputHost.exe                                        0→1 再次翻转
```

结论: 推广弹窗出现即由 TextInputHost 直接改写设置值（所谓"绕过组策略"即此）。

## 处置（已生效）

- `HKCU\Software\Microsoft\InputMethod\Settings\CHS` 键挂 Deny SetValue ACE（SID S-1-5-21-...-1001）
- 写入验证: UnauthorizedAccess ✓，值钉死 0 ✓
- 回滚方法: 提权移除该 Deny ACE（acl-deny3.ps1 反向操作）
- 注意: 本用户一切进程(含自己)都不可再写此键；仅删 ACE 可解

## 待观察

- 弹窗是否仍出现（其"启用"动作已失效）
- 若仍出现且烦人 → 下一步定位其展示状态（CBS settings.dat / CloudStore，均未捕获到点击期写入）

## 最终战报（Windhawk mod v0.2.0）

- v0.1 (RegSetValueExW) 零命中 → 实锤 CBS 组件**直接调 ntdll!NtSetValueKey**，绕过 win32 注册表包装层
- v0.2 下沉 NtSetValueKey + 大小写不敏感：弹窗触发期 **13 次写入尝试全部 STATUS_ACCESS_DENIED**（DbgView 实录）
- 值钉死 0；TextInputHost 只拦两个值名，其余写入与全系统其他进程不受影响
- 回滚 = Windhawk 里停用 mod

### 经验教训
1. 抓写入者：SACL 审计 (auditpol 0CCE921E) + 4657 事件是免调试器的决定性手段
2. hook CBS/输入体验类组件必须下到 ntdll 原生 API，win32 层会被绕过
3. .NET ACL API 的枚举/SDDL 读取对含 Deny 的键行为不稳，直接用 SDDL 字符串最可靠
