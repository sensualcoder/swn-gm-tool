#include "FactionControl.hpp"

namespace SwnGmTool
{
    const Faction& FactionControl::GetFaction(std::string fName)
    {
        auto item = this->FindFaction(fName);
        return item->first;
    }

    const std::vector<Faction> FactionControl::GetFactionList()
    {
        std::vector<Faction> factionList;

        for(auto i : this->FactionAssetMap)
        {
            factionList.push_back(i.first);
        }

        return factionList;
    }

    void FactionControl::AddFaction(Faction faction)
    {
        this->FactionAssetMap[faction];
    }

    void FactionControl::RemoveFaction(std::string fName)
    {
        this->FactionAssetMap.erase(this->FindFaction(fName) );
    }

    const std::vector<Asset> FactionControl::GetAssetList(std::string fName)
    {
        auto item = this->FindFaction(fName);

        return item->second;
    }

    void FactionControl::AddAsset(std::string fName, Asset asset)
    {
        auto item = this->FindFaction(fName);
        item->second.push_back(asset);
    }

    void FactionControl::RemoveAsset(std::string fName, std::string aName)
    {
        auto faction = this->FindFaction(fName);
        faction->second.erase(this->FindAsset(fName, aName) );
    }

    void FactionControl::ClearAssetList(std::string fName)
    {
        auto item = this->FindFaction(fName);
        item->second.clear();
    }

    int FactionControl::GetMapSize()
    {
        return this->FactionAssetMap.size();
    }

    void FactionControl::ClearMap()
    {
        this->FactionAssetMap.clear();
    }

    std::unordered_map<Faction, std::vector<Asset> >::iterator FactionControl::FindFaction(std::string fName)
    {
        return this->FactionAssetMap.find(Faction { fName } );
    }

    std::vector<Asset>::iterator FactionControl::FindAsset(std::string fName, std::string aName)
    {
        std::vector<Asset> list = this->FindFaction(fName)->second;

        for(auto iter = list.begin(); iter < list.end(); iter++)
        {
            if(iter->Name == aName)
                return iter;
        }
    }
}