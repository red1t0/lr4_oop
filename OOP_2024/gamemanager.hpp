#pragma once
#include "game.hpp"
#include "parser.hpp"
#include "input.hpp"
#include "display.hpp"

template <typename T, typename G>
class GameManager
{
    public:

    bool game_started;

    GameManager();

    void use_command();

    Game* game;

    T* parser;

    Input* input;

    Display<G>* display;

    private:

    void load_from_file();

    void load_from_input();

    void save_to_file();

    void attack();

    void use_ability();

};