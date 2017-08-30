#include <iostream>

#include "TestHelpers.hpp"

namespace Tests
{
    void printTestDivider(char div, std::string lineEnd)
    {
        std::cout << std::string(50, div) << lineEnd;
    }
    
    void printTestHeader(std::string str)
    {
        printTestDivider('=', "\n");
        std::cout << "=====" << str << "=====" << std::endl;
        printTestDivider('=', "\n");
    }
    
    void printTestLine(std::string str)
    {
        std::cout << "***" << str << "***" << std::endl;
    }
}
