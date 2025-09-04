:: Сборка проекта в релизную версию
cmake -S . -B build
cmake --build build --config Release

@echo off
:: Меняем текущую директорию на ту, где находится исполняемый файл
cd /d "%~dp0build\TBABGame\Release"

:: Запускаем программу
"TBABGame.exe"

pause