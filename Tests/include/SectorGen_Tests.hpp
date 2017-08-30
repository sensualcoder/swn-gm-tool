#ifndef SECTOR_GEN_TESTS_HPP
#define SECTOR_GEN_TESTS_HPP

#include <iostream>
#include <string>

#include "SectorGen.hpp"

#include "Tests.hpp"

using namespace SwnGmTool;

namespace Tests
{
    template <typename T>
    void test_map(Map<T>* map, std::string name)
    {
        printTestLine(name + " Tests");

        HexElement testElement = {"Test"};

        printTestLine("Create test map");
        std::unique_ptr<Map<T>> testMap(map);
        std::cout << "Map size: " << sizeof(*testMap) << "\n\n";
    }

    template <typename T>
    void test_hexelement(std::string name)
    {
        printTestLine(name + " struct tests");
        
        printTestLine("Create test struct");
        HexElement testStruct = { "Test" };
        std::cout << name + " struct size: " << sizeof(testStruct) << "\n\n";
    
        printTestDivider('=', "\n\n");
    }
}

#endif
