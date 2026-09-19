# reg-trap2.ps1 - enable registry audit CORRECTLY, wait 90s for user trigger, auto-collect (elevated, ASCII only)
$out = 'C:\Users\klp\AppData\Local\Temp\ime-recon\trap-events.txt'
Remove-Item $out -ErrorAction SilentlyContinue

auditpol --% /set /subcategory:{0CCE921F-69AE-11D9-BED3-505054503030} /success:enable
"=== auditpol state after set ===" | Out-File $out -Append -Encoding utf8
auditpol --% /get /subcategory:{0CCE921F-69AE-11D9-BED3-505054503030} | Out-File $out -Append -Encoding utf8

"=== NOW: trigger the popup and click its buttons (90s window) ===" | Out-File $out -Append -Encoding utf8
Start-Sleep -Seconds 90

"=== wevtutil 4657 ===" | Out-File $out -Append -Encoding utf8
wevtutil qe Security "/q:*[System[(EventID=4657)]]" /c:30 /rd:true /f:text 2>&1 | Out-File $out -Append -Encoding utf8
"=== wevtutil 4663 ===" | Out-File $out -Append -Encoding utf8
wevtutil qe Security "/q:*[System[(EventID=4663)]]" /c:10 /rd:true /f:text 2>&1 | Out-File $out -Append -Encoding utf8
Write-Output "capture done"
