# uia-watch.ps1 - poll IME-related top-level windows; auto-capture any transient popup (ASCII only)
Add-Type -AssemblyName UIAutomationClient
Add-Type -AssemblyName UIAutomationTypes

$seen = @{}
$script:snap = 0

function Get-ImeWindows {
    $root = [System.Windows.Automation.AutomationElement]::RootElement
    return $root.FindAll([System.Windows.Automation.TreeScope]::Children, [System.Windows.Automation.Condition]::TrueCondition)
}

Write-Output "=== WATCH START (30s) ==="
for ($i = 0; $i -lt 60; $i++) {
    $wins = Get-ImeWindows
    foreach ($w in $wins) {
        $c = $w.Current
        $proc = try { (Get-Process -Id $c.ProcessId -ErrorAction Stop).ProcessName } catch { '?' }
        $key = "{0}|{1}|{2}" -f $c.NativeWindowHandle, $c.ClassName, $proc
        $isImeProc = $proc -match '^(ChsIME|TextInputHost|ctfmon)$'
        $isCoreWin = $c.ClassName -match 'CoreWindow|CHSIME|IME'
        if (($isImeProc -or $isCoreWin) -and -not $seen.ContainsKey($key)) {
            $seen[$key] = 1
            Write-Output ("[{0:HH:mm:ss.fff}] NEW WINDOW: proc={1} pid={2} class='{3}' name='{4}' hwnd={5}" -f (Get-Date), $proc, $c.ProcessId, $c.ClassName, $c.Name, $c.NativeWindowHandle)
            $all = $w.FindAll([System.Windows.Automation.TreeScope]::Descendants, [System.Windows.Automation.Condition]::TrueCondition)
            $n = 0
            foreach ($e in $all) {
                $el = $e.Current
                $r = $el.BoundingRectangle
                $x = 0; $y = 0; $wd = 0; $ht = 0
                try { $x = [int]$r.X } catch {}; try { $y = [int]$r.Y } catch {}; try { $wd = [int]$r.Width } catch {}; try { $ht = [int]$r.Height } catch {}
                Write-Output ("    ctl={0} id='{1}' name='{2}' rect=({3},{4} {5}x{6})" -f $el.ControlType.ProgrammaticName, $el.AutomationId, $el.Name, $x, $y, $wd, $ht)
                $n++
                if ($n -ge 120) { Write-Output "    ...truncated"; break }
            }
        }
    }
    Start-Sleep -Milliseconds 500
}
Write-Output "=== WATCH END ==="
Write-Output "distinct windows seen:"
$seen.Keys | ForEach-Object { Write-Output ("  " + $_) }
