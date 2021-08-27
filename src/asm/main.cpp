#include <iostream>
#include <fstream>
#include <sstream>
#include <cstring>
#include <string>
#include <vector>

#include <unistd.h>
#include <iomanip>
#include <getopt.h>

#include "IO.hpp"
#include "Lexer.hpp"

#define DEFAULT_OUTPUT_FILE "a.mem"



std::string inputFile;
std::string outputFile;



//-----------------------------------------------
// Parse command line parameters
//-----------------------------------------------

void PrintUsageAndExit(char *filename){
    std::cout << "Usage:" << std::endl;
    std::cout << "\t" << filename << " [OPTIONS] input" << std::endl;
    std::cout << "Options:" << std::endl;
    std::cout << "\t-h, --help:\n\t\tPrints usage information (this)" << std::endl;
    std::cout << "\t-o, --output [file]:\n\t\tOuput file" << std::endl;
    exit(EXIT_SUCCESS);
}

void ParseArguments(int argc, char* argv[]){
    if (argc == 1) {
        PrintUsageAndExit(argv[0]);
    }

    int optionsIndex = 0;
    int c;

    // get option arguments
    static option longOptions[] = {
        {"help", no_argument, 0, 'h'},
        {"output", required_argument, 0, 'o'},
        {0, 0, 0, 0}
    };

    while (true){
        c = getopt_long (argc, argv, "ho:", longOptions, &optionsIndex);

        // found end of the options
        if (c == -1) {
            break;
        }

        switch (c) {
            case 'o':
                outputFile = optarg;
                break;

            case 'h':
                PrintUsageAndExit(argv[0]);
                break;

            case '?':
                PrintUsageAndExit(argv[0]);
                break;

            default:
                abort();
                break;
        }
    }

    // get non-option arguments
    std::vector<std::string> args;
    for (int pos=optind; pos < argc; pos++) {
        args.push_back(argv[pos]);
    }

    if (args.size() == 0) {
        std::cerr << "error: no input files" << std::endl;
        PrintUsageAndExit(argv[0]);
    }

    inputFile = args[0];

    // set default output name
    if (outputFile == "") {
        outputFile = DEFAULT_OUTPUT_FILE;
    }
}



//-----------------------------------------------
// Main
//-----------------------------------------------

int main(int argc, char *argv[]){
    ParseArguments(argc, argv);
    
    std::cout << "Reading from '" << inputFile << "'" << std::endl;
    std::cout << "Writing to '" << outputFile << "'" << std::endl;

    std::string contents = asm4::io::ReadTextFromFile(inputFile);
    std::vector<asm4::Token> tokens = asm4::lex::GetTokens(contents);
    
    return EXIT_SUCCESS;
}
