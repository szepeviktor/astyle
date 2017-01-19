# analyze powershell scripts using PSScript Analyzer
# PSAvoidUsingWriteHost is excluded because Write-Host can display color

$loc = Set-Location -Path "$Env:USERPROFILE\Batch" -PassThru
Write-Host("`nDirectory $loc")

$psfiles = @("clean.ps1", "dump.ps1", "load.ps1", "load-svn.ps1", "setvars.ps1")
ForEach ($psfile in $psfiles)
{
    $str = "* " * 25
    Write-Host("`nAnalyzing $psfile $str")
	Invoke-ScriptAnalyzer  -Path $psfile `
            -ExcludeRule PSAvoidUsingWriteHost, PSAvoidUsingCmdletAliases
}

Write-Host
Write-Host
Write-Host "Press any key to end . . ."
cmd /c pause | Out-Null
