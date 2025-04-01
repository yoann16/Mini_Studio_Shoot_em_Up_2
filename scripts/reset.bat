@echo off
echo suppresssion du build du cmake et des dépendances pour recommencer l'installation
echo ====================================================================

cd ..
if exist build (   
        rmdir /s /q build
        echo dossier build supprimer
    )

if exist cmake (   
        rmdir /s /q cmake
        echo dossier cmake supprimer
    )


if exist external\SFML-2.6.2 ( 
        rmdir /s /q external\SFML-2.6.2
        echo dossier SFML-2.6.2 supprimer
    )

if exist external\imgui (   
        rmdir /s /q external\imgui
        echo dossier imgui supprimer
    )

if exist external\imgui-sfml (  
        rmdir /s /q external\imgui-sfml
        echo dossier imgui-sfml supprimer
    )

if exist external\json (   
        rmdir /s /q external\json
        echo dossier json supprimer
    )

cd scripts

pause
exit /b 0