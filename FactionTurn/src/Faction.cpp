#include "Faction.hpp"

#include <cmath>

namespace FT
{
    // Class public methods
    Faction::Faction(const FactionCreateModel& faction) :
        Name(faction.Name), Force(faction.Force), Cunning(faction.Cunning), Wealth(faction.Wealth)
    {
        this->CurrentHp = this->MaxHp = CalcHp(faction.Force, faction.Cunning, faction.Wealth);
        this->Income = CalcIncome(faction.Force, faction.Cunning, faction.Wealth);
        this->Treasury = this->Experience = 0;
    }

    Faction::Faction(const FactionModel& faction) :
         Name(faction.Name), Force(faction.Force), Cunning(faction.Cunning), 
         Wealth(faction.Wealth), Income(faction.Income), Treasury(faction.Treasury), 
         CurrentHp(faction.CurrentHp), MaxHp(faction.MaxHp), Experience(faction.Experience)
    {
    }

    void Faction::TakeDamage(uint8_t damage)
    {
        this->Notify(Event { EventType::FACTION_DAMAGED } );

        if(damage >= this->CurrentHp)
        {
            this->Notify(Event { EventType::FACTION_DESTROYED } );
        }

        this->CurrentHp -= damage;
    }

    // Helper methods
    uint8_t CalcHp(uint8_t force, uint8_t cunning, uint8_t wealth)
    {
        return(RatingHpMap.find(force)->second
                + RatingHpMap.find(cunning)->second
                + RatingHpMap.find(wealth)->second
                + 4);
    }

    uint8_t CalcIncome(uint8_t force, uint8_t cunning, uint8_t wealth)
    {
        return(std::ceil(wealth / 2.0)
                + std::floor( (force + cunning) / 4.0) );
    }
}