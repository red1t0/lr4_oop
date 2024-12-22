#include "gamemanager.hpp"
#include "parser.hpp"
#include "myexception.hpp"
#include "input.hpp"
#include "display.hpp"
#include <iostream>

template <typename T, typename G>
GameManager<T, G>::GameManager()
{
    this->game = new Game();
    this->parser = new Parser();
    this->input = new Input();
    this->display = new Display<G>(this->game);
    this->game_started = false;
}

template <typename T, typename G>
void GameManager<T, G>::load_from_file()
{
    try{
            this->game->load_from_file();
            this->game_started = true;
    }
    catch(std::runtime_error& e){std::cerr << e.what() << std::endl;}
    catch(FileWasChanged& e){std::cerr << e.what() << std::endl << std::endl;}

    this->display->display_player_field();
    this->display->display_enemy_field();
}

template <typename T, typename G>
void GameManager<T, G>::load_from_input()
{
    try{

    std::vector<int> width_and_height = this->input->get_width_and_height();
    int ships_number = this->input->get_ships_number();
    std::vector<int> player_ships_lenghts = this->input->get_ships_lenghts(ships_number);

    std::vector<Orientation> player_ships_orientations = this->input->get_ships_orientations(ships_number);

    std::vector<std::vector<int>> player_ships_coordinates = this->input->get_coordinates(ships_number);

    this->game->load_from_input(width_and_height[0], width_and_height[1], ships_number, // Загрузиться из ввода
    player_ships_lenghts,
    player_ships_orientations,
    player_ships_coordinates);

    this->game_started = true;

    this->display->display_player_field();
    this->display->display_enemy_field();
    }
    catch (ImproperCooordsInput& e) {std::cerr << e.what() << std::endl;}
    catch (ImproperLenghtsInput& e) {std::cerr << e.what() << std::endl;}
    catch (ImproperOrieantationsInput& e) {std::cerr << e.what() << std::endl;}
    catch (ImproperShipsNumberInput& e) {std::cerr << e.what() << std::endl;}
    catch( ImproperWidthAndHeightInput& e) {std::cerr << e.what() << std::endl;}
}

template <typename T, typename G>
void GameManager<T, G>::save_to_file()
{
    if (!this->game_started)
    {
        std::cout << "Game hasnt started yet\n";
        return;
    }
    this->game->save_to_file();
}


template <typename T, typename G>
void GameManager<T, G>::attack()
{
    if (!this->game_started)
    {
        std::cout << "Game hasnt started yet\n";
        return;
    }
    try
    {
        std::vector<int> coords = this->input->get_attack_coords();
        this->game->player_attack(coords[0], coords[1]);

        this->display->display_player_field();
        this->display->display_enemy_field();
    }
    catch ( ImproperCooordsInput& e ) {std::cerr << e.what() << std::endl;}
}

template <typename T, typename G>
void GameManager<T, G>::use_ability()
{
    if (!this->game_started)
    {
        std::cout << "Game hasnt started yet\n";
        return;
    }
    this->game->use_ability();

    this->display->display_player_field();
    this->display->display_enemy_field();
}

template <typename T, typename G>
void GameManager<T, G>::use_command()
{
    try{
        
    char command = this->parser->get_command();

    if (command == this->parser->get_commands().at(std::string("ATTACK")))
    {
        this->attack();
        return;
    }
    if (command == this->parser->get_commands().at(std::string("LOAD_FROM_FILE")))
    {
        this->load_from_file();
        return;
    }
    if (command == this->parser->get_commands().at(std::string("SAVE")))
    {
        this->save_to_file();
        return;
    }
    if (command == this->parser->get_commands().at(std::string("LOAD_FROM_INPUT")))
    {
        this->load_from_input();
        return;
    }
    if (command == this->parser->get_commands().at(std::string("USE_ABILITY")))
    {
        this->use_ability();
        return;
    }
    if (command == this->parser->get_commands().at(std::string("STOP"))) {}


    } catch (ImproperCommandInput& e) {std::cerr << e.what();}
}