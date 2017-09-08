#include "FactionManager.hpp"

namespace SwnGmTool
{
    FactionManager::FactionManager(const FactionManager& fm)
    {
        this->Faction = fm.GetFaction();
    }

    FactionManager::FactionManager(FactionDTO faction)
    {
        this->Faction = faction;
    }

    FactionDTO FactionManager::GetFaction() const
    {
        return this->Faction;
    }
}