#include <catch2/catch.hpp>

#include <cereal/archives/json.hpp>

#include "ConfigModel.hpp"
#include "FactionModel.hpp"
#include "SwnGmToolAPI.hpp"

using namespace SwnGmTool;

namespace Tests
{
    TEST_CASE("SwnGmToolAPITests")
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

            std::stringstream stream;
            testAPI->GetFactionList(stream);
            cereal::JSONInputArchive archive(stream);
            
            FAC::Faction_List list;
            archive(list);

            REQUIRE(list.empty() == true);
            REQUIRE(list.size() == 0);
        }

        SECTION("API can add Factions to the control")
        {
            std::unique_ptr<SwnGmToolAPI> testAPI(new SwnGmToolAPI(defaultConfig) );

            testAPI->AddFaction(testFaction);

            std::stringstream stream;
            testAPI->GetFactionList(stream);
            cereal::JSONInputArchive archive(stream);
            
            FAC::Faction_List list;
            archive(list);

            REQUIRE(list.size() == 1);
            REQUIRE(list.empty() == false);
            REQUIRE(list[0] == testFaction);
        }

        SECTION("API can clear Faction list from the control")
        {
            std::unique_ptr<SwnGmToolAPI> testAPI(new SwnGmToolAPI(defaultConfig) );

            testAPI->AddFaction(testFaction);
            testAPI->ClearFactions();

            std::stringstream stream;
            testAPI->GetFactionList(stream);
            cereal::JSONInputArchive archive(stream);
            
            FAC::Faction_List list;
            archive(list);

            REQUIRE(list.size() == 0);
            REQUIRE(list.empty() == true);
        }
    }
}