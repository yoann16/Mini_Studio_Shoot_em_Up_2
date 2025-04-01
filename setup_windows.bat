@echo off
echo === Configuration du projet ===

cd scripts

:: Verification des prerequis
echo [INFO] Verification des outils necessaires...
call Check_Prerequisites.bat
if %errorlevel% neq 0 (
    echo [ERREUR] Verification des prerequis echouee.
    pause
    exit /b 1
)

:: Installation des dependances
echo [INFO] Installation des dependances...
call setup_deps.bat
if %errorlevel% neq 0 (
    echo [ERREUR] Installation des dependances echouee.
    pause
    exit /b 1
)


:: Configuration et compilation du projet
echo [INFO] Configuration et compilation du projet...
call configure.bat
if %errorlevel% neq 0 (
    echo [ERREUR] Configuration du projet echouee.
    pause
    exit /b 1
)

cd ..

echo === Installation terminee avec succes! ===

pause
exit /b 0