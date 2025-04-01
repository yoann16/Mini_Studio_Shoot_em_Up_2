@echo off
echo === Installation des dependances (SFML, ImGui, nlohmann-json) ===

cd ..

:: S'assurer que le dossier external existe
if not exist "external" (
    echo [INFO] Creation du dossier external...
    mkdir external
)

:: Installation de SFML
echo [INFO] Configuration de SFML 2.6.2...
if not exist "external\SFML-2.6.2" (
    REM Télécharger SFML uniquement s'il n'est pas présent
    cd external
    echo Téléchargement de SFML 2.6.2...
    curl -L -o sfml.zip https://github.com/SFML/SFML/releases/download/2.6.2/SFML-2.6.2-windows-vc16-64-bit.zip

    REM Extraire l'archive
    echo Extraction de SFML...
    powershell -command "Expand-Archive -Force sfml.zip ."
    
    REM Renommer le dossier
    if exist "SFML-2.6.2-windows-vc16-64-bit" (
        ren SFML-2.6.2-windows-vc16-64-bit SFML-2.6.2
    )
    
    del sfml.zip
    cd ..
    echo SFML est prêt dans external/SFML-2.6.2
) else (
    echo [OK] SFML est deja installe.
)

@REM :: Installation d'ImGui
@REM echo [INFO] Configuration d'ImGui...
@REM if not exist "external\imgui" (
@REM     cd external
@REM     echo [INFO] Telechargement d'ImGui...
@REM     git clone https://github.com/ocornut/imgui.git
@REM     cd ..
@REM     echo [OK] ImGui installe avec succes.
@REM ) else (
@REM     echo [OK] ImGui est deja installe.
@REM )

@REM :: Installation d'ImGui-SFML
@REM echo [INFO] Configuration d'ImGui-SFML...
@REM if not exist "external\imgui-sfml" (
@REM     cd external
@REM     echo [INFO] Telechargement d'ImGui-SFML...
@REM     git clone https://github.com/SFML/imgui-sfml.git
@REM     cd ..
@REM     echo [OK] ImGui-SFML installe avec succes.
@REM ) else (
@REM     echo [OK] ImGui-SFML est deja installe.
@REM )

:: Installation de nlohmann-json
echo [INFO] Configuration de nlohmann-json...
if not exist "external\json" (
    cd external
    echo [INFO] Telechargement de nlohmann-json...
    git clone https://github.com/nlohmann/json.git
    cd ..
    echo [OK] nlohmann-json installe avec succes.
) else (
    echo [OK] nlohmann-json est deja installe.
)

cd scripts
echo === Installation des dependances terminee ===
echo [INFO] Toutes les dependances ont ete installees dans le dossier external.
echo [INFO] Vous pouvez maintenant configurer le projet avec le script configure.bat.

exit /b 0