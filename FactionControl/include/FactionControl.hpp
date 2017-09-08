#ifndef FACTION_CONTROL_HPP
#define FACTION_CONTROL_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "AssetDTO.hpp"
#include "FactionAssetMap.hpp"
#include "FactionManager.hpp"

namespace SwnGmTool
{
    typedef std::vector<AssetDTO> AssetList;
    typedef std::vector<FactionDTO> FactionList;

    class FactionControl
    {
        public:
            FactionControl() {}
            ~FactionControl();

            int GetMapSize();
            void ClearMap();

            MapNode* GetFactionNode(std::string);

            FactionList& GetFactionList();
            FactionManager& GetFaction(std::string);
            void AddFaction(std::string);
            void AddFaction(const FactionManager&);
            void RemoveFaction(std::string);

            AssetList& GetAssetList(std::string);

        private:
            FactionAssetMap Map;
    };
}

#endif
