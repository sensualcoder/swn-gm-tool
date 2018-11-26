#include <catch/catch.hpp>

#include "Faction.hpp"
#include "Observer.hpp"

using namespace SwnGmTool;

namespace Tests
{
    class TestObeserver : public FT::Observer
    {
        public:
            TestObeserver() : DamageTaken(false), FactionDestroyed(false) {}
        
            void OnNotify(const FT::Event& event)
            {
                if(event.Type == FT::EventType::FACTION_DAMAGED)
                {
                    this->DamageTaken = true;
                }
                
                if(event.Type == FT::EventType::FACTION_DESTROYED)
                {
                    this->FactionDestroyed = true;
                }
            }

            bool DamageTaken;
            bool FactionDestroyed;
    };

    TEST_CASE("Faction Tests")
    {
        FactionCreateModel createModel = { "Test", "", 1, 1, 1 };
        FactionModel model = { "Test", "", 1, 1, 1 };

        SECTION("Create Faction from FactionCreateModel")
        {
            FT::Faction faction = FT::Faction(createModel);

            REQUIRE(faction == createModel);
        }

        SECTION("Create Faction from FactionModel")
        {
            FT::Faction faction = FT::Faction(model);

            REQUIRE(faction == model);
        }

        SECTION("TakeDamage notifies observers")
        {
            TestObeserver obs;

            FT::Faction faction = FT::Faction(createModel);
            int expectedHp = faction.GetModel().MaxHp - 1;
            faction.AddObserver(&obs);

            faction.TakeDamage(1);

            REQUIRE(obs.DamageTaken == true);
            REQUIRE(faction.GetModel().CurrentHp == expectedHp);
        }

        SECTION("Faction destroyed by damage notifies observers")
        {
            TestObeserver obs;

            FT::Faction faction = FT::Faction(createModel);
            faction.AddObserver(&obs);

            faction.TakeDamage(9001);

            REQUIRE(obs.DamageTaken == true);
            REQUIRE(faction.GetModel().CurrentHp == 0);
            REQUIRE(obs.FactionDestroyed == true);
        }
    }
}
