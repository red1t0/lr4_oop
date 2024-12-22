#include <iostream>
#include <fstream>
#include "fileprocessor.hpp"

FileProcessor::FileProcessor(std::ios::openmode mode, const std::string& filename)
    :file(filename, mode), filename(filename)
{
    if (!file.is_open()){throw std::runtime_error ("Failed to open file: " + filename);}
}

void FileProcessor::save_gamestate(GameState* gamestate)
{
    file << (*gamestate);
    file.flush();
}

void FileProcessor::load_gamestate(GameState* gamestate)
{
    try{
        file >> (*gamestate);
    }catch(FileWasChanged& e) {throw FileWasChanged(this->get_filename());}
}

FileProcessor::~FileProcessor()
{
    if (file.is_open()) file.close();
}