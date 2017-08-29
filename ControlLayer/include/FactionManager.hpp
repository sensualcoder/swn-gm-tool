#ifndef FACTION_MANAGER_HPP
#define FACTION_MANAGER_HPP

#include <memory>

#include "Manager.hpp"
#include "Faction.hpp"
#include "AssetManager.hpp"

namespace SwnGmTool
{
    class FactionManager : public Manager<Faction>
    {
        public:
            FactionManager();
            FactionManager(AssetManager*);

        private:
            std::unique_ptr<AssetManager> AssetMgr;
    };
}

#endif
