#pragma once
#include <iostream>
#include <vector>

#define MAX_SHIP_LENGHT 4
#define MIN_SHIP_LENGHT 1

enum class Condition { undamaged, damaged, destroyed};
enum class Orientation { vertical='v', horisontal='h'};

class Ship{
private:

    class Segment{
    private:
        Condition condition;
    public:

        Segment(Condition condition);

        Segment();

        void attack();

        Condition get_condition();

        void set_condition(Condition condition);

    };

    int lenght;
    Orientation orientation;
    std::vector<Segment*> segments; 

public:

    Ship(int lenght, Orientation orientation);

    Ship(int lenght, Orientation orientation, std::vector<Condition> segment_conditions);

    Ship(const Ship& ship);

    Ship& operator = (const Ship& ship);

    ~Ship();

    bool is_destroyed();

    Orientation get_orientation();

    int get_lenght();

    std::vector<Condition> get_conditions();

    void attack_segment(int ind);

    void destroy_segment(int ind);

    void print_segment(int ind);

    void print_segments();

};