@ECHO OFF
REM Prompt 1.2
REM Open a command prompt to run ffmpeg/ffplay/ffprobe
REM Copyright (C) 2013-2015  Kyle Schwarz

TITLE MPV Prompt

IF NOT EXIST ffmpeg.exe (
  CLS
  ECHO mpv.exe could not be found.
  GOTO:error
)

PROMPT $P$_$G
SET PATH=%CD%;%PATH%
CLS
ECHO Current directory is now: "%CD%"


CMD /Q /K 
GOTO:EOF

:error
ECHO.
ECHO Press any key to exit.
PAUSE >nul
GOTO:EOF
