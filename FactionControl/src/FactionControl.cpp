#include "FactionControl.hpp"

#include <cmath>

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

    const int FactionControl::GetFactionCount()
    {
        return this->Map.size();
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

    const FactionModel FactionControl::GetFactionDetails(int index)
    {
        auto item = this->Map.begin() + index;

        return item->Faction;
    }

    void FactionControl::AddFaction(const FactionModel& faction)
    {
        this->Map.push_back(FAC { faction, Asset_List() } );
    }

    void FactionControl::AddFaction(const FactionCreateModel& faction)
    {
        FactionModel model
        {
            .Name = faction.Name,
            .Description = faction.Description,
            .Force = faction.Force,
            .Cunning = faction.Cunning,
            .Wealth = faction.Wealth
        };

        model.MaxHP = model.CurrentHP = CalcHpFromAttributes(faction);

        model.Income = CalcIncomeFromAttributes(faction);

        model.FacCreds = model.Exp = 0;

        model.Tags = faction.Tags;

        this->AddFaction(model);
    }

    int FactionControl::CalcHpFromAttributes(const FactionCreateModel& faction)
    {
        int hp = RatingXpHpTable.find(faction.Force)->second.HP
                + RatingXpHpTable.find(faction.Cunning)->second.HP
                + RatingXpHpTable.find(faction.Wealth)->second.HP
                + 4;

        return hp;
    }

    int FactionControl::CalcIncomeFromAttributes(const FactionCreateModel& faction)
    {
        int income = std::ceil(faction.Wealth / 2.0)
                    + std::floor( (faction.Force + faction.Cunning) / 4.0);

        return income;
    }

    void FactionControl::RemoveFaction(int index)
    {
        auto item = this->Map.begin() + index;

        this->Map.erase(item);    
    }

    void FactionControl::ClearMap()
    {
        this->Map.clear();
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
