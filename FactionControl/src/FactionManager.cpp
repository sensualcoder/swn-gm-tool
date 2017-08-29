#include "FactionManager.hpp"

namespace SwnGmTool
{
    FactionManager::FactionManager()
    {
        this->AssetMgr = std::unique_ptr<AssetManager>();
    }

    FactionManager::FactionManager(AssetManager* manager)
    {
        this->AssetMgr = std::unique_ptr<AssetManager>(manager);
    }
}
