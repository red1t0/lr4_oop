#pragma once
#include <random>
#include <algorithm>
#include <vector>
#include "abilities.hpp"
#include "field.hpp"
#include "flags.hpp"

class AbilitiesManager
{
    private:
    
    std::vector<Iability*> abilities;

    public:

    AbilitiesManager();

    int size(){return abilities.size();}

    void use_ability(Field* field, Flags* flags);

    void add_ability();

    void print_abilityes();

    void pop(){if (!this->abilities.empty()) this->abilities.pop_back();}

};