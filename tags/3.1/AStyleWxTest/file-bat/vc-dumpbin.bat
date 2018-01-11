@rem  The file vsvars32.bat sets the environment variables for the compiler.
@rem  The system variable VS90COMNTOOLS contains the path to the batch file.

call "%VS90COMNTOOLS%\vsvars32.bat"

"%VCINSTALLDIR%\Vc7\bin\dumpbin"  /exports  ..\_CB-MinGW\bin\AStyle.dll

pause
