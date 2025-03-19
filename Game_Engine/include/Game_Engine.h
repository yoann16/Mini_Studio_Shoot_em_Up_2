#pragma once
#include <SFML/Graphics.hpp>
#include "KT_Array.h"
class Game_Engine 
{
public:
    Game_Engine();
    ~Game_Engine();

    void initialize();
    void update(float deltaTime);
    KT::Array <int, 1> t;

private:
    // Propriétés du moteur
};
