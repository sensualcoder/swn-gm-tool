#include "SwnGmToolAPI.hpp"

#include <cereal/archives/json.hpp>

namespace SwnGmTool
{
    SwnGmToolAPI::SwnGmToolAPI(ConfigModel config) 
        : SGTConfig(config), 
            SGTFactionControl(new FactionControl(config.DefaultFactionCount) )
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

    void SwnGmToolAPI::GetFactionList(std::ostream& out)
    { 
        cereal::JSONOutputArchive archive(out);
        archive(this->SGTFactionControl->GetFactionList() );
    }

    void SwnGmToolAPI::GetFactionDetails(int index, std::ostream& out)
    {
        cereal::JSONOutputArchive archive(out);
        archive(this->SGTFactionControl->GetFactionDetails(index) );
    }

    void SwnGmToolAPI::AddFaction(FactionModel model) 
    { 
        this->SGTFactionControl->AddFaction(model); 
    }

    void SwnGmToolAPI::AddFaction(FactionCreateModel model) 
    { 
        this->SGTFactionControl->AddFaction(model); 
    }

    void SwnGmToolAPI::ClearFactions() 
    { 
        this->SGTFactionControl->ClearMap(); 
    }

    std::stringstream SwnGmToolAPI::GetAssetList(int factionIndex)
    {
        std::stringstream stream;
        cereal::JSONOutputArchive archive(stream);
        archive(this->SGTFactionControl->GetAssetList(factionIndex) );

        return stream;
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