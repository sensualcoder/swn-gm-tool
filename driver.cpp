#include <iostream>
#include <string>

#include "Tests.hpp"

void printTestsMenu()
{
    std::cout << "Select a test to run" << std::endl;
    std::cout << "0) All tests" << std::endl;
    std::cout << "Q) Back" << "\n\n";
}

void selectTest(int option)
{
    switch(option)
    {
        case 'Q':
        case 'q':
            return;
        case 0:
        default:
            Tests::runAllTests();
            break;
    }
}

void tests()
{
    printTestsMenu();

    std::string line; 
    std::getline(std::cin, line);
    selectTest(line[0]);
}

void printMenu()
{
    std::cout << "Select option from list" <<std::endl;
    std::cout << "1) Run tests" << std::endl;
    std::cout << "Q) Quit" << "\n\n";
}

void parseLine(int option)
{
    switch(option)
    {
        case 1:
        default:
            tests();
            break;
    }
}

int main(int argc, char* argv[])
{
    printMenu();

    for (std::string line; std::getline(std::cin, line);)
    {
        if(line != "")
        {
            if(line[0] == 'Q' || line[0] == 'q')
                break;

            parseLine((int)line[0]);
        }

        printMenu();
    }

    return 0;
}
