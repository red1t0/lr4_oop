#include <iostream>
#include "gamemanager.hpp"
#include "display.cpp"
#include "gamemanager.cpp"
#include "display.hpp"
#include "parser.hpp"
#include "render.hpp"

int main()
{
    GameManager<Parser, Render>* gamemanager = new GameManager<Parser, Render>();
    while(true)
    {
        gamemanager->use_command();
    }
    return 0;
}