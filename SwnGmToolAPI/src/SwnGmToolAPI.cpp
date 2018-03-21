#include "SwnGmToolAPI.hpp"

namespace SwnGmTool
{
    SwnGmToolAPI::SwnGmToolAPI(ConfigModel config) 
        : SGTConfig(config), 
            SGTFactionControl(new FactionControl(config) ), 
            SGTSectorGen(new SectorGen() )
    {
    }

    SwnGmToolAPI::~SwnGmToolAPI() = default;
    SwnGmToolAPI::SwnGmToolAPI(SwnGmToolAPI && op) noexcept = default;
    SwnGmToolAPI& SwnGmToolAPI::operator=(SwnGmToolAPI && op) noexcept = default;

    ConfigModel SwnGmToolAPI::GetConfig()
    { 
        return this->SGTConfig; 
    }

    int SwnGmToolAPI::GetFactionCount()
    {
        return this->SGTFactionControl->GetFactionCount();
    }

    FactionModel SwnGmToolAPI::GetFactionDetails(int index)
    {
        return this->SGTFactionControl->GetFactionDetails(index);
    }

    Faction_List SwnGmToolAPI::GetFactionList()
    { 
        return this->SGTFactionControl->GetFactionList();
    }

    void SwnGmToolAPI::AddFaction(FactionModel model) 
    { 
        this->SGTFactionControl->AddFaction(model); 
    }

    void SwnGmToolAPI::AddFaction(FactionCreateModel model) 
    { 
        this->SGTFactionControl->AddFaction(model); 
    }

    void SwnGmToolAPI::ClearMap() 
    { 
        this->SGTFactionControl->ClearMap(); 
    }

    Asset_List SwnGmToolAPI::GetAssetList(int factionIndex)
    {
        return this->SGTFactionControl->GetAssetList(factionIndex);
    }

    void SwnGmToolAPI::AddAsset(int factionIndex, AssetModel asset)
    {
        this->SGTFactionControl->AddAsset(factionIndex, asset);
    }

    void SwnGmToolAPI::RemoveAsset(int factionIndex, int assetIndex)
    {
        this->SGTFactionControl->RemoveAsset(factionIndex, assetIndex);
    }
    
    void SwnGmToolAPI::ClearAssets(int factionIndex)
    {
        this->SGTFactionControl->ClearAssets(factionIndex);
    }
}