#include <memory>

#include <catch2/catch.hpp>

#include "SectorGen.hpp"

using namespace SwnGmTool;

namespace Tests
{
    TEST_CASE("SectorGenTests")
    {
        std::unique_ptr<SectorGen> testGen(new SectorGen() );

        REQUIRE(testGen != nullptr);
        REQUIRE(testGen->GetMapSize() == STD_MAP_WIDTH * STD_MAP_HEIGHT);

        SECTION("Generate a sector")
        {
            testGen->GenerateSector();

            REQUIRE(testGen->GetSystemListSize() > MIN_STAR_MOD);
            REQUIRE(testGen->GetSystemListSize() <= STD_MAP_WIDTH * STD_MAP_HEIGHT);
        }
    }
}