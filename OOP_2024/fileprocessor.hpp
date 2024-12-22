#pragma once
#include "gamestate.hpp"
#include <fstream>

class FileProcessor
{
    private:

    std::fstream file;

    std::string filename;

    public:
    
    FileProcessor(std::ios::openmode mode, const std::string& filename="save.txt");

    void save_gamestate(GameState* gamestate);

    void load_gamestate(GameState* gamestate);

    std::string get_filename(){return this->filename;}

    ~FileProcessor();
};