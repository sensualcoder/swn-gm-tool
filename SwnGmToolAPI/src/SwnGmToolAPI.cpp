#include "SwnGmToolAPI.hpp"

namespace SwnGmTool
{
    // Public methods

    SwnGmToolAPI* SwnGmToolAPI::CreateAPI(ConfigModel config)
    {
        SwnGmToolAPI* api = new SwnGmToolAPI();
        api->Init(config);

        return api;
    }

    // Private methods

    bool SwnGmToolAPI::Init(ConfigModel config)
    {
        this->SGTConfig = config;

        if(this->SGTConfig.Version == "0")
            return false;

        this->SGTFactionControl = std::unique_ptr<FactionControl>(new FactionControl(this->SGTConfig) );
        this->SGTSectorGen = std::unique_ptr<SectorGen>(new SectorGen() );

        return true;
    }
}