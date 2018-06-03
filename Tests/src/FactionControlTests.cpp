#include <fstream>
#include <memory>
#include <string>
#include <vector>

#include <catch/catch.hpp>

#include "AssetModel.hpp"
#include "FactionControl.hpp"
#include "FactionModel.hpp"
#include "FileAccess.hpp"

using namespace SwnGmTool;

namespace Tests
{
    TEST_CASE("FactionControlTests")
    {
        std::unique_ptr<FactionControl> testControl(new FactionControl() );

        REQUIRE(testControl != nullptr);

        std::string testName = "Test";
        FactionModel testFaction { testName };

        REQUIRE(testFaction.Name == testName);

        SECTION("Add faction")
        {
            testControl->AddFaction(testFaction);

            REQUIRE(testControl->GetFactionCount() == 1);
            REQUIRE(testControl->GetFactionList().size() == 1);
            REQUIRE(testControl->GetFactionList()[0] == testFaction);
        }

        SECTION("Remove faction")
        {
            testControl->AddFaction(testFaction);
            testControl->RemoveFaction(0);

            REQUIRE(testControl->GetFactionCount() == 0);
            REQUIRE(testControl->GetFactionList().size() == 0);
        }

        SECTION("Add large amount of factions")
        {
            int test_count = 1000;
            for(int i = 0; i < test_count; i++)
            {
                std::string name = "Test" + std::to_string(i);
                FactionModel tmp = FactionModel { name };
                testControl->AddFaction(tmp);
            }

            REQUIRE(testControl->GetFactionCount() == test_count);
            REQUIRE(testControl->GetFactionList().size() == test_count);
        }

        SECTION("Add large amount of assets to a faction")
        {
            testControl->AddFaction(testFaction);

            int test_count = 10000;
            for(int i = 0; i < test_count; i++)
            {
                std::string name = testName + std::to_string(i);
                AssetModel tmp = AssetModel { name };
                testControl->AddAsset(0, tmp);
            }

            REQUIRE(testControl->GetAssetList(0).size() == test_count);
        }

        SECTION("Save and load")
        {
            testControl->AddFaction(testFaction);

            FileAccess<FactionControl> oaccess;
            std::ofstream out("test.sgt");
            oaccess.Save(out, *testControl, "Test");

            testControl->ClearMap();

            REQUIRE(testControl->GetFactionCount() == 0);
            REQUIRE(testControl->GetFactionList().size() == 0);

            FileAccess<FactionControl> iaccess;
            std::ifstream in("test.sgt");
            iaccess.Load(in, *testControl);

            REQUIRE(testControl->GetFactionCount() == 1);
            REQUIRE(testControl->GetFactionList().size() == 1);
            REQUIRE(testControl->GetFactionList()[0] == testFaction);
        }
    }
}
