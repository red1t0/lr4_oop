#include <iostream>
#include <string>
#include <bits/stdc++.h>
#include <unordered_map>
#include "myexception.hpp"
#include "gamestate.hpp"


GameState::GameState()
{
    this->player_field = new Field(0, 0);
    this->player_shipmanager = new ShipManager(0, {},{});
    this->abilitiesmanager = new AbilitiesManager();
    this->enemy_field = new Field(0, 0);
    this->enemy_shipmanager = new ShipManager(0, {}, {});
    this->flags = new Flags();
}


GameState::GameState // для инициализации из ввода
    (int width, int height, int player_ship_number, int enemy_ship_number, 
    std::vector<int> player_ships_lenghts,
    std::vector<int> enemy_ships_lenghts,
    std::vector<Orientation> player_ships_orientations,
    std::vector<Orientation> enemy_ships_orientations, 
    std::vector<std::vector<int>> player_ships_coordinates, 
    std::vector<std::vector<int>> enemy_ships_coordinates)
    :player_ships_coordinates(player_ships_coordinates),
    enemy_ships_coordinates(enemy_ships_coordinates)
{
    this->player_field = new Field(width, height);
    this->player_shipmanager = new ShipManager(player_ship_number, player_ships_lenghts,
    player_ships_orientations);
    this->abilitiesmanager = new AbilitiesManager();
    this->enemy_field = new Field(width, height);
    this->enemy_shipmanager = new ShipManager(enemy_ship_number, enemy_ships_lenghts, 
    enemy_ships_orientations);
    this->flags = new Flags();
 }


std::string GameState::get_data_for_output() const
{
    std::string player_data, enemy_data, field_data, hash;

    field_data = std::to_string(this->player_field->get_width()) + 
    "|" + std::to_string(this->player_field->get_height());

    player_data = std::to_string(this->player_shipmanager->get_ships_number());
    for (auto elem: this->player_shipmanager->get_ships_lenghts()) player_data += "|" + std::to_string(elem);
    for(size_t i=0; i<this->player_shipmanager->get_ships_number(); i++)
    {
        if (this->player_shipmanager->get_ships_orientations()[i] == Orientation::horisontal) player_data += "|h";
        else player_data += "|v";
    }
    for (auto elem: this->player_ships_coordinates) player_data += "|" + std::to_string(elem[0]) + "," + std::to_string(elem[1]);
    for (auto elem: this->player_shipmanager->get_ships_conditions())
    {
        player_data += "|";
        for (auto condition: elem) player_data += std::to_string(static_cast<int>(condition));
    }
    player_data += "|" + std::to_string(this->abilitiesmanager->size());
    player_data += "|" + std::to_string(static_cast<int>(this->flags->double_damage));

    enemy_data = std::to_string(this->enemy_shipmanager->get_ships_number());
    for (auto elem: this->enemy_shipmanager->get_ships_lenghts()) enemy_data += "|" + std::to_string(elem);
    for(size_t i=0; i<this->enemy_shipmanager->get_ships_number(); i++)
    {
        if (this->enemy_shipmanager->get_ships_orientations()[i] == Orientation::horisontal) enemy_data += "|h";
        else enemy_data += "|v";
    }
    for (auto elem: this->enemy_ships_coordinates) enemy_data += "|" + std::to_string(elem[0]) + "," + std::to_string(elem[1]);
    for (auto elem: this->enemy_shipmanager->get_ships_conditions())
    {
        enemy_data += "|";
        for (auto condition: elem) enemy_data += std::to_string(static_cast<int>(condition));
    }

    hash = std::to_string(std::hash<std::string>{}(field_data + "\n" + player_data + "\n" + enemy_data));

    return hash + "\n" + field_data + "\n" + player_data + "\n" + enemy_data;
}

void GameState::get_data_from_input(std::string hash, std::string field_data, std::string player_data, std::string enemy_data)
{

    std::string hash_from_file = std::to_string(std::hash<std::string>{}(field_data + "\n" + player_data + "\n" + enemy_data));

    if (hash.compare(hash_from_file)) throw FileWasChanged("");


    int width, height, player_ship_number, enemy_ship_number;

    std::vector<int> player_ships_lenghts;
    std::vector<Orientation> player_ships_orientations;
    std::vector<std::vector<int>> player_ships_coordinates;
    std::vector<std::vector<Condition>> player_ships_conditions;
    int abilities_manager_size;
    bool double_damage_flag;

    std::vector<int> enemy_ships_lenghts;
    std::vector<Orientation> enemy_ships_orientations;
    std::vector<std::vector<int>> enemy_ships_coordinates;
    std::vector<std::vector<Condition>> enemy_ships_conditions;


    width = std::stoi(field_data.substr(0, field_data.find('|')));
    height = std::stoi(field_data.substr(field_data.find('|')+1));

    std::stringstream stream_player_data(player_data);
    std::string elem_from_player_data;
    int player_elem_counter = -1;
    while(!stream_player_data.eof())
    {
        player_elem_counter++;
        getline(stream_player_data, elem_from_player_data, '|');
        if (player_elem_counter == 0) player_ship_number = std::stoi(elem_from_player_data);
        if (player_elem_counter > player_ship_number*0 && player_elem_counter <= player_ship_number*1) 
            player_ships_lenghts.push_back(std::stoi(elem_from_player_data));
        if (player_elem_counter > player_ship_number*1 && player_elem_counter <= player_ship_number*2) 
            player_ships_orientations.push_back(
                elem_from_player_data == "h" ? Orientation::horisontal : Orientation::vertical);
        if (player_elem_counter > player_ship_number*2 && player_elem_counter <= player_ship_number*3) 
            player_ships_coordinates.push_back(
                {std::stoi(elem_from_player_data.substr(0, elem_from_player_data.find(','))),
                 std::stoi(elem_from_player_data.substr(elem_from_player_data.find(',')+1))});
        if (player_elem_counter > player_ship_number*3 && player_elem_counter <= player_ship_number*4)
            {
                std::vector<Condition> temp_conditions;
                for (auto condition: elem_from_player_data)
                    temp_conditions.push_back(condition == '0' ? 
                    Condition::undamaged :condition == '1' ?
                    Condition::damaged : Condition::destroyed);
                player_ships_conditions.push_back(temp_conditions);
            }
        if (player_elem_counter == player_ship_number*4 + 1)
            abilities_manager_size = std::stoi(elem_from_player_data);
        if (player_elem_counter == player_ship_number*4+ 2)
            double_damage_flag = static_cast<bool>(std::stoi(elem_from_player_data));
    }

    std::stringstream stream_enemy_data(enemy_data);
    std::string elem_from_enemy_data;
    int enemy_elem_counter = -1;
    while(!stream_enemy_data.eof())
    {
        enemy_elem_counter++;
        getline(stream_enemy_data, elem_from_enemy_data, '|');
        if (enemy_elem_counter == 0) enemy_ship_number = std::stoi(elem_from_enemy_data);
        if (enemy_elem_counter > enemy_ship_number*0 && enemy_elem_counter <= enemy_ship_number*1) 
            enemy_ships_lenghts.push_back(std::stoi(elem_from_enemy_data));
        if (enemy_elem_counter > enemy_ship_number*1 && enemy_elem_counter <= enemy_ship_number*2) 
            enemy_ships_orientations.push_back(
                elem_from_enemy_data == "h" ? Orientation::horisontal : Orientation::vertical);
        if (enemy_elem_counter > enemy_ship_number*2 && enemy_elem_counter <= enemy_ship_number*3) 
            enemy_ships_coordinates.push_back(
                {std::stoi(elem_from_enemy_data.substr(0, elem_from_enemy_data.find(','))),
                 std::stoi(elem_from_enemy_data.substr(elem_from_enemy_data.find(',')+1))});
        if (enemy_elem_counter > enemy_ship_number*3 && enemy_elem_counter <= enemy_ship_number*4)
            {
                std::vector<Condition> temp_conditions;
                for (auto condition: elem_from_enemy_data)
                    temp_conditions.push_back(condition == '0' ? 
                    Condition::undamaged :condition == '1' ?
                    Condition::damaged : Condition::destroyed);
                enemy_ships_conditions.push_back(temp_conditions);
            }   
    }

    this->player_field = new Field(width, height);
    this->player_shipmanager = new ShipManager(enemy_ship_number, player_ships_lenghts,
    player_ships_orientations, player_ships_conditions);
    this->abilitiesmanager = new AbilitiesManager();
    this->enemy_field = new Field(width, height);
    this->enemy_shipmanager = new ShipManager(enemy_ship_number, enemy_ships_lenghts, 
    enemy_ships_orientations, enemy_ships_conditions);
    this->player_ships_coordinates = player_ships_coordinates;
    this->enemy_ships_coordinates = enemy_ships_coordinates;
    this->flags = new Flags();
    if (double_damage_flag) this->flags->double_damage = true;
    if (abilities_manager_size < 3) while (this->abilitiesmanager->size() != abilities_manager_size) this->abilitiesmanager->pop();
    if (abilities_manager_size > 3) while (this->abilitiesmanager->size() != abilities_manager_size) this->abilitiesmanager->add_ability();

}

std::ostream& operator << (std::ostream &os, const GameState &gamestate)
{
    return os << gamestate.get_data_for_output();
}

std::istream& operator >> (std::istream& in, GameState &gamestate)
{
    std::string field_data, player_data, enemy_data, hash;
    std::getline(in, hash);
    std::getline(in, field_data);
    std::getline(in, player_data);
    std::getline(in, enemy_data);
    try{
        gamestate.get_data_from_input(hash, field_data, player_data, enemy_data);
    } catch (FileWasChanged& e) {throw e;}
    return in;
}
