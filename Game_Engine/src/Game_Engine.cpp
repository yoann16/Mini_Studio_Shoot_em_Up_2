#include "Game_Engine.h"
#include <iostream>

Game_Engine::Game_Engine() {
    std::cout << "Game Engine constructor called" << std::endl;
}

Game_Engine::~Game_Engine() {
    std::cout << "Game Engine destructor called" << std::endl;
}

void Game_Engine::initialize() {
    std::cout << "Game Engine initialized" << std::endl;
}

void Game_Engine::update(float deltaTime) {
    // Logique de mise à jour
}
