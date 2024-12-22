#include "parser.hpp"
#include "myexception.hpp"
#include <iostream>
#include <fstream>

void Parser::set_cotrol()
{
    std::string line;

    std::map<std::string, char> new_map;

    std::vector<char> values;
 
    std::ifstream in("control.txt"); // окрываем файл для чтения
    if (in.is_open())
    {
        while (std::getline(in, line))
        {
            if (line.find('=') == std::string::npos) return ;
            if (!this->commands.count( line.substr(0, line.find('=') ) ) ) return ;
            if ( line.substr( line.find('=') + 1).length() != 1) return ;
            for (auto value: values)
            {
                if (value == line.substr( line.find('=') + 1)[0]) return;
            }
            new_map[line.substr(0, line.find('='))] = line.substr( line.find('=') + 1)[0];
            values.push_back(line.substr( line.find('=') + 1)[0]);
        }
        if (this->commands.size() != new_map.size()) return;

        this->commands = new_map;
    }
    in.close();     // закрываем файл
}

Parser::Parser()
{
    this->commands[std::string("ATTACK")] = 'a';
    this->commands[std::string("USE_ABILITY")] = 'u';
    this->commands[std::string("SAVE")] = 's';
    this->commands[std::string("LOAD_FROM_FILE")] = 'b';
    this->commands[std::string("LOAD_FROM_INPUT")] = 'i';
    this->commands[std::string("HELP")] = 'h';
    this->commands[std::string("STOP")] = 'd';

    this->set_cotrol();

}

char Parser::get_command()
{
    std::cin >> command;

    if (command == commands.at(std::string("ATTACK"))) return commands.at(std::string("ATTACK"));
    if (command == commands.at(std::string("LOAD_FROM_FILE"))) return commands.at(std::string("LOAD_FROM_FILE"));
    if (command == commands.at(std::string("SAVE"))) return commands.at(std::string("SAVE"));
    if (command == commands.at(std::string("LOAD_FROM_INPUT"))) return commands.at(std::string("LOAD_FROM_INPUT"));
    if (command == commands.at(std::string("USE_ABILITY"))) return commands.at(std::string("USE_ABILITY"));
    if (command == commands.at(std::string("STOP"))) return commands.at(std::string("STOP"));

    throw ImproperCommandInput(std::string(1, command));

}