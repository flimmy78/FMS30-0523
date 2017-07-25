cd /d %~dp0
for %%i in (./MediaCaptureSource.dll,*.ax) do regsvr32 /s %%i
pause