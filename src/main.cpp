#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>

#include <unistd.h>
#include <iomanip>
#include <getopt.h>

#include "OpCode.hpp"
#include "CPU4.hpp"



//-----------------------------------------------
// Global Variables
//-----------------------------------------------
unsigned char *memory;



//-----------------------------------------------
// Load memory
//-----------------------------------------------
void NibblesToMem(unsigned char *nibbles) {
    memory = new unsigned char [MEMORY_SIZE];
    for (int i = 0; i < MEMORY_SIZE; i++)
    {
        memory[i] = (nibbles[2*i] << 4) | nibbles[2*i+1];
    }
}

unsigned char HexToNibble(char c){
    if ( c >= '0' && c <= '9'){
        return c - '0';
    }
    if (c >= 'A' && c <= 'F') {
        return c - '7'; // === c - 'A' + 10
    }
    if (c >= 'a' && c <= 'f') {
        return c - 'W'; // === c - 'a' + 10
    }
    std::cerr << "error: Invalid input character '" << c << "'. Expecting hexadecimal digits only.";
    exit(EXIT_FAILURE);
}

void LoadFromString(char * str) {
    unsigned char *nibbles = new unsigned char[MEMORY_SIZE*2];
    int index=0;

    while (*str && index < MEMORY_SIZE*2) {
        char c = *str++; // dereference & increment pointer
        if (c==' ' || c=='\t' || c=='\r' || c=='\n'){
            continue;
        }
        nibbles[index++] = HexToNibble(c); // dereference & increment pointer
    }

    if (index == MEMORY_SIZE*2 && *str != '\0') {
        std::cout << "warning: input longer than " << std::to_string(MEMORY_SIZE*2);
        std::cout << " hexacimal digits (" << std::to_string(MEMORY_SIZE) + " bytes). Memory will be truncated.";
    }

    while (index < MEMORY_SIZE*2) {
        nibbles[index++] = 0; // pad with zeroes
    }

    NibblesToMem(nibbles);
    delete nibbles;
}

void LoadFromFile(char * filepath) {
    std::ifstream file;
    std::stringstream sstr;

    file.open(filepath, std::ios::in);
    if (!file.is_open()){
        std::cerr << "error: Unable to open file '" << filepath << "'" << std::endl;
        exit(EXIT_FAILURE);
    }

    sstr << file.rdbuf();
    file.close();

    std::string str = sstr.str();

    char *chars = new char[str.size()+1];
    strcpy(chars, str.c_str());
    LoadFromString(chars);
    delete chars;
}

//-----------------------------------------------
// Parse command line parameters
//-----------------------------------------------

void PrintUsage(char *filename){
    std::cout << "Usage:" << std::endl;
    std::cout << "\t" << filename << " [OPTIONS] input" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "\t-h, --help:\n\t\tPrints usage information (this)" << std::endl;
    std::cout << "\t-f, --file [file]:\n\t\tFile containing hexadecimal values to load into memory" << std::endl;
    std::cout << "\t-s, --string [hex string]:\n\t\tString of hexadecimal values to be loaded into memory" << std::endl;
}

void LoadMemoryFromArgs(int argc, char* argv[]){
    if (argc == 1) {
        PrintUsage(argv[0]);
        exit(EXIT_SUCCESS);
    }

    int optionsIndex = 0;
    int c;

    // get option arguments
    static option longOptions[] = {
        {"file", required_argument, 0, 'f'},
        {"help", no_argument, 0, 'h'},
        {"string", required_argument, 0, 's'},
        {0, 0, 0, 0}
    };

    while (true){
        c = getopt_long (argc, argv, "f:hs:", longOptions, &optionsIndex);

        // found end of the options
        if (c == -1) {
            break;
        }

        switch (c) {
            case 'f':
                LoadFromFile(optarg);
                break;

            case 's':
                LoadFromString(optarg);
                break;

            case 'h':
                PrintUsage(argv[0]);
                exit(EXIT_SUCCESS);
                break;

            case '?':
                PrintUsage(argv[0]);
                exit(EXIT_SUCCESS);
                break;

            default:
                abort();
                break;
        }
    }
}



//-----------------------------------------------
// Main
//-----------------------------------------------

int main(int argc, char *argv[]){
    LoadMemoryFromArgs(argc, argv);
    emulator::CPU4 cpu(memory);
    cpu.Run(5);
    std::cout << cpu << std::endl;
    
    return EXIT_SUCCESS;
}
