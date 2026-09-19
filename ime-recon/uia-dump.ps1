# uia-dump.ps1 — identify host process + element tree of the on-screen promo popup
Add-Type -AssemblyName UIAutomationClient
Add-Type -AssemblyName UIAutomationTypes

$interesting = @()

$root = [System.Windows.Automation.AutomationElement]::RootElement
$children = $root.FindAll([System.Windows.Automation.TreeScope]::Children, [System.Windows.Automation.Condition]::TrueCondition)

Write-Output "=== 顶层窗口清单（IME 相关） ==="
foreach ($w in $children) {
    $name = $w.Current.Name
    $cls  = $w.Current.ClassName
    $pid  = $w.Current.ProcessId
    $proc = try { (Get-Process -Id $pid -ErrorAction Stop).ProcessName } catch { '?' }
    if ($proc -match 'ChsIME|TextInputHost|ctfmon' -or $name -match '输入|候选|搜索|建议|Bing|bing') {
        Write-Output ("[{0}] pid={1} proc={2} class={3} name={4}" -f $w.Current.NativeWindowHandle, $pid, $proc, $cls, $name)
        $interesting += $w
    }
}

Write-Output ""
Write-Output "=== 嫌疑窗口的元素树（深度 4） ==="
foreach ($w in $interesting) {
    Write-Output ("### WINDOW: {0} / {1} (pid {2})" -f $w.Current.Name, $w.Current.ClassName, $w.Current.ProcessId)
    $all = $w.FindAll([System.Windows.Automation.TreeScope]::Descendants, [System.Windows.Automation.Condition]::TrueCondition)
    $depth = 0
    foreach ($e in $all) {
        $c = $e.Current
        $r = $c.BoundingRectangle
        Write-Output ("  - ctl={0} id='{1}' name='{2}' rect=({3},{4},{5},{6})" -f $c.ControlType.ProgrammaticName, $c.AutomationId, $c.Name, [int]$r.X, [int]$r.Y, [int]$r.Width, [int]$r.Height)
        $depth++
        if ($depth -ge 200) { break }
    }
}
