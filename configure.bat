@echo off
echo Configuration du projet...

echo Création d'un nouveau dossier build...
mkdir build
cd build
echo Configuration de CMake...
cmake .. -G "Visual Studio 17 2022" -A x64

echo.
echo Configuration terminée avec succès!
echo.
echo INSTRUCTIONS:
echo 1. Ouvrez le projet dans Visual Studio (le fichier .sln dans le dossier build)
echo 2. Pour ajouter de nouveaux fichiers, créez-les dans les dossiers include/ et src/ appropriés
echo.
pause