@echo off
echo Configuration de la structure du projet 

REM Créer les dossiers nécessaires
mkdir Game_Engine\include 2>nul
mkdir Game_Engine\src 2>nul
mkdir Game\include 2>nul
mkdir Game\src 2>nul
mkdir Game_Launcher\src 2>nul
mkdir external 2>nul

type nul > CMakeLists.txt
type nul > Game_Engine\CMakeLists.txt
type nul > Game\CMakeLists.txt
type nul > Game_Launcher\CMakeLists.txt

echo.
echo Fichiers CMakeLists.txt vides crees avec succes!
echo Structure de dossiers creee.
echo.
pause