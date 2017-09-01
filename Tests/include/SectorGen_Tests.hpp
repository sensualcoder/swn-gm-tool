#ifndef SECTOR_GEN_TESTS_HPP
#define SECTOR_GEN_TESTS_HPP

#include <iostream>
#include <string>

#include "Hex.hpp"
#include "HexElement.hpp"
#include "HexMap.hpp"
#include "Planet.hpp"
#include "SectorGen.hpp"

#include "TestHelpers.hpp"

using namespace SwnGmTool;

namespace Tests
{
    template<typename T>
    void test_mapgen(std::string name)
    {
        printTestLine(name + " Tests");

        printTestLine("Create test map generator");
        std::unique_ptr<T> testGenerator(new T() );
        std::cout << "Generator size: " << sizeof(*testGenerator) << "\n\n";

        printTestDivider('=', "\n\n");
    }

    template <typename T>
    void test_map(std::string name)
    {
        printTestLine(name + " Tests");

        T testElement { "Test" };

        printTestLine("Create test map");
        std::unique_ptr<HexGrid::HexMap> testMap(new HexGrid::HexMap() );
        std::cout << "Map size: " << sizeof(*testMap) << "\n\n";

        printTestLine("Check map set size");
        std::cout << "Map set size: " << sizeof(testMap->GetMap() ) << "\n\n";

        printTestDivider('=', "\n\n");
    }

    template <typename T, typename R>
    void test_hex(std::string name)
    {
        printTestLine(name + " Tests");

        T testElement { "Test" };

        printTestLine("Create test hex");
        std::unique_ptr<R> testHex(new R(0, 0, 0));
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
