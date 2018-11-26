#include "Faction.hpp"

#include <cmath>

namespace FT
{
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

    // Class public methods
    Faction::Faction(const FactionCreateModel& faction) : Model()
    {
        this->Model.Name = faction.Name;
        this->Model.Force = faction.Force;
        this->Model.Cunning = faction.Cunning;
        this->Model.Wealth = faction.Wealth;

        this->Model.CurrentHp = this->Model.MaxHp = CalcHp(faction.Force, faction.Cunning, faction.Wealth);
        this->Model.Income = CalcIncome(faction.Force, faction.Cunning, faction.Wealth);
        this->Model.Treasury = this->Model.Experience = 0;
    }

    Faction::Faction(const FactionModel& faction) : Model(faction)
    {
    }

    void Faction::TakeDamage(unsigned int damage)
    {
        if(damage >= this->Model.CurrentHp)
        {
            this->Model.CurrentHp = 0;
        }
        else
        {
            this->Model.CurrentHp -= damage;
        }

        this->Notify(Event { EventType::FACTION_DAMAGED } );

        if(this->Model.CurrentHp == 0)
        {
            this->Notify(Event { EventType::FACTION_DESTROYED } );
        }
    }

    const FactionModel& Faction::GetModel() const 
    { 
        return this->Model; 
    }
}
