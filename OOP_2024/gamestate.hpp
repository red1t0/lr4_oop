#pragma once
#include <iostream>
#include "field.hpp"
#include "shipmanager.hpp"
#include "abilities.hpp"
#include "abilitiesmanager.hpp"
#include "myexception.hpp"
#include "flags.hpp"

class GameState
{
    public:

    GameState();

    GameState(int width, int height, int player_ship_number, int enemy_ship_number, 
    std::vector<int> player_ships_lenghts,
    std::vector<int> enemy_ships_lenghts,
    std::vector<Orientation> player_ships_orientations,
    std::vector<Orientation> enemy_ships_orientations, 
    std::vector<std::vector<int>> player_ships_coordinates, 
    std::vector<std::vector<int>> enemy_ships_coordinates);
    
    Field* player_field;
    Field* enemy_field;
    std::vector<std::vector<int>> player_ships_coordinates;
    std::vector<std::vector<int>> enemy_ships_coordinates;
    ShipManager* player_shipmanager;
    ShipManager* enemy_shipmanager;
    AbilitiesManager* abilitiesmanager;
    Flags* flags;

    std::string get_data_for_output() const;

    void get_data_from_input(std::string hash, std::string field_data, std::string player_data, std::string enemy_data);

};


std::ostream& operator << (std::ostream &os, const GameState &gamestate);

std::istream& operator >> (std::istream& in, GameState &gamestate);