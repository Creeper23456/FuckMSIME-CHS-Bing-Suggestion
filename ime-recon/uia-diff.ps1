# uia-diff.ps1 - baseline/diff mode: snapshot Windows Input Experience UIA tree; diff reveals popup elements (ASCII only)
param([string]$mode)
Add-Type -AssemblyName UIAutomationClient
Add-Type -AssemblyName UIAutomationTypes

$root = [System.Windows.Automation.AutomationElement]::RootElement
$wins = $root.FindAll([System.Windows.Automation.TreeScope]::Children, [System.Windows.Automation.Condition]::TrueCondition)
$target = $null
foreach ($w in $wins) {
    if ($w.Current.ClassName -eq 'Windows.UI.Core.CoreWindow' -and $w.Current.Name -eq 'Windows Input Experience') { $target = $w; break }
}
if (-not $target) { Write-Output "ERR: Input Experience window not found"; exit 1 }

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
