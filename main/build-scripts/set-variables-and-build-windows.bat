@echo off

:: ˵��
echo ��cmd����set-variables-and-build-windows.bat windevΪvs���������������
echo ��cmd����set-variables-and-build-windows.bat slnΪvs��������������ɽ������
echo ��cmd����set-variables-and-build-windows.bat cleanΪ���Դ������������
echo ��cmd����set-variables-and-build-windows.bat���ٱ��벢���famous

:: ����
echo %1 | findstr clean >nul
if %errorlevel% equ 0 (set v=1) else (set v=0)
echo %1 | findstr sln >nul
if %errorlevel% equ 0 (set sln=1) else (set sln=0)
echo %1 | findstr windev >nul
if %errorlevel% equ 0 (set windev=1) else (set windev=0)
if %windev% equ 1 goto :step0
if exist ..\build rd /q /s ..\build
if exist ..\dependencies64\boost\stage\lib\win32\libboost_wave-vc140-mt-gd-1_59.lib del /f /q ..\dependencies64\boost\stage\lib\win32\libboost_wave-vc140-mt-gd-1_59.lib
if exist ..\dependencies64\cef\bin\win32\libcef.dll.pdb del /f /q ..\dependencies64\cef\bin\win32\libcef.dll.pdb
:step0
if %v% equ 1 if exist v.txt del /f /q v.txt
if %v% equ 1 goto :eof

:: dependencies64�Զ�ƥ��
::cd ..\dependencies64\gtest
::mklink /j include include-win
::cd ..\..\build-scripts
if %windev% equ 1 goto :eof

:: ��ȡ·��, setlocal EnableDelayedExpansion, endlocal
set fn=vcvarsall.bat
set v=""
if exist v.txt for /f "delims=" %%a in ('findstr "\<%fn%\>" v.txt') do set v=%%a
set v=%v:*>=%
echo ����%fn%Ϊ: %v%
if not exist "%v%" echo ����%fn%...
if not exist "%v%" for %%a in (c d e f g h i j k l m n o p q r s t u v w x y z) do if exist %%a:\ pushd %%a:\ & (for /r %%b in (*%fn%) do if /i "%%~nxb" equ "%fn%" set v=%%b & echo �ѵ�%fn%Ϊ: %%b) & popd
set BUILD_VCVARSALL=%v%
set fn=7z.exe
set v=""
if exist v.txt for /f "delims=" %%a in ('findstr "\<%fn%\>" v.txt') do set v=%%a
set v=%v:*>=%
echo ����%fn%Ϊ: %v%
if not exist "%v%" echo ����%fn%...
if not exist "%v%" for %%a in (c d e f g h i j k l m n o p q r s t u v w x y z) do if exist %%a:\ pushd %%a:\ & (for /r %%b in (*%fn%) do if /i "%%~nxb" equ "%fn%" set v=%%b & echo �ѵ�%fn%Ϊ: %%b) & popd
set BUILD_7ZIP=%v%
echo ·������, ����ֶ��޸��뱣�ָ�ʽ��·����û�л��з�>v.txt
echo ^<vcvarsall.bat^>%BUILD_VCVARSALL%>>v.txt
echo ^<7z.exe^>%BUILD_7ZIP%>>v.txt

set BUILD_ARCHIVE_NAME="famous"
set BUILD_PARALLEL_THREADS=12

build-windows.bat

