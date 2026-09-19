# win32-watch2.ps1 - fast EnumWindows watcher with pid cache, output streamed to file (ASCII only)
Add-Type @"
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;
public class WinEnum2 {
    public static HashSet<uint> TargetPids = new HashSet<uint>();
    public static Dictionary<uint, string> ProcCache = new Dictionary<uint, string>();
    public static List<string> Out = new List<string>();

    [DllImport("user32.dll")] public static extern bool EnumWindows(EnumWindowsProc cb, IntPtr lp);
    public delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);
    [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint pid);
    [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr hWnd, StringBuilder sb, int max);
    [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr hWnd, StringBuilder sb, int max);
    [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr hWnd);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT r);

    public static void Snap() {
        lock(Out) {
            EnumWindows((h, l) => {
                uint pid; GetWindowThreadProcessId(h, out pid);
                if (!TargetPids.Contains(pid)) return true;
                bool vis = IsWindowVisible(h);
                var sb = new StringBuilder(256); GetClassName(h, sb, 256);
                var tb = new StringBuilder(256); GetWindowText(h, tb, 256);
                RECT r; GetWindowRect(h, out r);
                Out.Add(string.Format("TOP hwnd=0x{0:X} pid={1} class='{2}' text='{3}' rect=({4},{5},{6},{7}) vis={8}",
                    h.ToInt64(), pid, sb, tb, r.L, r.T, r.R, r.B, vis));
                return true;
            }, IntPtr.Zero);
        }
    }
}
"@

$pids = @{}
foreach ($n in 'ChsIME','TextInputHost','ctfmon') {
    foreach ($p in (Get-Process -Name $n -ErrorAction SilentlyContinue)) { $pids[[uint32]$p.Id] = 1 }
}
[WinEnum2]::TargetPids = New-Object 'System.Collections.Generic.HashSet[uint32]'
foreach ($k in $pids.Keys) { [WinEnum2]::TargetPids.Add($k) | Out-Null }

Write-Output ("targets: " + ([string]::Join(',', ([WinEnum2]::TargetPids))))

$baseline = @{}
for ($i = 0; $i -lt 60; $i++) {
    [WinEnum2]::Snap()
    foreach ($line in [WinEnum2]::Out) {
        if (-not $baseline.ContainsKey($line)) {
            $baseline[$line] = 1
            Write-Output ("[{0:HH:mm:ss.fff}] {1}" -f (Get-Date), $line)
        }
    }
    [WinEnum2]::Out.Clear()
    Start-Sleep -Milliseconds 450
}
Write-Output "=== END, distinct lines: $($baseline.Count) ==="
