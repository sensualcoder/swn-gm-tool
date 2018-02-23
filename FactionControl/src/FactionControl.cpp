#include "FactionControl.hpp"

namespace SwnGmTool
{
    // Public methods

    FactionControl::FactionControl(ConfigModel config)
    {
        if(config.DefaultFactionCount >= 0)
            this->Map.reserve(config.DefaultFactionCount);
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

    const Faction_List FactionControl::GetFactionList()
    {
        Faction_List factionList;

        for(auto it : this->Map)
        {
            factionList.push_back(it.Faction);
        }

        return factionList;
    }

    void FactionControl::AddFaction(const FactionModel& faction)
    {
        this->Map.push_back(FAC { faction, Asset_List() } );
    }

    void FactionControl::RemoveFaction(int index)
    {
        auto item = this->Map.begin() + index;

        this->Map.erase(item);    
    }

    const Asset_List FactionControl::GetAssetList(int index)
    {
        return this->Map[index].AssetList;
    }

    void FactionControl::AddAsset(int index, const AssetModel& asset)
    {
        this->Map[index].AssetList.push_back(asset);
    }

    void FactionControl::RemoveAsset(int index, int assetIndex)
    {
        auto asset = this->Map[index].AssetList.begin();
        std::advance(asset, assetIndex);

        this->Map[index].AssetList.erase(asset);
    }

    void FactionControl::RemoveAllAssetsOfType(int index, const AssetModel& asset)
    {
        this->Map[index].AssetList.remove(asset);
    }

    void FactionControl::ClearAssets(int index)
    {
        this->Map[index].AssetList.clear();
    }
}
