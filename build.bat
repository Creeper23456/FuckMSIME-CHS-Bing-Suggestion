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

rem -- locate vcvars64.bat: vswhere first (any VS edition / Build Tools),
rem -- then hardcoded fallbacks for local machines --
set "VCVARS="
set "VSWHERE=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
if exist "%VSWHERE%" (
    for /f "usebackq delims=" %%i in (`"%VSWHERE%" -latest -products * -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
        if not defined VCVARS if exist "%%i\VC\Auxiliary\Build\vcvars64.bat" set "VCVARS=%%i\VC\Auxiliary\Build\vcvars64.bat"
    )
)
if not defined VCVARS set "VCVARS=E:\Program Files\Microsoft Visual Studio\18\Community\VC\Auxiliary\Build\vcvars64.bat"
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

rem -- /utf-8 is REQUIRED: strings.h is UTF-8 (no BOM) and contains non-ASCII
rem -- text in every locale table. Without this flag cl decodes the source
rem -- using the system ANSI codepage (GBK, CP1252, ...), silently mangling
rem -- all of it at compile time -> mojibake in the UI regardless of runtime.
cl /nologo /O2 /W4 /EHsc /MT /utf-8 /DUNICODE /D_UNICODE ^
   /Fe:build\FuckMSIME-CHS-Bing-Suggestion.exe ^
   src\main.cpp ^
   /link advapi32.lib /SUBSYSTEM:CONSOLE
if errorlevel 1 (
    echo BUILD FAILED
    exit /b 1
)

mt -nologo -manifest src\app.manifest "-outputresource:build\FuckMSIME-CHS-Bing-Suggestion.exe;#1"
if errorlevel 1 (
    echo MANIFEST EMBED FAILED
    exit /b 1
)

echo.
echo OK: build\FuckMSIME-CHS-Bing-Suggestion.exe ^(requireAdministrator + comctl32 v6 embedded^)
