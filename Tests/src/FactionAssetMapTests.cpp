#include <catch/catch.hpp>

#include "FactionAssetMap.hpp"

using namespace SwnGmTool;

namespace Tests
{
    TEST_CASE("FactionAssetMapTests")
    {
        std::unique_ptr<FactionAssetMap> testMap(new FactionAssetMap(0) );

        REQUIRE(testMap != nullptr);

        std::string testName = "Test";
        FactionModel testFaction { testName };

        REQUIRE(testFaction.Name == testName);

        SECTION("Add faction")
        {
            testMap->emplace(testFaction, FAC::Asset_List() );

            REQUIRE(testMap->size() == 1);
            
            auto item = testMap->begin();
            REQUIRE(*item->first == testFaction);
        }

        SECTION("Remove faction")
        {
            testMap->emplace(testFaction, FAC::Asset_List() );
            auto item = testMap->begin();
            testMap->erase(item);

            REQUIRE(testMap->size() == 0);
        }

        SECTION("Add large amount of factions")
        {
            int test_count = 1000;
            for(int i = 0; i < test_count; i++)
            {
                std::string name = "Test" + std::to_string(i);
                FactionModel tmp = FactionModel { name };
                testMap->emplace(tmp, FAC::Asset_List() );
            }

            REQUIRE(testMap->size() == test_count);
        }
    }
}