#pragma once
#include <vector>
#include <iostream>
#include "ship.hpp"

class Input
{
    public:

    Input(){}

    std::vector<int> get_attack_coords();

    std::vector<int> get_width_and_height();

    int get_ships_number();

    std::vector<int> get_ships_lenghts(int ships_number);

    std::vector<Orientation> get_ships_orientations(int ships_number);

    std::vector<std::vector<int>> get_coordinates(int ships_number);

    const char* get_filename();
};