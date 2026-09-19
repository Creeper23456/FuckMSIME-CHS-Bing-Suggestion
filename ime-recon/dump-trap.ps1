# dump-trap.ps1 - collect 4657 registry-audit events (elevated, ASCII only)
$ev = Get-WinEvent -FilterHashtable @{ LogName = 'Security'; Id = 4657 } -MaxEvents 50 -ErrorAction SilentlyContinue
$out = 'C:\Users\klp\AppData\Local\Temp\ime-recon\trap-events.txt'
if (-not $ev) { "NO 4657 EVENTS FOUND" | Out-File $out -Encoding utf8; exit }
$ev | ForEach-Object {
    $x = [xml]$_.ToXml()
    "===== $($_.TimeCreated) =====" | Out-File $out -Append -Encoding utf8
    $_.Message | Out-File $out -Append -Encoding utf8
}
Write-Output "dumped $($ev.Count) events to $out"
