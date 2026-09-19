# uia-diff2.ps1 - find Input Experience CoreWindow via EnumWindows, then UIA-walk from hwnd (ASCII only)
param([string]$mode)
Add-Type -AssemblyName UIAutomationClient
Add-Type -AssemblyName UIAutomationTypes
Add-Type @"
using System;
using System.Text;
using System.Runtime.InteropServices;
public class WFind {
    public static IntPtr Found = IntPtr.Zero;
    public delegate bool EnumWindowsProc(IntPtr hWnd, IntPtr lParam);
    [DllImport("user32.dll")] public static extern bool EnumWindows(EnumWindowsProc cb, IntPtr lp);
    [DllImport("user32.dll")] public static extern uint GetWindowThreadProcessId(IntPtr hWnd, out uint pid);
    [DllImport("user32.dll", CharSet=CharSet.Unicode)] public static extern int GetClassName(IntPtr hWnd, StringBuilder sb, int max);
    public static IntPtr FindClassForPid(string cls, uint wantPid) {
        Found = IntPtr.Zero;
        EnumWindows((h, l) => {
            uint pid; GetWindowThreadProcessId(h, out pid);
            if (pid == wantPid) {
                var sb = new StringBuilder(256); GetClassName(h, sb, 256);
                if (sb.ToString() == cls) { Found = h; return false; }
            }
            return true;
        }, IntPtr.Zero);
        return Found;
    }
}
"@

$tipid = (Get-Process -Name TextInputHost -ErrorAction SilentlyContinue | Select-Object -First 1).Id
if (-not $tipid) { Write-Output "ERR: TextInputHost not running"; exit 1 }
$hwnd = [WFind]::FindClassForPid('Windows.UI.Core.CoreWindow', [uint32]$tipid)
if ($hwnd -eq [IntPtr]::Zero) { Write-Output "ERR: CoreWindow not found for pid $tipid"; exit 1 }
Write-Output ("CoreWindow hwnd=0x{0:X} pid={1}" -f $hwnd.ToInt64(), $tipid)

$target = [System.Windows.Automation.AutomationElement]::FromHandle($hwnd)
$all = $target.FindAll([System.Windows.Automation.TreeScope]::Descendants, [System.Windows.Automation.Condition]::TrueCondition)
$set = @{}
foreach ($e in $all) {
    $c = $e.Current
    $r = $c.BoundingRectangle
    $x = 0; try { $x = [int]$r.X } catch {}
    $y = 0; try { $y = [int]$r.Y } catch {}
    $wd = 0; try { $wd = [int]$r.Width } catch {}
    $ht = 0; try { $ht = [int]$r.Height } catch {}
    if ($c.Name -ne '' -or $c.AutomationId -ne '') {
        $set["$($c.AutomationId)|$($c.Name)|$($c.ControlType.ProgrammaticName)|$x,$y,$wd,$ht"] = 1
    }
}

$file = "C:\Users\klp\AppData\Local\Temp\ime-recon\uiatree.$mode.txt"
$set.Keys | Out-File $file -Encoding utf8
Write-Output ("mode={0} elements={1} saved={2}" -f $mode, $set.Count, $file)
