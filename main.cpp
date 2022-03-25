#include <iostream>
#include "parser.h"

int main() {

    Parser par;

    bool open = false;
    int attempts = 0;

    while( !open ){

        try{

            std::cout << "Enter file path for city dict\n";

            attempts++;

            std::string file;

            std::getline( std::cin, file );

            par.loadCityDict( file );

            open = true;

        }

        catch(...){

            std::cout << "Try different file path\n";

            if( attempts == 9 ){

                std::cout << "Something is going wrong, take a rest :-)\n";

                return 0;

            }

        }

    }

    while( true ){

        std::string inquiry;

        std::cout << "Enter phrase to parse\n";

        std::getline( std::cin, inquiry );

        if( inquiry == "c" ) break;

        try {

            auto response = par.parseInquiry(inquiry);

            std::cout << "(Intent: " + response + ")" << std::endl;

        }

        catch(...){

            std::cout << "Oops, something went wrong, don't panic! Try one more time :)\n";

        }

    }

    return 0;
}
