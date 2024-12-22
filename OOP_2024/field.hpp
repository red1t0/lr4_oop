#pragma once
#include <iostream>
#include <vector>
#include "ship.hpp"

#define VOID_INDEX -1

enum class CellStatus { unknown='*', empty='_', ship};

class Field
{
private:

    class Cell
    {
    private:

        Ship* ship;
        int  ind;
        CellStatus cellstatus;

    public:

        Cell():ship(nullptr),ind(VOID_INDEX),cellstatus(CellStatus::empty){}

        void set_status(CellStatus status);

        void set_ship(Ship* ship, int ind);

        CellStatus get_status();

        Ship* get_ship();

        int get_ind();
    };

    int width, height;
    std::vector< std::vector<Cell*>> cells;

    bool check_ship_in_square(int coord_x, int coord_y);

    void check_ship_intersection(int coord_x, int coord_y, Ship* ship);

    void set_cell(int coord_x, int coord_y, Ship* ship=nullptr, int ind=VOID_INDEX);

public:

    Field(int width, int height);

    ~Field();

    Field(const Field& field);

    Field& operator = (const Field& field);

    Field(Field&& field);

    Field& operator = (Field&& field);

    int get_width(){return this->width;}

    int get_height(){return this->height;}

    bool check_ship_in_cell(int coord_x, int coord_y);
    
    Cell* get_cell(int coord_x, int coord_y);

    void place_ship(int coord_x, int coord_y, Ship* ship);

    void attack_cell(int coord_x, int coord_y, bool double_attack);

    void print();

};