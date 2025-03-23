@echo off
setlocal enabledelayedexpansion

echo Configuration du projet...

cd ..
echo Creation d'un nouveau dossier build...
if not exist build mkdir build
cd build

@REM echo POINT DE CONTROLE 1

REM Test simple pour voir si on peut lire le fichier
echo Test de lecture du fichier .vs_path.txt:
if exist "..\scripts\.vs_path.txt" (
    echo Le fichier existe!
    type "..\scripts\.vs_path.txt"
) else (
    echo Le fichier n'existe pas.
)

@REM echo POINT DE CONTROLE 2

REM Configuration directe de Visual Studio
echo Configuration directe de l'environnement Visual Studio...
if exist "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" (
    call "C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    echo Visual Studio 2022 configure.
) else if exist "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" (
    call "C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat" x64
    echo Visual Studio 2019 configure.
) else (
    echo ATTENTION: Visual Studio non trouve.
)

@REM echo POINT DE CONTROLE 3
echo Configuration de CMake...
cmake .. -G "Visual Studio 17 2022" -A x64
if !errorlevel! neq 0 (
    echo ERREUR: La configuration CMake a echoue.
    cd ..\scripts
    exit /b 1
)

echo Configuration terminee avec succes!
echo.
echo INSTRUCTIONS:
echo 1. Ouvrez le projet dans Visual Studio (le fichier .sln dans le dossier build)
echo 2. Pour ajouter de nouveaux fichiers, creez-les dans les dossiers include/ et src/ appropries
echo.
exit /b 0
