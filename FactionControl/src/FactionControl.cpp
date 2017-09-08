#include "FactionControl.hpp"

namespace SwnGmTool
{
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

    MapNode* FactionControl::GetFactionNode(std::string name)
    {
        auto item = this->Map.find(name);

        return *item;
    }

    FactionList& FactionControl::GetFactionList()
    {
        std::vector<FactionDTO>* factionList = new std::vector<FactionDTO>();

        for(auto it = this->Map.begin(); it != this->Map.end(); it++)
        {
            factionList->push_back(it->Faction.GetFaction() );
        }

        return *factionList;
    }

    FactionManager& FactionControl::GetFaction(std::string name)
    {
        auto item = this->Map.find(name);

        return item->Faction;
    }

    void FactionControl::AddFaction(std::string name)
    {
        this->AddFaction(FactionManager(name) );
    }

    void FactionControl::AddFaction(const FactionManager& manager)
    {
        this->Map.push_back(manager);
    }

    void FactionControl::RemoveFaction(std::string name)
    {
        auto item = this->Map.find(name);        

        this->Map.erase(item);
    }

    AssetList& FactionControl::GetAssetList(std::string name)
    {
        auto item = this->Map.find(name);

        return item->AssetList;
    }
}
