@echo off
setlocal enabledelayedexpansion

echo Verification des prerequis...
echo ===========================

echo Checking Visual Studio...

set VS_FOUND=0
set VS_PATH=

:: Check Visual Studio installation folders
if exist "C:\Program Files\Microsoft Visual Studio\2022\Community" (
    echo [OK] Visual Studio 2022 Community found.
    set VS_FOUND=1
    set "VS_PATH=C:\Program Files\Microsoft Visual Studio\2022\Community\VC\Auxiliary\Build\vcvarsall.bat"
    goto vs_found
)

if exist "C:\Program Files\Microsoft Visual Studio\2022\Professional" (
    echo [OK] Visual Studio 2022 Professional found.
    set VS_FOUND=1
    set "VS_PATH=C:\Program Files\Microsoft Visual Studio\2022\Professional\VC\Auxiliary\Build\vcvarsall.bat"
    goto vs_found
)

:: ... [autres vérifications VS] ...

if !VS_FOUND! equ 0 (
    echo [ERROR] Visual Studio not found.
    exit /b 1
)

:vs_found
echo [OK] Visual Studio is installed.
echo VS_PATH=!VS_PATH! > .vs_path.txt
echo Checking CMake...

:: Vérifier si CMake est dans le PATH système
where cmake >nul 2>&1
if !errorlevel! equ 0 (
    echo [OK] CMake trouve dans le PATH systeme.
) else (
    :: Vérifier les emplacements courants d'installation
    set CMAKE_FOUND=0
    
    if exist "C:\Program Files\CMake\bin\cmake.exe" (
        set CMAKE_FOUND=1
        echo [AVERTISSEMENT] CMake est installe mais n'est pas dans le PATH.
        echo [AVERTISSEMENT] Ajoutez "C:\Program Files\CMake\bin" au PATH ou utilisez la version locale.
        set "PATH=C:\Program Files\CMake\bin;%PATH%"
        goto :create_cmake    
    ) else if exist "C:\Program Files (x86)\CMake\bin\cmake.exe" (
        set CMAKE_FOUND=1
        echo [AVERTISSEMENT] CMake est installe mais n'est pas dans le PATH.
        echo [AVERTISSEMENT] Ajoutez "C:\Program Files (x86)\CMake\bin" au PATH ou utilisez la version locale.
        set "PATH=C:\Program Files (x86)\CMake\bin;%PATH%"
        goto :create_cmake
    ) else if exist "%LOCALAPPDATA%\Programs\CMake\bin\cmake.exe" (
        set CMAKE_FOUND=1
        echo [AVERTISSEMENT] CMake est installe pour l'utilisateur actuel mais n'est pas dans le PATH.
        echo [AVERTISSEMENT] Ajoutez "%LOCALAPPDATA%\Programs\CMake\bin" au PATH ou utilisez la version locale.
        set "PATH=%LOCALAPPDATA%\Programs\CMake\bin;%PATH%"
        goto :create_cmake
    ) else if exist "%APPDATA%\CMake\bin\cmake.exe" (
        set CMAKE_FOUND=1
        echo [AVERTISSEMENT] CMake est installe pour l'utilisateur actuel mais n'est pas dans le PATH.
        echo [AVERTISSEMENT] Ajoutez "%APPDATA%\CMake\bin" au PATH ou utilisez la version locale.
        set "PATH=%APPDATA%\CMake\bin;%PATH%"
        goto :create_cmake
    )
    
    :: Vérifier si une version locale existe dans le projet
    if exist "..\cmake\bin\cmake.exe" (
        set CMAKE_FOUND=1
        echo [OK] CMake local trouve dans le projet.
        set "PATH=..\cmake\bin;%PATH%"
        goto :cmake_check_end
    )
    
    :: Si CMake n'est toujours pas trouvé, proposer de l'installer localement
    if !CMAKE_FOUND! equ 0 (
        echo [AVERTISSEMENT] CMake n'a pas ete trouve sur le systeme ni dans le projet.
        :create_cmake
        echo Voulez-vous telecharger et installer CMake localement pour ce projet? (O/N)
        set /p INSTALL_CMAKE=
        
        if /i "!INSTALL_CMAKE!"=="O" (
            echo [INFO] Telechargement de CMake...
            
            :: Créer le dossier cmake s'il n'existe pas
            if not exist "..\cmake" mkdir "..\cmake"
            
            :: Télécharger CMake portable
            powershell -Command "Invoke-WebRequest -Uri 'https://github.com/Kitware/CMake/releases/download/v3.26.4/cmake-3.26.4-windows-x86_64.zip' -OutFile '..\cmake.zip'"
            
            if !errorlevel! neq 0 (
                echo [ERREUR] Echec du telechargement de CMake.
                exit /b 1
            )
            
            :: Extraire l'archive
            echo [INFO] Extraction de CMake...
            powershell -Command "Expand-Archive -Path '..\cmake.zip' -DestinationPath '..'"
            
            if !errorlevel! neq 0 (
                echo [ERREUR] Echec de l'extraction de CMake.
                exit /b 1
            )
            
            :: Renommer le dossier extracté
            for /d %%i in ("..\cmake-*") do (
                if exist "..\cmake" rd /s /q "..\cmake"
                ren "%%i" "cmake"
            )
            
            :: Nettoyer
            del "..\cmake.zip"
            
            :: Ajouter CMake au PATH temporairement
            set "PATH=..\cmake\bin;%PATH%"
            
            echo [OK] CMake a ete installe localement pour le projet.
        ) else (
            echo [INFO] Installation de CMake annulee.
            echo [INFO] Vous pouvez telecharger et installer CMake manuellement depuis https://cmake.org/download/
            exit /b 1
        )
    )
)

:cmake_check_end
:: Vérifier que CMake est maintenant disponible
where cmake >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERREUR] Impossible de trouver ou d'installer CMake.
    exit /b 1
)

echo [OK] CMake est disponible pour le projet.



:: Vérifier la version de CMake
for /f "tokens=3" %%i in ('cmake --version ^| findstr /C:"cmake version"') do (
    set cmake_version=%%i
)
echo Version de CMake detectee: %cmake_version%

:: Extraire les composants de la version (majeur.mineur.patch)
for /f "tokens=1,2,3 delims=." %%a in ("%cmake_version%") do (
    set cmake_major=%%a
    set cmake_minor=%%b
    set cmake_patch=%%c
)

:: Vérifier si la version est >= 3.14
set VERSION_OK=0
if %cmake_major% gtr 3 (
    set VERSION_OK=1
) else if %cmake_major% equ 3 (
    if %cmake_minor% geq 14 (
        set VERSION_OK=1
    )
)

if %VERSION_OK% equ 0 (
    echo [ERREUR] CMake version %cmake_version% est trop ancienne. Version 3.14 ou superieure requise.
    echo [ERREUR] Veuillez mettre a jour CMake ou installer une version plus recente.
    exit /b 1
)

echo [OK] CMake version %cmake_version% est compatible avec ce projet.

:: Vérifier si Git est installé
echo Verification de Git...
where git >nul 2>&1
if %errorlevel% neq 0 (
    echo [ERREUR] Git n'est pas installe ou n'est pas dans le PATH.
    echo Git est necessaire pour cloner vcpkg.
    echo Vous pouvez le télécharger depuis: https://git-scm.com/download/win
    exit /b 1
)
echo [OK] Git trouve.

echo Tous les prerequis sont installes.
exit /b 0