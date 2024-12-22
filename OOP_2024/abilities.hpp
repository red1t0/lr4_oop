#pragma once
#include <iostream>
#include <string>
#include "field.hpp"
#include "flags.hpp"

#define SCANNER_X_SIZE 2
#define SCANNER_Y_SIZE 2

class Iability
{
public:
    virtual void use_skill(Field* field, Flags* flags) = 0;
    virtual std::string as_string() = 0;
};

class Double_damage: public Iability
{
    public:

    void use_skill(Field* field, Flags* flags) override {flags->double_damage = true;}

    std::string as_string(){return "Double damage ability";}

};

class Scanner: public Iability
{
    public:

    void use_skill(Field* field, Flags* flags) override;

    std::string as_string(){return "Scanner ability";}

};

class Shelling: public Iability
{
    public:

    void use_skill(Field* field, Flags* flags) override;

    std::string as_string(){return "Shelling ability";}
};




