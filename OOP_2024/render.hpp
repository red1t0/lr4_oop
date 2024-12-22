#pragma once
#include "game.hpp"

class Render
{
    public:
    Render(){};

    void display_player_field(Game* game);

    void display_enemy_field(Game* game);
};