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
