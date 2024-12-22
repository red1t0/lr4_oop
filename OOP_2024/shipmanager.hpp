#pragma once
#include <vector>
#include <iostream>

#include "field.hpp"
#include "ship.hpp"

class ShipManager
{
private:
    const int num_of_ships;
    std::vector<Ship*> ships;
public:
    ShipManager(int num_of_ships, std::vector<int> lenghts, std::vector<Orientation> orientations);

    ShipManager(int num_of_ships, std::vector<int> lenghts, 
    std::vector<Orientation> orientations, std::vector<std::vector<Condition>> ship_conditions);

    int get_ships_number(){return this->ships.size();}

    std::vector<int> get_ships_lenghts();

    std::vector<Orientation> get_ships_orientations();

    std::vector<std::vector<Condition>> get_ships_conditions();

    ~ShipManager();

    Ship* get_ship(int ind);

    int destroyed_number();

    bool all_ships_destroyed();
    
    void show_info();

};