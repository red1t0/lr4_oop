#include <iostream>
#include <random>
#include <algorithm>
#include "abilities.hpp"
#include "myexception.hpp"

void Scanner::use_skill(Field* field, Flags* flags)
{
    int coord_x, coord_y;
    std::cout << "Put the coords of the bottom left corner of the scanner ability:\n" << std::endl;
    std::cin >> coord_x >> coord_y;
    bool ship_is_in_square = false;
    for(size_t temp_coord_y = coord_y; temp_coord_y < coord_y+SCANNER_Y_SIZE; temp_coord_y++)
        for (size_t temp_coord_x = coord_x; temp_coord_x < coord_x+SCANNER_X_SIZE; temp_coord_x++)  
            if (field->check_ship_in_cell(temp_coord_x, temp_coord_y)) ship_is_in_square = true;
    if (ship_is_in_square) std::cout << "There is ship in the square" << std::endl;
    else std::cout << "There is no ship in the square" << std::endl;
}


void Shelling::use_skill(Field* field, Flags* flags)
{
    std::vector<Ship*> ships;
    for(size_t coord_y=0; coord_y<field->get_height(); coord_y++)
    {
        for(size_t coord_x=0; coord_x<field->get_width(); coord_x++)
        {
            if (field->check_ship_in_cell(coord_x, coord_y))
            {
                bool temp_flag = true;
                for( auto ship: ships) if (ship == field->get_cell(coord_x, coord_y)->get_ship() ) temp_flag = false;
                if (temp_flag) ships.push_back(field->get_cell(coord_x, coord_y)->get_ship());
            }
        }
    }
    if (ships.size() == 0) return;
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(ships.begin(), ships.end(), gen);
    int lenght = ships[0]->get_lenght();
    std::uniform_int_distribution<> distr(0,  lenght-1);
    int rand_segment_index = distr(gen);
    ships[0]->attack_segment(rand_segment_index);
}   
