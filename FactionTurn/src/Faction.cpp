#include "Faction.hpp"

#include <cmath>

namespace FT
{
    // Forward declarations
    class Faction;

    // Class public methods
    Faction::Faction(std::string name, uint8_t force, uint8_t cunning, uint8_t wealth) :
        Name(name), Force(force), Cunning(cunning), Wealth(wealth)
    {
        this->CurrentHp = this->MaxHp = CalcHp(force, cunning, wealth);
        this->Income = CalcIncome(force, cunning, wealth);
        this->Treasury = this->Experience = 0;
    }

    Faction::Faction(std::string name, uint8_t force, uint8_t cunning, uint8_t wealth, uint8_t income, uint8_t treasury, uint8_t currentHp, uint8_t maxHp, uint8_t experience) :
        Name(name), Force(force), Cunning(cunning), Wealth(wealth), Income(income), Treasury(treasury), CurrentHp(currentHp), MaxHp(maxHp), Experience(experience)
    {
    }

    Faction::Faction(const FactionCreateModel& faction)
    {
        this->Force = faction.Force;
        this->Cunning = faction.Cunning;
        this->Wealth = faction.Wealth;

        this->CurrentHp = this->MaxHp = CalcHp(faction.Force, faction.Cunning, faction.Wealth);
        this->Income = CalcIncome(faction.Force, faction.Cunning, faction.Wealth);
        this->Treasury = this->Experience = 0;
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