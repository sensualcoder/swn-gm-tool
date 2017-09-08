#include "TestHelpers.hpp"

#include <iostream>

namespace Tests
{
    void printTestDivider(char div, const std::string& lineEnd)
    {
        std::cout << std::string(50, div) << lineEnd;
    }
    
    void printTestHeader(const std::string& str)
    {
        printTestDivider('=', "\n");
        std::cout << "=====" << str << "=====" << std::endl;
        printTestDivider('=', "\n");
    }
    
    void printTestLine(const std::string& str)
    {
        std::cout << "***" << str << "***" << std::endl;
    }
}
