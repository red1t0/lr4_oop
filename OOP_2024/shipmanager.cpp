#include <vector>
#include <iostream>

#include "field.hpp"
#include "ship.hpp"
#include "shipmanager.hpp"

ShipManager::ShipManager(int num_of_ships, std::vector<int> lenghts, std::vector<Orientation> orientations):num_of_ships(num_of_ships)
{
    for(size_t lenght_iterator=0; lenght_iterator<num_of_ships; lenght_iterator++)
    {
        ships.push_back(new Ship(lenghts[lenght_iterator], orientations[lenght_iterator]));
    }
}

ShipManager::ShipManager(int num_of_ships, std::vector<int> lenghts, 
std::vector<Orientation> orientations, std::vector<std::vector<Condition>> ship_conditions
):num_of_ships(num_of_ships)
{
    for(size_t lenght_iterator=0; lenght_iterator<num_of_ships; lenght_iterator++)
    {
        ships.push_back(new Ship(lenghts[lenght_iterator], 
        orientations[lenght_iterator], ship_conditions[lenght_iterator]));
    }
}

ShipManager::~ShipManager()
{
    for(size_t length_iterator=0; length_iterator< num_of_ships; length_iterator++)
        delete ships[length_iterator];
}

Ship* ShipManager::get_ship(int ind)
{
    if ( ind < 0 || ind >= this->num_of_ships)
    {
        std::cerr << "Invalid index in ShipManager::get_ship" << std::endl;
        exit(1);
    }
    return this->ships[ind];
}

std::vector<int> ShipManager::get_ships_lenghts()
{
    std::vector<int> ships_lenghts = {};
    for (auto ship: this->ships) ships_lenghts.push_back(ship->get_lenght());
    return ships_lenghts;
}

std::vector<Orientation> ShipManager::get_ships_orientations()
{
    std::vector<Orientation> ships_orientations = {};
    for (auto ship: this->ships) ships_orientations.push_back(ship->get_orientation());
    return ships_orientations;
}

std::vector<std::vector<Condition>> ShipManager::get_ships_conditions()
{
    std::vector<std::vector<Condition>> ships_conditions = {};
    for (auto ship: this->ships) ships_conditions.push_back(ship->get_conditions());
    return ships_conditions;
}    
    
void ShipManager::show_info() 
{
    for(size_t index_iterator=0; index_iterator<this->num_of_ships; index_iterator++) this->ships[index_iterator]->print_segments();
    std::cout << std::endl;
}    

int ShipManager::destroyed_number()
{
    int counter = 0;
    for (auto ship: this->ships) if (ship->is_destroyed()) counter++;
    return counter; 
}

bool ShipManager::all_ships_destroyed()
{
    for(auto ship: this->ships) if (!ship->is_destroyed()) return false;
    return true;
}