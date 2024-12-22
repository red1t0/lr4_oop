#include <iostream>
#include "abilitiesmanager.hpp"
#include "myexception.hpp"
#include "flags.hpp"

AbilitiesManager::AbilitiesManager()
{
    std::vector<Iability*> temp_vector = {new Scanner, new Double_damage, new Shelling};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(temp_vector.begin(), temp_vector.end(), gen);
    abilities = temp_vector;
}

void AbilitiesManager::use_ability(Field* field, Flags* flags)
{
    if (!abilities.size())
    {
        throw(AbilityUseInEmptyManger(this));
    }else{
        abilities[0]->use_skill(field, flags);
        abilities.erase(abilities.begin());
    }
}

void AbilitiesManager::add_ability()
{
    std::vector<Iability*> temp_vector = {new Scanner, new Double_damage, new Shelling};
    std::random_device rd;
    std::mt19937 gen(rd());
    std::shuffle(temp_vector.begin(), temp_vector.end(), gen);
    abilities.push_back(temp_vector[0]);
}

void AbilitiesManager::print_abilityes()
{
    std::cout << "Number of abilityes available: "<<  abilities.size() << std::endl;
    std::cout << "Available abilityes:" << std::endl;
    for (auto ability: abilities) std::cout << ability->as_string() << std::endl;
    std::cout << std::endl;
}
