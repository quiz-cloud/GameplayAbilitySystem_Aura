@echo off
setlocal enabledelayedexpansion
title DeltaForce Safe Optimizer

rem ============================================================
rem  三角洲行动 一键优化（安全可逆版）
rem  设计原则：只做临时优化，游戏退出后自动还原；
rem  不删除任何文件，不修改 NVIDIA 面板，不永久改系统。
rem ============================================================

cd /d "%~dp0"

net session >nul 2>&1
if errorlevel 1 (
    echo 需要管理员权限，正在请求...
    powershell -NoProfile -Command "Start-Process -FilePath '%~f0' -Verb RunAs"
    exit /b
)

set "BACKUP_DIR=%~dp0DeltaForce_SafeBackup"
set "SCHEME_FILE=%BACKUP_DIR%\power_scheme.txt"
set "WEGAME=D:\Program Files (x86)\WeGame\wegame.exe"
set "GAME_DIR=D:\WeGameApps\rail_apps\DeltaForce(2001918)\DeltaForce\Binaries\Win64"
set "GAME_EXE=DeltaForceClient-Win64-Shipping.exe"
set "GAME_PATH=%GAME_DIR%\%GAME_EXE%"
set "HIGH_PERF=8c5e7fda-e8bf-4a96-9a85-a6e23a8c635c"

if not exist "%BACKUP_DIR%" mkdir "%BACKUP_DIR%"

:menu
cls
echo ============================================================
echo   三角洲行动 一键优化    安全可逆版
echo ============================================================
echo   游戏运行期间会临时开启高性能电源、关闭 Xbox 录屏、
echo   开启游戏模式，并把游戏进程设为高优先级；
echo   游戏退出后会自动恢复你原来的设置。
echo.
echo   1. 开始优化并启动游戏
echo   2. 立即恢复原设置
echo   3. 退出
echo.
choice /c 123 /n /m "请选择 1/2/3: "
if errorlevel 3 exit /b
if errorlevel 2 goto restore
if errorlevel 1 goto start

:start
if not exist "%SCHEME_FILE%" (
    powercfg /getactivescheme > "%SCHEME_FILE%"
)
if not exist "%BACKUP_DIR%\GameConfigStore.reg" (
    reg export "HKCU\System\GameConfigStore" "%BACKUP_DIR%\GameConfigStore.reg" /y >nul 2>&1
)
if not exist "%BACKUP_DIR%\GameBar.reg" (
    reg export "HKCU\Software\Microsoft\GameBar" "%BACKUP_DIR%\GameBar.reg" /y >nul 2>&1
)
if not exist "%BACKUP_DIR%\UserGpuPreferences.reg" (
    reg export "HKCU\Software\Microsoft\DirectX\UserGpuPreferences" "%BACKUP_DIR%\UserGpuPreferences.reg" /y >nul 2>&1
)
if not exist "%BACKUP_DIR%\AppCompatFlags.reg" (
    reg export "HKCU\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" "%BACKUP_DIR%\AppCompatFlags.reg" /y >nul 2>&1
)

powercfg /setactive "%HIGH_PERF%" >nul 2>&1
reg add "HKCU\System\GameConfigStore" /v GameDVR_Enabled /t REG_DWORD /d 0 /f >nul 2>&1
reg add "HKCU\Software\Microsoft\GameBar" /v AutoGameModeEnabled /t REG_DWORD /d 1 /f >nul 2>&1
reg add "HKCU\Software\Microsoft\GameBar" /v AllowAutoGameMode /t REG_DWORD /d 1 /f >nul 2>&1
reg add "HKCU\Software\Microsoft\DirectX\UserGpuPreferences" /v "%GAME_PATH%" /t REG_SZ /d "GpuPreference=2;" /f >nul 2>&1
reg add "HKCU\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" /v "%GAME_PATH%" /t REG_SZ /d "~ DISABLEDXMAXIMIZEDWINDOWEDMODE" /f >nul 2>&1

echo.
echo 优化已生效，正在启动 WeGame...
if exist "%WEGAME%" (
    start "" "%WEGAME%"
) else (
    echo 未找到 WeGame，请手动启动游戏。
)
echo 等待游戏进程：%GAME_EXE%
echo 游戏退出后会自动恢复原设置，请不要关闭这个窗口。

:waitgame
timeout /t 3 /nobreak >nul
tasklist /fi "imagename eq %GAME_EXE%" 2>nul | find /i "%GAME_EXE%" >nul
if errorlevel 1 goto waitgame

echo.
echo 检测到游戏，正在设为高优先级。
:boost
powershell -NoProfile -Command "Get-Process -Name '%GAME_EXE:~0,-4%' -ErrorAction SilentlyContinue | ForEach-Object { try { $_.PriorityClass = 'High' } catch {} }" >nul 2>&1
timeout /t 5 /nobreak >nul
tasklist /fi "imagename eq %GAME_EXE%" 2>nul | find /i "%GAME_EXE%" >nul
if not errorlevel 1 goto boost

echo.
echo 游戏已退出，正在恢复原设置...
goto restore

:restore
set "ORIG_SCHEME="
for /f "delims=" %%a in ('powershell -NoProfile -Command "$c = Get-Content -Raw '%SCHEME_FILE%'; if ($c -match '[0-9a-fA-F]{8}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{4}-[0-9a-fA-F]{12}') { $Matches[0] }"') do set "ORIG_SCHEME=%%a"
if defined ORIG_SCHEME (
    powercfg /setactive "%ORIG_SCHEME%" >nul 2>&1
    echo 电源计划已还原。
) else (
    powercfg /setactive SCHEME_BALANCED >nul 2>&1
    echo 未找到备份，已恢复为平衡电源计划。
)

if exist "%BACKUP_DIR%\GameConfigStore.reg" (
    reg import "%BACKUP_DIR%\GameConfigStore.reg" >nul 2>&1
) else (
    reg delete "HKCU\System\GameConfigStore" /v GameDVR_Enabled /f >nul 2>&1
)
if exist "%BACKUP_DIR%\GameBar.reg" (
    reg import "%BACKUP_DIR%\GameBar.reg" >nul 2>&1
) else (
    reg delete "HKCU\Software\Microsoft\GameBar" /v AutoGameModeEnabled /f >nul 2>&1
    reg delete "HKCU\Software\Microsoft\GameBar" /v AllowAutoGameMode /f >nul 2>&1
)
if exist "%BACKUP_DIR%\UserGpuPreferences.reg" (
    reg import "%BACKUP_DIR%\UserGpuPreferences.reg" >nul 2>&1
) else (
    reg delete "HKCU\Software\Microsoft\DirectX\UserGpuPreferences" /v "%GAME_PATH%" /f >nul 2>&1
)
if exist "%BACKUP_DIR%\AppCompatFlags.reg" (
    reg import "%BACKUP_DIR%\AppCompatFlags.reg" >nul 2>&1
) else (
    reg delete "HKCU\Software\Microsoft\Windows NT\CurrentVersion\AppCompatFlags\Layers" /v "%GAME_PATH%" /f >nul 2>&1
)

echo 所有临时优化已还原，本窗口可以关闭。
pause
exit /b
