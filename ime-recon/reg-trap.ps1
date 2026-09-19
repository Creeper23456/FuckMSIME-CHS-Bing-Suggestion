# reg-trap.ps1 - arm registry audit trap on InputMethod tree (elevated, ASCII only)
$ErrorActionPreference = 'Continue'

# 1) enable success auditing for the Registry subcategory (use GUID, locale-proof)
auditpol /set /subcategory:{0CCE921F-69AE-11D9-BED3-505054503030} /success:enable
Write-Output "auditpol done"

# 2) SACL: audit SetValue (and Delete) success on HKCU InputMethod tree for Everyone
$keyPath = 'HKCU:\Software\Microsoft\InputMethod'
$ack = Get-Acl $keyPath
$ruleSetValue = New-Object System.Security.AccessControl.RegistryAuditRule('Everyone', 'SetValue', 'ContainerInherit', 'None', 'Success')
$ruleDelete   = New-Object System.Security.AccessControl.RegistryAuditRule('Everyone', 'Delete',    'ContainerInherit', 'None', 'Success')
$ack.AddAuditRule($ruleSetValue)
$ack.AddAuditRule($ruleDelete)
Set-Acl -Path $keyPath -AclObject $ack
Write-Output "SACL armed on $keyPath (subtree)"

# 3) also arm the sister tree used by input experience settings
$keyPath2 = 'HKCU:\Software\Microsoft\Input'
$ack2 = Get-Acl $keyPath2
$ack2.AddAuditRule( (New-Object System.Security.AccessControl.RegistryAuditRule('Everyone','SetValue','ContainerInherit','None','Success')) )
Set-Acl -Path $keyPath2 -AclObject $ack2
Write-Output "SACL armed on $keyPath2 (subtree)"
Write-Output "TRAP ACTIVE - trigger the popup now, click things, then run dump-trap.ps1 (elevated)"
