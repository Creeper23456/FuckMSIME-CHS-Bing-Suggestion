# win32-watch.ps1 - EnumWindows-based watcher: any top-level/child window belonging to IME processes (ASCII only)
Add-Type @"
using System;
using System.Text;
using System.Collections.Generic;
using System.Runtime.InteropServices;
public class WinEnum {
    [DllImport("user32.dll")] public static extern bool EnumWindows(EnumWindowsProc cb, IntPtr lp);
    [DllImport("user32.dll")] public static extern bool EnumChildWindows(IntPtr hwnd, EnumWindowsProc cb, IntPtr lp);
    public delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);
    [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint pid);
    [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr hWnd, StringBuilder sb, int max);
    [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetWindowText(IntPtr hWnd, StringBuilder sb, int max);
    [DllImport("user32.dll")] public static extern bool IsWindowVisible(IntPtr hWnd);
    [StructLayout(LayoutKind.Sequential)] public struct RECT { public int L, T, R, B; }
    [DllImport("user32.dll")] public static extern bool GetWindowRect(IntPtr hWnd, out RECT r);

    public static List<string> Snap() {
        var found = new List<string>();
        EnumWindows((h, l) => {
            uint pid; GetWindowThreadProcessId(h, out pid);
            var info = Describe(h, pid);
            if (info != null) {
                found.Add(info);
                EnumChildWindows(h, (ch, l2) => {
                    uint cpid; GetWindowThreadProcessId(ch, out cpid);
                    var ci = DescribeChild(ch, cpid);
                    if (ci != null) found.Add(ci);
                    return true;
                }, IntPtr.Zero);
            }
            return true;
        }, IntPtr.Zero);
        return found;
    }
    static string ProcName(uint pid) {
        try {
            var p = System.Diagnostics.Process.GetProcessById((int)pid);
            return p.ProcessName;
        } catch { return "?"; }
    }
    static string Describe(IntPtr h, uint pid) {
        string proc = ProcName(pid);
        if (!(proc == "ChsIME" || proc == "TextInputHost" || proc == "ctfmon")) return null;
        var sb = new StringBuilder(256); GetClassName(h, sb, 256);
        var tb = new StringBuilder(256); GetWindowText(h, tb, 256);
        RECT r; GetWindowRect(h, out r);
        return string.Format("TOP hwnd=0x{0:X} proc={1} pid={2} class='{3}' text='{4}' rect=({5},{6},{7},{8}) vis={9}",
            h.ToInt64(), proc, pid, sb, tb, r.L, r.T, r.R, r.B, IsWindowVisible(h));
    }
    static string DescribeChild(IntPtr h, uint pid) {
        string proc = ProcName(pid);
        if (!(proc == "ChsIME" || proc == "TextInputHost")) return null;
        var sb = new StringBuilder(256); GetClassName(h, sb, 256);
        var tb = new StringBuilder(256); GetWindowText(h, tb, 256);
        RECT r; GetWindowRect(h, out r);
        return string.Format("  CHILD hwnd=0x{0:X} proc={1} class='{2}' text='{3}' rect=({4},{5},{6},{7}) vis={8}",
            h.ToInt64(), proc, sb, tb, r.L, r.T, r.R, r.B, IsWindowVisible(h));
    }
}
"@

Write-Output "=== WIN32 WATCH START (30s) ==="
$baseline = @{}
for ($i = 0; $i -lt 75; $i++) {
    $snap = [WinEnum]::Snap()
    foreach ($line in $snap) {
        if (-not $baseline.ContainsKey($line)) {
            $baseline[$line] = 1
            Write-Output ("[{0:HH:mm:ss.fff}] {1}" -f (Get-Date), $line)
        }
    }
    Start-Sleep -Milliseconds 400
}
Write-Output "=== WATCH END, distinct: $($baseline.Count) ==="
