$out = 'C:\Users\klp\AppData\Local\Temp\ime-recon\trap-events.txt'
Remove-Item $out -ErrorAction SilentlyContinue
$Host.UI.RawUI.WindowTitle = 'TRAP RUNNING - GO TYPE NOW! 45s'
"=== trigger popup and click buttons NOW (45s) ===" | Out-File $out -Append -Encoding utf8
Start-Sleep -Seconds 45
"=== wevtutil 4657 (registry modified) ===" | Out-File $out -Append -Encoding utf8
wevtutil qe Security "/q:*[System[(EventID=4657)]]" /c:40 /rd:true /f:text 2>&1 | Out-File $out -Append -Encoding utf8
"=== wevtutil 4663 (file/object access) ===" | Out-File $out -Append -Encoding utf8
wevtutil qe Security "/q:*[System[(EventID=4663)]]" /c:40 /rd:true /f:text 2>&1 | Out-File $out -Append -Encoding utf8
"=== END ===" | Out-File $out -Append -Encoding utf8
Write-Output "collected - window can close"
