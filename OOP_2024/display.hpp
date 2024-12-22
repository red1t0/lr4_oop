#pragma once
#include "game.hpp"
#include "render.hpp"

template <typename T>
class Display
{
    public:

    Display(Game* game);

    void display_player_field();

    void display_enemy_field();

    private:

    T* render;

    Game* game;


};