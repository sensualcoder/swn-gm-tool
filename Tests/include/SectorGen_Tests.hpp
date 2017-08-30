#ifndef SECTOR_GEN_TESTS_HPP
#define SECTOR_GEN_TESTS_HPP

#include <iostream>
#include <string>

#include "Hex.hpp"
#include "HexElement.hpp"
#include "Planet.hpp"
#include "SectorGen.hpp"

#include "TestHelpers.hpp"

using namespace SwnGmTool;

namespace Tests
{
    template <typename T, typename R>
    void test_map(std::string name)
    {
        printTestLine(name + " Tests");

        T testElement { "Test" };

        printTestLine("Create test map");
        std::unique_ptr<Map<R>> testMap(new Map<R>(10, 10));
        std::cout << "Map size: " << sizeof(*testMap) << "\n\n";

        printTestDivider('=', "\n\n");
    }

    template <typename T>
    void test_hex(std::string name)
    {
        printTestLine(name + " Tests");

        HexElement testElement { "Test" };

        printTestLine("Create test hex");
        std::unique_ptr<Hex<T>> testHex(new Hex<T>(0, 0, 0));
        std::cout << "Hex size: " << sizeof(*testHex) << "\n\n";

        printTestDivider('=', "\n\n");
    }

    template <typename T>
    void test_hexelement(std::string name)
    {
        T testElement { "Test" };

        printTestLine(name + " element tests");

        std::cout << name + " struct size: " << sizeof(testElement) << "\n\n";
    
        printTestDivider('=', "\n\n");
    }
}

#endif
