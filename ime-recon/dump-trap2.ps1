# dump-trap2.ps1 - full diagnostics + wider event sweep (elevated, ASCII only)
$out = 'C:\Users\klp\Appdata\Local\Temp\ime-recon\trap-events.txt'
Remove-Item $out -ErrorAction SilentlyContinue

"=== AUDITPOL Registry subcategory ===" | Out-File $out -Append -Encoding utf8
auditpol /get /subcategory:{0CCE921F-69AE-11D9-BED3-505054503030} | Out-File $out -Append -Encoding utf8

"=== SACL of HKCU InputMethod (elevated view) ===" | Out-File $out -Append -Encoding utf8
try {
    $ack = Get-Acl 'HKCU:\Software\Microsoft\InputMethod' -Audit
    $ack.AuditToString | Out-File $out -Append -Encoding utf8
} catch { "SACL read ERR: $_" | Out-File $out -Append -Encoding utf8 }

"=== elevated HKCU sid ===" | Out-File $out -Append -Encoding utf8
[System.Security.Principal.WindowsIdentity]::GetCurrent().Name | Out-File $out -Append -Encoding utf8

"=== wevtutil 4657 (registry modified) ===" | Out-File $out -Append -Encoding utf8
wevtutil qe Security "/q:*[System[(EventID=4657)]]" /c:20 /rd:true /f:text 2>&1 | Out-File $out -Append -Encoding utf8

"=== wevtutil 4663 (object access, last 20) ===" | Out-File $out -Append -Encoding utf8
wevtutil qe Security "/q:*[System[(EventID=4663)]]" /c:20 /rd:true /f:text 2>&1 | Out-File $out -Append -Encoding utf8

Write-Output "done"
