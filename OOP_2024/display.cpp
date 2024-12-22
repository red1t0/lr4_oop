#include "display.hpp"

template <typename T>
Display<T>::Display(Game* game):game(game)
{
    this->render = new Render();
}

template <typename T>
void Display<T>::display_enemy_field()
{
    this->render->display_enemy_field(this->game);
}

template <typename T>
void Display<T>::display_player_field()
{
    this->render->display_player_field(this->game);
}