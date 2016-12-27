# analyze powershell scripts using PSScript Analyzer
# PSAvoidUsingWriteHost is excluded because Write-Host can display color

$loc = Set-Location -Path "$Env:USERPROFILE\Batch" -PassThru
Write-Host("`nDirectory $loc")

$psfiles = @("clean.ps1", "dump.ps1", "load.ps1", "load-svn.ps1", "setvars.ps1")
ForEach ($psfile in $psfiles)
{
    $str = "* " * 40
    Write-Host("`nAnalyzing $psfile $str `n")
	Invoke-ScriptAnalyzer -ExcludeRule PSAvoidUsingWriteHost  -Path $psfile
}

