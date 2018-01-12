#include "SwnGmToolAPI.hpp"

namespace SwnGmTool
{
    SwnGmToolAPI::SwnGmToolAPI(ConfigModel config) : SGTConfig(config), SGTFactionControl(new FactionControl(config) ), SGTSectorGen(new SectorGen)
    {
    }

    SwnGmToolAPI::~SwnGmToolAPI() = default;
    SwnGmToolAPI::SwnGmToolAPI(SwnGmToolAPI && op) noexcept = default;
    SwnGmToolAPI& SwnGmToolAPI::operator=(SwnGmToolAPI && op) noexcept = default;

    ConfigModel SwnGmToolAPI::GetConfig()
    { 
        return this->SGTConfig; 
    }

    Faction_List SwnGmToolAPI::GetFactionList()
    { 
        return this->SGTFactionControl->GetFactionList();
    }

    void SwnGmToolAPI::AddFaction(FactionModel model) 
    { 
        this->SGTFactionControl->AddFaction(model); 
    }

    void SwnGmToolAPI::ClearMap() 
    { 
        this->SGTFactionControl->ClearMap(); 
    }
}