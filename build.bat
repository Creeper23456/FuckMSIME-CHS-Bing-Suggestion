@echo off
setlocal enabledelayedexpansion

rem == FuckMSIME-CHS-Bing-Suggestion build script (MSVC x64) ==
rem Usage: build.bat          -> build\FuckMSIME-CHS-Bing-Suggestion.exe
rem        build.bat clean    -> remove build dir

if "%1"=="clean" (
    if exist build rmdir /s /q build
    echo cleaned.
    exit /b 0
)

rem -- locate vcvars64.bat: E: first (this machine), then C: fallbacks --
set "VCVARS=E:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"
if not exist "%VCVARS%" set "VCVARS=C:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"
if not exist "%VCVARS%" set "VCVARS=C:\Program Files (x86)\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvars64.bat"
if not exist "%VCVARS%" (
    echo ERROR: vcvars64.bat not found - adjust the path in build.bat
    exit /b 1
)

if not exist build mkdir build

call "%VCVARS%" >nul 2>&1
if errorlevel 1 (
    echo ERROR: vcvars64.bat failed
    exit /b 1
)

cl /nologo /O2 /W4 /EHsc /MT /DUNICODE /D_UNICODE ^
   /Fe:build\FuckMSIME-CHS-Bing-Suggestion.exe ^
   src\main.cpp ^
   /link advapi32.lib /SUBSYSTEM:CONSOLE
if errorlevel 1 (
    echo BUILD FAILED
    exit /b 1
)

echo.
echo OK: build\FuckMSIME-CHS-Bing-Suggestion.exe
