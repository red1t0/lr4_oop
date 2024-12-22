#include "render.hpp"
#include "game.hpp"
#include <iostream>

void Render::display_player_field(Game* game)
{
    Field* field = game->get_gamestate()->player_field;

    for(size_t coord_x=0; coord_x<field->get_height(); coord_x++)
    {
        for(size_t coord_y=0; coord_y<field->get_width(); coord_y++)
        {
            if (field->get_cell(coord_x, coord_y)->get_status() == CellStatus::ship)
                field->get_cell(coord_x, coord_y)->get_ship()->print_segment(field->get_cell(coord_x, coord_y)->get_ind());
            else
                std::cout << static_cast<char>(field->get_cell(coord_x, coord_y)->get_status()) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}

void Render::display_enemy_field(Game* game)
{
    Field* field = game->get_gamestate()->enemy_field;

    for(size_t coord_x=0; coord_x<field->get_height(); coord_x++)
    {
        for(size_t coord_y=0; coord_y<field->get_width(); coord_y++)
        {
            if (field->get_cell(coord_x, coord_y)->get_status() == CellStatus::ship)
                field->get_cell(coord_x, coord_y)->get_ship()->print_segment(field->get_cell(coord_x, coord_y)->get_ind());
            else
                std::cout << static_cast<char>(field->get_cell(coord_x, coord_y)->get_status()) << " ";
        }
        std::cout << std::endl;
    }

    std::cout << std::endl;
}