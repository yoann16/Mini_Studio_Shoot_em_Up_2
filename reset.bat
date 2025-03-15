@echo off
echo Suppression du build...
if exist build (
    echo Suppression du dossier build existant...
    rmdir /s /q build
)

echo.
pause