@echo off

:: Fail early if environment not set
if not defined BUILD_VCVARSALL exit /b 1
if not defined BUILD_ARCHIVE_NAME exit /b 1
if not defined BUILD_PARALLEL_THREADS exit /b 1
if not defined BUILD_7ZIP exit /b 1

:: Clean and enter shadow build folder
echo Cleaning...
cd .. || goto :error
::if exist build rmdir build /s /q || goto :error
mkdir build || goto :error

:: Unpack archived dependencies
echo Unpacking archived dependencies...
"%BUILD_7ZIP%" x -y -odependencies64 dependencies64\large_files_win32.7z || goto :error

:: Setup VC++ environment
echo Setting up VC++...
call "%BUILD_VCVARSALL%" amd64 || goto :error

:: Run cmake
cd build || goto :error
echo %BUILD_VCVARSALL% | findstr 2017 && set v=1 || set v=0
if %v% equ 1 (cmake -G "Visual Studio 15 2017 Win64" .. || goto :error) else (cmake -G "Visual Studio 14 2015 Win64" .. || goto :error)

:: Build with MSBuild
echo Building...
msbuild "%BUILD_ARCHIVE_NAME%.sln" /t:Clean /p:Configuration=RelWithDebInfo || goto :error
if %sln% equ 1 goto :eof
msbuild "%BUILD_ARCHIVE_NAME%.sln" /p:Configuration=RelWithDebInfo /m:%BUILD_PARALLEL_THREADS% || goto :error

:: Create server folder to later zip
set SERVER_FOLDER=%BUILD_ARCHIVE_NAME%
if exist "%SERVER_FOLDER%" rmdir "%SERVER_FOLDER%" /s /q || goto :error
mkdir "%SERVER_FOLDER%" || goto :error

:: Copy media files
echo Copying media...
xcopy ..\deploy\general\server "%SERVER_FOLDER%\server" /e /i /y || goto :error
xcopy ..\deploy\general\wallpapers "%SERVER_FOLDER%\wallpapers" /e /i /y || goto :error
::copy ..\deploy\general\famous_server_3.0.pdf "%SERVER_FOLDER%" || goto :error

:: Copy binaries
echo Copying binaries...
copy shell\*.dll "%SERVER_FOLDER%\server" || goto :error
copy shell\RelWithDebInfo\FamousServer.exe "%SERVER_FOLDER%\server" || goto :error
copy shell\RelWithDebInfo\FamousServer.pdb "%SERVER_FOLDER%\server" || goto :error
copy shell\RelWithDebInfo\libcef.dll.pdb "%SERVER_FOLDER%\server" || goto :error
copy shell\FamousServer.config "%SERVER_FOLDER%\server" || goto :error
copy shell\*.ttf "%SERVER_FOLDER%\server" || goto :error
copy shell\*.pak "%SERVER_FOLDER%\server" || goto :error
xcopy shell\locales "%SERVER_FOLDER%\server\locales" /e /i /y || goto :error

:: Copy documentation
echo Copying documentation...
copy ..\CHANGELOG "%SERVER_FOLDER%" || goto :error
copy ..\LICENSE "%SERVER_FOLDER%" || goto :error
copy ..\README "%SERVER_FOLDER%" || goto :error

:: Create zip file
echo Creating zip...
"%BUILD_7ZIP%" a "%BUILD_ARCHIVE_NAME%.7z" "%SERVER_FOLDER%" || goto :error

:: Skip exiting with failure
goto :EOF

:error
exit /b %errorlevel%
