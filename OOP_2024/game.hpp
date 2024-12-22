#pragma once
#include <iostream>
#include "field.hpp"
#include "shipmanager.hpp"
#include "abilities.hpp"
#include "abilitiesmanager.hpp"
#include "myexception.hpp"
#include "flags.hpp"
#include "gamestate.hpp"

class Game
{
    public:

    Game():gamestate(new GameState()){};

    Game(GameState* gamestate):gamestate(gamestate){}

    GameState* get_gamestate(){return this->gamestate;}

    void player_attack(int x_coord, int y_coord);

    void use_ability();

    void enemy_attack();

    bool player_lost(){return this->get_gamestate()->player_shipmanager->all_ships_destroyed();}

    bool enemy_lost(){return this->get_gamestate()->enemy_shipmanager->all_ships_destroyed();}

    void save_to_file(const char* filename="save.txt");

    void load_from_file(const char* filename="save.txt");

    void load_from_input(int width, int height, int player_ship_number,
    std::vector<int> player_ships_lenghts,
    std::vector<Orientation> player_ships_orientations,
    std::vector<std::vector<int>> player_ships_coordinates);

    private:

    void arrange_player_ships();

    void ararnge_enemy_ships();

    GameState* gamestate;
    
};