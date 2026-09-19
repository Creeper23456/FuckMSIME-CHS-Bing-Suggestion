$out = 'C:\Users\klp\AppData\Local\Temp\ime-recon\acl-result.txt'
Remove-Item $out -ErrorAction SilentlyContinue
try {
  $reg = [Microsoft.Win32.Registry]::CurrentUser.OpenSubKey('Software\Microsoft\InputMethod\Settings\CHS', $true)
  $reg.SetValue('Enable Cloud Candidate', 0, 'DWord')
  $reg.SetValue('AutoShowCloudSuggestion', 0, 'DWord')
  "values zeroed" | Out-File $out -Append -Encoding utf8

  $sec = $reg.GetAccessControl()
  $id = New-Object System.Security.Principal.SecurityIdentifier('S-1-5-21-3590017983-3034070771-77558994-1001')
  $rule = New-Object System.Security.AccessControl.RegistryAccessRule($id, [System.Security.AccessControl.RegistryRights]::SetValue, [System.Security.AccessControl.InheritanceFlags]::None, [System.Security.AccessControl.PropagationFlags]::None, [System.Security.AccessControl.AccessControlType]::Deny)
  $sec.AddAccessRule($rule)
  $reg.SetAccessControl($sec)
  "deny rule added + committed" | Out-File $out -Append -Encoding utf8

  $sec2 = [Microsoft.Win32.Registry]::CurrentUser.OpenSubKey('Software\Microsoft\InputMethod\Settings\CHS').GetAccessControl()
  $denies = $sec2.Access | Where-Object { $_.AccessControlType -eq 'Deny' }
  "persisted deny rules: $(($denies | Measure-Object).Count)" | Out-File $out -Append -Encoding utf8
  $denies | ForEach-Object { "  DENY $($_.RegistryRights) -> $($_.IdentityReference)" | Out-File $out -Append -Encoding utf8 }

  "=== write attempt (should be BLOCKED) ===" | Out-File $out -Append -Encoding utf8
  try {
    $reg2 = [Microsoft.Win32.Registry]::CurrentUser.OpenSubKey('Software\Microsoft\InputMethod\Settings\CHS', $true)
    $reg2.SetValue('Enable Cloud Candidate', 1, 'DWord')
    "WRITE SUCCEEDED - DENY NOT EFFECTIVE" | Out-File $out -Append -Encoding utf8
  } catch { "WRITE BLOCKED: $($_.Exception.GetType().Name)" | Out-File $out -Append -Encoding utf8 }

  $v = [Microsoft.Win32.Registry]::CurrentUser.OpenSubKey('Software\Microsoft\InputMethod\Settings\CHS').GetValue('Enable Cloud Candidate')
  "final value: $v" | Out-File $out -Append -Encoding utf8
} catch {
  "FATAL: $_" | Out-File $out -Append -Encoding utf8
}
