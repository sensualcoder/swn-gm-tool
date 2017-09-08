#include "FactionManager.hpp"

namespace SwnGmTool
{
    FactionManager::FactionManager() 
    {
        this->Faction = FactionDTO();
    }

    FactionManager::FactionManager(std::string name)
    {
        this->Faction = FactionDTO { name };
    }

    FactionManager::FactionManager(const FactionManager& fm)
    {
        this->Faction = fm.GetFaction();
    }

    FactionManager::FactionManager(const FactionDTO& faction)
    {
        this->Faction = faction;
    }

    FactionDTO FactionManager::GetFaction() const
    {
        return this->Faction;
    }

    void FactionManager::SetFaction(const FactionDTO& faction)
    {
        this->Faction = faction;
    }
}