@echo off
echo Configuration du projet avec SFML 2.6.2...

cd ..
REM Vérifier si le dossier SFML existe déjà
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
)
echo SFML est prêt dans external/SFML-2.6.2