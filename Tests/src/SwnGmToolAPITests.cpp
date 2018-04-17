#include <catch/catch.hpp>

#include "ConfigModel.hpp"
#include "FactionModel.hpp"
#include "SwnGmToolAPI.hpp"

using namespace SwnGmTool;

namespace Tests
{
    TEST_CASE("SWN GM Tool API tests")
    {
        ConfigModel defaultConfig
        { 
            .DefaultFactionCount = 5 
        };

        FactionModel testFaction
        {
            .Name = "Test"
        };

        SECTION("API is created with default Faction Control size")
        {
            std::unique_ptr<SwnGmToolAPI> testAPI(new SwnGmToolAPI(defaultConfig) );

            REQUIRE(testAPI->GetConfig().DefaultFactionCount == 5);
            REQUIRE(testAPI->GetFactionList().empty() == true);
            REQUIRE(testAPI->GetFactionList().size() == 0);
        }

        SECTION("API can add Factions to the control")
        {
            std::unique_ptr<SwnGmToolAPI> testAPI(new SwnGmToolAPI(defaultConfig) );

            testAPI->AddFaction(testFaction);

            REQUIRE(testAPI->GetFactionList().size() == 1);
            REQUIRE(testAPI->GetFactionList().empty() == false);
            REQUIRE(testAPI->GetFactionList()[0] == testFaction);
        }

        SECTION("API can clear Faction list from the control")
        {
            std::unique_ptr<SwnGmToolAPI> testAPI(new SwnGmToolAPI(defaultConfig) );

            testAPI->AddFaction(testFaction);
            testAPI->ClearFactions();

            REQUIRE(testAPI->GetFactionList().size() == 0);
            REQUIRE(testAPI->GetFactionList().empty() == true);
        }
    }
}