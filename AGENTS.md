# AGENTS.md — FuckMSIME-CHS-Bing-Suggestion

> Agent 操作手册。任何 AI Agent 接手本仓库前必须先读完本文档，并遵守「操作规程」一节。

## 1. 项目目标

**保留微软拼音的本地输入能力，废掉 Bing 云候选、展开建议及其推广入口。**

验收标准（三项独立成立）：

1. 不再向云端请求建议（网络路径断掉）
2. 已缓存的云建议也不能进入候选列表（功能入口断掉）
3. 推广提示、展开建议、Bing 搜索入口失效（可用性判断断掉）

明确边界：只控制设置页不算达标；只隐藏窗口不算达标；只封今天的服务器域名不算达标。

## 2. 环境事实（2025 实测）

| 项目 | 值 |
|---|---|
| 系统 | Windows 11 24H2, build **26100.9457** |
| WSL | WSL2, Fedora 44, 互操作正常（powershell.exe / cmd.exe 可直呼） |
| MSVC | `E:\Program Files\Microsoft Visual Studio\18\Community\VC\Tools\MSVC\14.51.36231\bin\Hostx64\x64\` |
| Windows SDK | `C:\Program Files (x86)\Windows Kits\10\`（Include 22621/26100/28000） |
| 调试器 | Debugging Tools **未安装**（Debuggers\x64 仅剩 dbghelp/dbgcore/srcsrv/symsrv 四个 DLL） |
| shell 权限 | 非管理员；UAC 提权操作需用户点击（**已获用户授权**） |
| GitHub | `Creeper23456/FuckMSIME-CHS-Bing-Suggestion`（private, SSH） |

## 3. 静态侦察结论（已完成，只读）

目标模块目录：`C:\Windows\System32\InputMethod\CHS\`
全部模块版本 **10.0.26100.9278**。

### 3.1 网络路径归属（PE 导入表证据）

| 模块 | 导入的网络栈 | 结论 |
|---|---|---|
| **ChsProxyDS.dll** | **WINHTTP.dll** 完整链：`WinHttpOpen → WinHttpCrackUrl → WinHttpConnect → WinHttpOpenRequest → WinHttpSendRequest → WinHttpSetStatusCallback → WinHttpReceiveResponse → WinHttpQueryHeaders → WinHttpReadData → WinHttpCloseHandle`，另有 `WinHttpGetProxyForUrl` / `WinHttpGetIEProxyConfigForCurrentUser` | **云建议/Bing 请求路径，头号目标** |
| ChsLexiconUpdateDS.dll | WININET.dll + urlmon.dll | 词库更新，独立栈，次要目标 |
| 其余 (ChsIME.exe, ChsAdvancedDS, ChsRoaming, ChsPinyinDS, ChsEM) | 无直接网络导入 | 不直接联网 |

### 3.2 字符串证据（ChsProxyDS.dll，UTF-16LE）

```text
https://cn.bing.com
https://cloudsuggestion.chinacloudsites.cn
CloudUID / suggestion / Suggests / OnRequestBingTest
```

### 3.3 运行时目标（截至侦察时）

- `ChsIME.exe` PID 7576 — IME 引擎宿主，ChsProxyDS.dll 预期加载于此（待 cdb `lm` 确认）
- `TextInputHost.exe` PID 16048 — 共享 UI 宿主（**不要**对其实施全进程网络拒绝）

## 4. 执行计划

### Phase A — 动态采证（当前阶段，用户已授权 UAC）

1. **安装调试器**：下载 Windows SDK setup（winsdksetup.exe），静默安装 "Debugging Tools for Windows" 功能 → `cdb.exe`。UAC 由用户点击。
2. **符号配置**：`srv*C:\symbols*https://msdl.microsoft.com/download/symbols`（已获联网授权，仅下载微软公共符号）。
3. **会话框架**：`ime-recon/cdb-session.sh` — FIFO 驱动 cdb stdin，stdout 落日志，Agent 循环读日志 → 分析 → 写下一条命令。
4. **附加与断点**（`bu` 延迟解析）：

   ```text
   bu winhttp!WinHttpConnect     ".printf \"[CONNECT] \"; du @rdx; k; g"
   bu winhttp!WinHttpOpenRequest ".printf \"[OPENREQ] \"; du @r8; k; g"
   bu winhttp!WinHttpSendRequest ".printf \"[SEND] \"; k; g"
   ```

   x64 约定：WinHttpConnect 服务器名在 `RDX`，WinHttpOpenRequest 路径在 `R8`。无需 MITM 证书。
5. **触发**：用户在文本框用**虚构文本**打拼音、点开 Bing 建议。
6. **产出**：`logs/` 下的命中调用栈 + ChsProxyDS.dll 内 RVA 链 + 模块 SHA256 清单（版本钉死）。

### Phase B — 上移 Hook 层（另行授权后）

1. 对同版本 ChsProxyDS.dll 副本反汇编，从 WinHTTP 调用点沿 Phase A 调用栈向上追。
2. 优先找三类位置（按优先级）：
   - 云建议提供器的**启用判断**（始终走"不可用"分支）
   - 提供器的**注册/调度入口**（不加入候选来源）
   - 云结果**合并进候选列表**的入口（拒收云候选，保留本地）
3. 优先复用程序自身的"关闭功能"路径，而不是伪造空响应。
4. 若必须留在网络层且宿主共享：按"连接句柄→主机→请求句柄→来源标记"过滤，只拒绝已标记请求；处理并发与句柄复用。
5. 硬性断网兜底（可选）：WFP `FWPM_LAYER_ALE_AUTH_CONNECT_V4/V6`，按 `FwpmGetAppIdFromFileName0` 得到的 app id 加 `FWP_ACTION_BLOCK` 过滤器，调试期用 `FWPM_SESSION_FLAG_DYNAMIC`。
6. 交付形态：Windhawk mod（单文件 C++，`@include` 精确到实测宿主路径）或独立注入器 + Hook DLL（MSVC 14.51 工具链编译）。

## 5. 操作规程（强制）

### Git

- **原子化提交**：一个提交只做一件事（一个脚本、一份文档、一处修复）。提交信息用 `type: 摘要`（chore/docs/feat/fix/refactor）。
- 提交前 `git status` 确认无夹带文件；日志/符号/二进制产物一律不进库（.gitignore 已覆盖）。

### 安全边界

- 不修改 `%SystemRoot%` 下任何磁盘文件；不改注册表配置值来"假装关闭"。
- Hook 原型不区分地拒绝全部 WinHTTP 时，`@include` 必须钉死实测宿主路径，禁止随手扩到 TextInputHost.exe。
- 测试一律用虚构文本；日志提交前检查不含真实输入内容。
- 私有 RVA/偏移必须绑定模块版本 + SHA256；版本不匹配则拒绝应用并报告，禁止沿用旧偏移。

### 调试会话

- 附加对象：ChsIME.exe。断点命中期间该进程冻结（打字短暂卡顿属预期）。
- cdb 被强杀会带走 ChsIME.exe，系统自动重启之，无数据损失——但正常退出必须用 `q`。
- 每轮会话从干净状态开始：先禁用 mod/脚本 → 重启宿主 → 再启用 → 再触发。
- 回归清单（hook 落地后）：普通拼音、双拼、候选翻页、退格、中文标点、切换应用、组合文本提交、反复触发推广流程、睡眠恢复、宿主重启后的请求计数（拒绝后高频重试 = 未完成）。

## 6. 当前状态

- [x] 静态侦察（本文档第 3 节）
- [x] gh 建仓 + AGENTS.md
- [ ] Phase A-1: 安装 Debugging Tools（UAC）
- [ ] Phase A-2: cdb 会话框架
- [ ] Phase A-3: 附加 + 断点 + 符号
- [ ] Phase A-4: 触发采证，产出 RVA 链
- [ ] Phase B: hook 层决策与实现（另行授权）
