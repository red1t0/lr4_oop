#include <iostream>
#include "abilities.hpp"
#include "abilitiesmanager.hpp"
#include "field.hpp"
#include "myexception.hpp"

std::string AbilityUseInEmptyManger::what()
{
    std::string msg = "Empty Abilities Manager\n\0";
    return msg;
}

std::string AttackOutOfBounds::what()
{
    std::string msg = "Attack in field, with height" + std::to_string(field->get_height()) +
    " with width" + std::to_string(field->get_width())+
    "Attack coords are :\n" + std::to_string(coord_x) + " " + std::to_string(coord_y) + "\n\0";
    return msg;
}

std::string CellOutOfBounds::what()
{
    std::string msg = "Cell is out of bounds. Field parameters: height-" + std::to_string(field->get_height()) +
    " width-"+ std::to_string(field->get_width())+ "\n" +
    "Cell coords are: (" + std::to_string(coord_x) + "," + std::to_string(coord_y) + ")\n\0";
    return msg;
}

std::string SetCellOutOfBounds::what()
{
    std::string msg = "Setting cell is out bounds. Field parameters: '\n'height-" + std::to_string(field->get_height()) + '\n' +
    "width-"+ std::to_string(field->get_width())+
    "Cell coords are :\n" + std::to_string(coord_x) + " " + std::to_string(coord_y) + "\n\0";
    return msg;
}

std::string  ShipIntersection::what()
{
    std::string msg = "Shipintersection in field, with height " + std::to_string(field->get_height()) +
    " with width " + std::to_string(field->get_width())+
    " Ship place coords are :\n" + std::to_string(coord_x) + " " + std::to_string(coord_y) + "\n\0";
    return msg;
}


std::string IncorrectShipPlace::what()
{
    std::string msg = "Cant place ship with lenght: " + std::to_string(lenght) +
    " and orientation: " + static_cast<char>(orientation) +  
    + " in the cell(" + std::to_string(coord_x) + "," + std::to_string(coord_y) + ")\n";
    return msg;
}


std::string FileWasChanged::what()
{
    std::string msg = "File was changed. Loading from file is impossible";
    return msg;
}

std::string ImproperCooordsInput::what()
{
    std::string msg = "Improper coords: " + std::to_string(this->x) + std::to_string(this->y) + '\n';
    return msg;
}

std::string ImproperCommandInput::what()
{
    std::string msg = "Cant find command: " + this->input + "\n";
    return msg;
}

std::string ImproperLenghtsInput::what()
{
    std::string msg = "Improper lenght: " + std::to_string(this->lenght) + "\n";
    return msg;
}

std::string ImproperWidthAndHeightInput::what()
{
    std::string msg = "Improper input: " + this->input_string;
    return msg;
}

std::string ImproperShipsNumberInput::what()
{
    std::string msg = "Improper ship number: " + std::to_string(this->num) + '\n';
    return msg;
}

std::string ImproperOrieantationsInput::what()
{
    std::string msg = "Improper orientations input: " + std::to_string(this->input) + '\n';
    return msg;
}

