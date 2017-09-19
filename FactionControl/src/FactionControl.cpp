#include "FactionControl.hpp"

namespace SwnGmTool
{
    FactionControl::FactionControl(uint8_t mapSize)
    {
        this->Map.reserve(mapSize);
    }

    FactionControl::~FactionControl()
    {
        this->Map.clear();
    }

    int FactionControl::GetMapSize()
    {
        return this->Map.size();
    }

    void FactionControl::ClearMap()
    {
        this->Map.clear();
    }

    Faction_List FactionControl::GetFactionList()
    {
        Faction_List factionList;

        for(auto it : this->Map)
        {
            factionList.push_back(it.Faction);
        }

        return factionList;
    }

    FactionDTO& FactionControl::GetFaction(std::string name)
    {
        auto item = this->Map.find(name);

        return item->Faction;
    }

    void FactionControl::AddFaction(std::string name)
    {
        this->AddFaction(FactionDTO { name } );
    }

    void FactionControl::AddFaction(const FactionDTO& faction)
    {
        this->Map.push_back(FAC { faction, Asset_List() } );
    }

    void FactionControl::RemoveFaction(std::string name)
    {
        auto item = this->Map.find(name);        

        this->Map.erase(item);
    }

    Asset_List& FactionControl::GetAssetList(std::string name)
    {
        auto item = this->Map.find(name);

        return item->AssetList;
    }
}
