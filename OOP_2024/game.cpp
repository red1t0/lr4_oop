#include <iostream>
#include <random>
#include <algorithm>
#include <ctime>
#include "game.hpp"
#include "fileprocessor.hpp"


void Game::player_attack(int x_coord, int y_coord) // атака пользователя
{
    int destroyed_number_before = this->get_gamestate()->enemy_shipmanager->destroyed_number();
    try{
        this->get_gamestate()->enemy_field->attack_cell(x_coord, y_coord, this->get_gamestate()->flags->double_damage);
        if (this->get_gamestate()->flags->double_damage) this->get_gamestate()->flags->double_damage=false;;
    }catch(AttackOutOfBounds& e)
    {
        std::cout << e.what();
        return;
    }
    int destroyed_nuber_after = this->get_gamestate()->enemy_shipmanager->destroyed_number();
    if ( destroyed_nuber_after > destroyed_number_before) this->get_gamestate()->abilitiesmanager->add_ability();
}

void Game::enemy_attack() // атака противника (рандом)
{
    srand((unsigned)time(0)); 
    int coord_x, coord_y;
    coord_x = (rand()%this->get_gamestate()->player_field->get_width());
    coord_y = (rand()%this->get_gamestate()->player_field->get_height());
    try
    {
        this->get_gamestate()->player_field->attack_cell(coord_x, coord_y, false);
    }catch(AttackOutOfBounds& e){}
}

void Game::use_ability() // Ипользование способности
{
    int destroyed_number_before = this->get_gamestate()->enemy_shipmanager->destroyed_number();
    try{
        this->get_gamestate()->abilitiesmanager->use_ability(this->get_gamestate()->enemy_field, this->get_gamestate()->flags);
    }catch(AbilityUseInEmptyManger& e)
    {
        std::cout << e.what();
        return;
    }
    int destroyed_nuber_after = this->get_gamestate()->enemy_shipmanager->destroyed_number();
    if ( destroyed_nuber_after > destroyed_number_before) this->get_gamestate()->abilitiesmanager->add_ability();
}

void Game::arrange_player_ships() // Расставить корабли пользователя (внутренняя функция)
{
    for (size_t lenght_iterator=0; lenght_iterator<this->get_gamestate()->player_ships_coordinates.size(); lenght_iterator++)
    {
        try{
            this->get_gamestate()->player_field->place_ship(
                this->get_gamestate()->player_ships_coordinates[lenght_iterator][0], 
                this->get_gamestate()->player_ships_coordinates[lenght_iterator][1],
            this->get_gamestate()->player_shipmanager->get_ship(lenght_iterator));
        }catch(ShipIntersection& e)
        {
            std::cout << e.what();
        }catch(IncorrectShipPlace& e)
        {
            std::cout<< e.what();
        }
    }
}

void Game::ararnge_enemy_ships() // Расставить корабли противника (внутренняя функция)
{
    for (size_t lenght_iterator=0; lenght_iterator<this->get_gamestate()->enemy_ships_coordinates.size(); lenght_iterator++)
    {
        try{
            this->get_gamestate()->enemy_field->place_ship(
                this->get_gamestate()->enemy_ships_coordinates[lenght_iterator][0], 
                this->get_gamestate()->enemy_ships_coordinates[lenght_iterator][1],
            this->get_gamestate()->enemy_shipmanager->get_ship(lenght_iterator));
        }catch(ShipIntersection& e){}
        catch(IncorrectShipPlace& e){}
    }
}

void Game::save_to_file(const char* filename) // Сохраниться в файл
{
    try{
    FileProcessor* fileprocessor = new FileProcessor(std::ios::out, filename);
    fileprocessor->save_gamestate(this->get_gamestate());
    } catch (std::runtime_error e)
    {
        std::cout << e.what() << std::endl;
        return;
    }   
}

void Game::load_from_file(const char* filename) // Загрузиться из файла
{   
    try{
    FileProcessor* fileprocessor = new FileProcessor(std::ios::in, filename);
    fileprocessor->load_gamestate(this->get_gamestate());
    this->arrange_player_ships();
    this->ararnge_enemy_ships();
    } catch (std::runtime_error& e){throw e;} 
    catch (FileWasChanged& e){throw e;}
}

void Game::load_from_input(int width, int height, int player_ship_number, // Загрузиться из ввода
    std::vector<int> player_ships_lenghts,
    std::vector<Orientation> player_ships_orientations,
    std::vector<std::vector<int>> player_ships_coordinates)
{
    this->get_gamestate()->player_ships_coordinates = player_ships_coordinates;
    this->get_gamestate()->player_field = new Field(width, height);
    this->get_gamestate()->player_shipmanager = new ShipManager(player_ship_number, player_ships_lenghts, player_ships_orientations);
    this->arrange_player_ships();

    // add random to enemy
    srand((unsigned)time(0)); 
    std::vector<std::vector<int>> enemy_ships_coordinates;
    std::vector<int> enemy_ships_lenghts;
    std::vector<Orientation> enemy_ships_orientations;
    for(size_t i=0;i<player_ship_number;i++)
    {
        enemy_ships_lenghts.push_back(rand()%MAX_SHIP_LENGHT+1);
        enemy_ships_orientations.push_back(rand()%2 == 0 ? Orientation::horisontal : Orientation::vertical);
        enemy_ships_coordinates.push_back({rand()%width, rand()%height});
    }

    this->get_gamestate()->enemy_ships_coordinates = enemy_ships_coordinates;
    this->get_gamestate()->enemy_field = new Field(width, height);
    this->get_gamestate()->enemy_shipmanager = new ShipManager(player_ship_number, enemy_ships_lenghts, enemy_ships_orientations);
    this->ararnge_enemy_ships();

}