#include <iostream>
#include <vector>
#include "ship.hpp"
#include "field.hpp"
#include "myexception.hpp"

void Field::Cell::set_status(CellStatus status)
{
    switch (status)
    {
    case CellStatus::empty:
        this->cellstatus = CellStatus::empty;
        break;
    case CellStatus::ship:
        this->cellstatus = CellStatus::ship;
        break;
    default:
        std::cerr << "Default in Cell->set_status" << std::endl;
        break;
    }
}

void Field::Cell::set_ship(Ship* ship, int ind) {this->ship = ship; this->ind = ind;}

CellStatus Field::Cell::get_status() {return this->cellstatus;}

Ship* Field::Cell::get_ship() {return this->ship;}

int Field::Cell::get_ind() {return this->ind;}

Field::Field(int width, int height):width(width),height(height)
{
        for(size_t coord_y=0; coord_y < this->height; coord_y++)
        {
            std::vector<Cell*> cell_array;
            for(size_t coord_x=0;coord_x<this->width; coord_x++) cell_array.push_back(new Cell());
            this->cells.push_back(cell_array);
        }
}

Field::~Field()
{
    for(size_t coord_y=0; coord_y < this->height; coord_y++)
        for(size_t coord_x=0; coord_x< this->width; coord_x++)
            delete this->cells[coord_y][coord_x];
}

Field::Field(const Field& field):width(field.width),height(field.height)
{
    for(size_t coord_y=0; coord_y<this->height; coord_y++)
    {
        std::vector<Cell*> cell_array;
        for(size_t coord_x=0; coord_x<this->width; coord_x++) cell_array.push_back(new Cell());
        this->cells.push_back(cell_array);
    }
    for(size_t coord_y=0; coord_y<this->height; coord_y++)
    {
        for(size_t coord_x=0; coord_x<this->width; coord_x++)
        {
            if ( field.cells[coord_y][coord_x]->get_ship() != nullptr)
            {
                Ship* new_ship = new Ship(*field.cells[coord_y][coord_x]->get_ship());
                {
                    for(size_t temp_coord_y=0; temp_coord_y<this->height; temp_coord_y++)
                    {
                        for(size_t temp_coord_x=0; temp_coord_x<this->width; temp_coord_x++)
                        {
                            if ( field.cells[coord_y][coord_x]->get_ship() == field.cells[temp_coord_y][temp_coord_x]->get_ship() )
                            {
                                int temp_ind = field.cells[temp_coord_y][temp_coord_x]->get_ind();

                                this->cells[temp_coord_y][temp_coord_x]->set_ship(new_ship, temp_ind);
                            }
                        }
                    }
                }
            }
        }
    }
}

Field& Field::operator = (const Field& field)
{
    Field temp_field(field);
    std::swap(this->height, temp_field.height);
    std::swap(this->width, temp_field.width);
    std::swap(this->cells, temp_field.cells);
    return *this;
}

Field::Field(Field&& field):width(0),height(0),cells(0){std::swap(this->cells, field.cells);}

Field& Field::operator = (Field&& field){
    if (this != & field)
    {
        std::swap(this->height, field.height);
        std::swap(this->width, field.width);
        std::swap(this->cells, field.cells);
    }
    return *this;
}

Field::Cell* Field::get_cell(int coord_x, int coord_y)
{
    if ( coord_x < this->width && coord_x >= 0 && coord_y < this->height && coord_y >= 0)
        return this->cells[height-1-coord_y][coord_x];
    else
    {
        throw CellOutOfBounds(this, coord_x, coord_y);
    }
}

void Field::set_cell(int coord_x, int coord_y,Ship* ship, int ind)
{
    try{
        (this->get_cell(coord_x, coord_y))->set_ship(ship, ind);
        (this->get_cell(coord_x, coord_y))->set_status(CellStatus::ship);
    }catch(CellOutOfBounds& e)
    {
        throw SetCellOutOfBounds(this, coord_x, coord_y);
    }
}

bool Field::check_ship_in_cell(int coord_x, int coord_y)
{
    Cell* cell = nullptr;
    try{
        Cell* cell = get_cell(coord_x, coord_y);
        return cell->get_ship() != nullptr;
        }
    catch(CellOutOfBounds& e){
        return false;}
}

bool Field::check_ship_in_square(int coord_x, int coord_y)
{
    return ( check_ship_in_cell(coord_x-1, coord_y) || check_ship_in_cell(coord_x-1, coord_y+1) || check_ship_in_cell(coord_x-1, coord_y-1) ||
    check_ship_in_cell(coord_x, coord_y) || check_ship_in_cell(coord_x, coord_y+1) || check_ship_in_cell(coord_x, coord_y-1) ||
    check_ship_in_cell(coord_x+1, coord_y) || check_ship_in_cell(coord_x+1, coord_y+1) || check_ship_in_cell(coord_x+1, coord_y-1) );
}

void Field::check_ship_intersection(int coord_x, int coord_y, Ship* ship)
{
    for(size_t index_counter = 0; index_counter < ship->get_lenght(); index_counter++)
    {
        if (ship->get_orientation() == Orientation::horisontal)
        {
            if (check_ship_in_square(coord_x+index_counter, coord_y)) throw ShipIntersection(this, coord_x+index_counter, coord_y);
        }else
        {
            if (check_ship_in_square(coord_x, coord_y+index_counter)) throw ShipIntersection(this, coord_x, coord_y+index_counter);
        }
    }
}

void Field::place_ship(int coord_x, int coord_y, Ship* ship)
{
    try{check_ship_intersection(coord_x, coord_y, ship);}
    catch(ShipIntersection& e) {throw e;}
    for(size_t index_counter = 0; index_counter < ship->get_lenght(); index_counter++)
    {
        if (ship->get_orientation() == Orientation::horisontal)
        {
            if (coord_x+index_counter >= this->width || coord_x+index_counter < 0 || coord_y >= this->height || coord_y < 0)
                throw(IncorrectShipPlace(this, coord_x+index_counter, coord_y, ship->get_orientation(), ship->get_lenght()) );
        }
        else
        {
            if (coord_x >= this->width || coord_x < 0 || coord_y+index_counter >= this->height || coord_y+index_counter < 0)
                throw(IncorrectShipPlace(this, coord_x, coord_y+index_counter, ship->get_orientation(), ship->get_lenght()) );
        }
    }

    for(size_t index_counter = 0; index_counter < ship->get_lenght(); index_counter++)
    {
        if (ship->get_orientation() == Orientation::horisontal)
        {
            this->set_cell(coord_x+index_counter, coord_y, ship, index_counter);
        }else this->set_cell(coord_x, coord_y+index_counter, ship, index_counter);
    }
}

void Field::attack_cell(int coord_x, int coord_y, bool double_attack)
{
    Cell* attacking_cell = nullptr;
    try{
        attacking_cell = this->get_cell(coord_x, coord_y);
    }catch (CellOutOfBounds& e){throw AttackOutOfBounds(this, coord_x, coord_y);}
    switch (attacking_cell->get_status())
    {
    case CellStatus::ship:
    {
        int attack_index = attacking_cell->get_ind();
        attacking_cell->get_ship()->attack_segment(attack_index);
        if (double_attack) attacking_cell->get_ship()->destroy_segment(attack_index);
        break;
    }
    case CellStatus::empty:
        break;
    case CellStatus::unknown:
        if ( attacking_cell->get_ship() != nullptr)
        {
            attacking_cell->set_status(CellStatus::ship);
            this->attack_cell(coord_x, coord_y, double_attack);
        }
        else attacking_cell->set_status(CellStatus::empty);
        break;
    default:
        std::cout << "Default in Field::attack_cell" << std::endl;
        break;
    }
}

void Field::print()
{
    for(size_t coord_x=0; coord_x<this->height; coord_x++)
    {
        for(size_t coord_y=0; coord_y<this->width; coord_y++)
        {
            if (this->cells[coord_x][coord_y]->get_status() == CellStatus::ship)
                this->cells[coord_x][coord_y]->get_ship()->print_segment(this->cells[coord_x][coord_y]->get_ind());
            else
                std::cout << static_cast<char>(this->cells[coord_x][coord_y]->get_status()) << " ";
        }
        std::cout << std::endl;
    }
}