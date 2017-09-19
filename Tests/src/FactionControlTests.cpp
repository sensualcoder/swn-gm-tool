#include <memory>
#include <string>
#include <vector>

#include "Tests.hpp"
#include "catch.hpp"

#include "FactionControl.hpp"

using namespace SwnGmTool;

namespace Tests
{
    TEST_CASE("Factions can be added and removed from a control")
    {
        std::unique_ptr<FactionControl> testControl(new FactionControl() );

        REQUIRE(testControl != nullptr);

        std::string testName = "Test";
        FactionDTO testFaction { testName };

        REQUIRE(testFaction.Name == testName);

        SECTION("Adding factions increases map size and list shows new faction")
        {
            testControl->AddFaction(testFaction);

            REQUIRE(testControl->GetMapSize() == 1);
            REQUIRE(testControl->GetFactionList().size() == 1);
            REQUIRE(testControl->GetFactionList() == std::vector<FactionDTO> { testFaction } );
        }

        SECTION("Removing factions decreases map size and list is empty")
        {
            testControl->AddFaction(testFaction);
            testControl->RemoveFaction(testName);

            REQUIRE(testControl->GetMapSize() == 0);
            REQUIRE(testControl->GetFactionList().size() == 0);
            REQUIRE(testControl->GetFactionList() == std::vector<FactionDTO>() );
        }

        SECTION("Adding a large amount of factions increases map size and list returns same amount")
        {
            int test_count = 1000;
            for(int i = 0; i < test_count; i++)
            {
                std::string name = "Test" + std::to_string(i);
                std::unique_ptr<FactionDTO> tmp = std::unique_ptr<FactionDTO>(new FactionDTO { name });
                testControl->AddFaction(*tmp);
            }

            REQUIRE(testControl->GetMapSize() == test_count);
            REQUIRE(testControl->GetFactionList().size() == test_count);
        }
    }

    TEST_CASE("Assets can be added and removed from a faction in the control")
    {
        std::unique_ptr<FactionControl> testControl(new FactionControl() );
        
        REQUIRE(testControl != nullptr);

        std::string testName = "Test";
        FactionDTO testFaction { testName };

        REQUIRE(testFaction.Name == testName);
        
        testControl->AddFaction(testFaction);
        
        REQUIRE(testControl->GetMapSize() == 1);
        REQUIRE(testControl->GetFactionList().size() == 1);
        REQUIRE(testControl->GetFactionList() == std::vector<FactionDTO> { testFaction } );

        SECTION("Adding a large amount of assets to the list increases the list size")
        {
            int test_count = 1000;
            for(int i = 0; i < test_count; i++)
            {
                std::string name = testName + std::to_string(i);
                std::unique_ptr<AssetDTO> tmp = std::unique_ptr<AssetDTO>(new AssetDTO { name });
                testControl->GetAssetList(testName).push_back(*tmp);
            }

            REQUIRE(testControl->GetAssetList(testName).size() == test_count);
        }
    }
}
