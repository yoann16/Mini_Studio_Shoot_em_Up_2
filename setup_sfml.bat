@echo off
echo Configuration du projet avec SFML 2.6.2...

REM Télécharger SFML
cd external
echo Téléchargement de SFML 2.6.2...
curl -L -o sfml.zip https://github.com/SFML/SFML/releases/download/2.6.2/SFML-2.6.2-windows-vc16-64-bit.zip

REM Extraire l'archive
echo Extraction de SFML...
powershell -command "Expand-Archive -Force sfml.zip ."
ren SFML-2.6.2-windows-vc16-64-bit SFML-2.6.2
del sfml.zip

echo SFML a été installé avec succès dans external/SFML-2.6.2
cd ..

REM Créer un fichier main.cpp de base
echo Création du fichier main.cpp...
(
echo #include ^<SFML/Graphics.hpp^>
echo #include ^<iostream^>
echo.
echo int main^(^)
echo {
echo     sf::RenderWindow window^(sf::VideoMode^(800, 600^), "SFML Game"^);
echo     sf::CircleShape shape^(100.f^);
echo     shape.setFillColor^(sf::Color::Green^);
echo.
echo     while ^(window.isOpen^(^)^)
echo     {
echo         sf::Event event;
echo         while ^(window.pollEvent^(event^)^)
echo         {
echo             if ^(event.type == sf::Event::Closed^)
echo                 window.close^(^);
echo         }
echo.
echo         window.clear^(^);
echo         window.draw^(shape^);
echo         window.display^(^);
echo     }
echo.
echo     return 0;
echo }
) > Game_Launcher\src\main.cpp

REM Créer un fichier Game_Engine de base
echo Création de fichiers Game_Engine de base...
(
echo #pragma once
echo #include ^<SFML/Graphics.hpp^>
echo.
echo class Game_Engine {
echo public:
echo     Game_Engine^(^);
echo     ~Game_Engine^(^);
echo.
echo     void initialize^(^);
echo     void update^(float deltaTime^);
echo.
echo private:
echo     // Propriétés du moteur
echo };
) > Game_Engine\include\Game_Engine.h

(
echo #include "Game_Engine.h"
echo #include ^<iostream^>
echo.
echo Game_Engine::Game_Engine^(^) {
echo     std::cout ^<^< "Game Engine constructor called" ^<^< std::endl;
echo }
echo.
echo Game_Engine::~Game_Engine^(^) {
echo     std::cout ^<^< "Game Engine destructor called" ^<^< std::endl;
echo }
echo.
echo void Game_Engine::initialize^(^) {
echo     std::cout ^<^< "Game Engine initialized" ^<^< std::endl;
echo }
echo.
echo void Game_Engine::update^(float deltaTime^) {
echo     // Logique de mise à jour
echo }
) > Game_Engine\src\Game_Engine.cpp

REM Créer un fichier Game de base
echo Création de fichiers Game de base...
(
echo #pragma once
echo #include ^<SFML/Graphics.hpp^>
echo #include "Game_Engine.h"
echo.
echo class Game {
echo public:
echo     Game^(^);
echo     ~Game^(^);
echo.
echo     void initialize^(^);
echo     void update^(float deltaTime^);
echo     void render^(sf::RenderWindow& window^);
echo.
echo private:
echo     Game_Engine m_engine;
echo     sf::CircleShape m_shape;
echo };
) > Game\include\Game.h

(
echo #include "Game.h"
echo #include ^<iostream^>
echo.
echo Game::Game^(^) : m_shape^(100.f^) {
echo     std::cout ^<^< "Game constructor called" ^<^< std::endl;
echo     m_shape.setFillColor^(sf::Color::Green^);
echo }
echo.
echo Game::~Game^(^) {
echo     std::cout ^<^< "Game destructor called" ^<^< std::endl;
echo }
echo.
echo void Game::initialize^(^) {
echo     m_engine.initialize^(^);
echo     std::cout ^<^< "Game initialized" ^<^< std::endl;
echo }
echo.
echo void Game::update^(float deltaTime^) {
echo     m_engine.update^(deltaTime^);
echo     // Logique de jeu
echo }
echo.
echo void Game::render^(sf::RenderWindow& window^) {
echo     window.draw^(m_shape^);
echo }
) > Game\src\Game.cpp

echo.
echo Configuration terminée avec succès!
echo 1. SFML 2.6.2 a été téléchargé et installé
echo 2. Des fichiers de base ont été créés
echo.
echo Vous pouvez maintenant configurer CMake avec la commande:
echo    mkdir build
echo    cd build
echo    cmake .. -G "Visual Studio 17 2022" -A x64
echo.
pause