#include "FactionControl.hpp"

#include <cmath>

namespace SwnGmTool
{
    // Public methods

    FactionControl::FactionControl(int size) : Map(size)
    {
    }

    FactionControl::~FactionControl()
    {
        this->Map.clear();
    }

    int FactionControl::GetFactionCount() const
    {
        return this->Map.size();
    }

    const FAC::Faction_List FactionControl::GetFactionList()
    {
        FAC::Faction_List factionList;

        if(this->Map.size() > 0)
        {
            factionList.reserve(this->Map.size() );

            for(auto& it : this->Map)
            {
                factionList.push_back(*it.first);
            }
        }

        return factionList;
    }

    const FactionModel FactionControl::GetFactionDetails(int index)
    {
        auto item = this->Map.begin();
        std::advance(item, index);

        return *item->first;
    }

    void FactionControl::AddFaction(const FactionModel& faction)
    {
        this->Map.emplace(faction, FAC::Asset_List() );
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
        auto item = this->Map.begin();
        std::advance(item, index);

        this->Map.erase(item);
    }

    void FactionControl::ClearMap()
    {
        this->Map.clear();
    }

    const FAC::Asset_List FactionControl::GetAssetList(int index)
    {
        auto item = this->Map.begin();
        std::advance(item, index);

        return *item->second;
    }

    void FactionControl::AddAsset(int index, const AssetModel& asset)
    {
        auto item = this->Map.begin();
        std::advance(item, index);

        item->second->push_back(asset);
    }

    void FactionControl::RemoveAsset(int index, int assetIndex)
    {
        auto item = this->Map.begin();
        std::advance(item, index);

        auto asset = item->second->begin();
        std::advance(asset, assetIndex);

        item->second->erase(asset);
    }

    void FactionControl::RemoveAllAssetsOfType(int index, const AssetModel& asset)
    {
        auto item = this->Map.begin();
        std::advance(item, index);

        item->second->remove(asset);
    }

    void FactionControl::ClearAssets(int index)
    {
        auto item = this->Map.begin();
        std::advance(item, index);

        item->second->clear();
    }
}
