#pragma once
#include <iostream>
#include <vector>
#include <map>
#include "gamestate.hpp"

class Parser
{
    public:

    std::map<std::string, char> get_commands(){return this->commands;}

    Parser();

    char get_command();

    private:

    std::map<std::string, char> commands;

    char command;

    void set_cotrol();
};