# uia-dump.ps1 - identify host process + element tree of the on-screen promo popup (ASCII only)
Add-Type -AssemblyName UIAutomationClient
Add-Type -AssemblyName UIAutomationTypes

$interesting = @()
$root = [System.Windows.Automation.AutomationElement]::RootElement
$children = $root.FindAll([System.Windows.Automation.TreeScope]::Children, [System.Windows.Automation.Condition]::TrueCondition)

Write-Output "=== TOP-LEVEL WINDOWS (IME-related) ==="
foreach ($w in $children) {
    $name = $w.Current.Name
    $cls  = $w.Current.ClassName
    $wpid = $w.Current.ProcessId
    $proc = try { (Get-Process -Id $wpid -ErrorAction Stop).ProcessName } catch { '?' }
    if ($proc -match 'ChsIME|TextInputHost|ctfmon|SearchHost' -or $name -match 'Bing|bing|Input|Candidate|Suggest') {
        Write-Output ("hwnd={0} pid={1} proc={2} class={3} name={4}" -f $w.Current.NativeWindowHandle, $wpid, $proc, $cls, $name)
        $interesting += $w
    }
}

Write-Output ""
Write-Output "=== ELEMENT TREES (up to 200 each) ==="
foreach ($w in $interesting) {
    Write-Output ("### WINDOW: {0} / {1} (pid {2})" -f $w.Current.Name, $w.Current.ClassName, $w.Current.ProcessId)
    $all = $w.FindAll([System.Windows.Automation.TreeScope]::Descendants, [System.Windows.Automation.Condition]::TrueCondition)
    $n = 0
    foreach ($e in $all) {
        $c = $e.Current
        $r = $c.BoundingRectangle
        Write-Output ("  - ctl={0} id='{1}' name='{2}' rect=({3},{4},{5},{6})" -f $c.ControlType.ProgrammaticName, $c.AutomationId, $c.Name, [int]$r.X, [int]$r.Y, [int]$r.Width, [int]$r.Height)
        $n++
        if ($n -ge 200) { Write-Output "  ... (truncated)"; break }
    }
}
