#include <iostream>
#include <cstdlib>
#include "include/Encrypt.h"
#include <fstream>

int main()
{
    char c = 'c';
    Encrypt obj;

    std::string inp;

    while (inp != "x"){
        system("clear");
        std::cout << "To see Cipher Table, press 's'\nTo see more options, press 'm'\nTo exit, press 'x': ";
        std::cin >> inp;
        std::cout << std::endl;

        if (inp == "s"){
            obj.printCipher();
        }
        else if (inp == "m"){
            obj.start();
        }
    }

    return 0;
}
