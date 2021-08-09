#include "IO.hpp"

#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

std::string asm4::io::ReadTextFromFile(std::string filepath) {
    std::ifstream file;
    std::stringstream sstr;

    file.open(filepath, std::ios::in);
    if (!file.is_open()){
        std::cerr << "error: Unable to open file '" << filepath << "'" << std::endl;
        exit(EXIT_FAILURE);
    }

    sstr << file.rdbuf();
    file.close();

    return sstr.str();
}