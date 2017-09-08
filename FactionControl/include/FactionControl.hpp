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

    struct ControlDTO
    {
        FactionManager* Faction;
        AssetList* Assets;
    };

    class FactionControl
    {
        public:
            FactionControl() {}
            ~FactionControl();

            int GetMapSize();
            void ClearMap();

            ControlDTO& GetControlDTO();

            FactionList& GetFactionList();
            FactionManager& GetFaction(std::string);
            void AddFaction(std::string);
            void AddFaction(const FactionManager&);
            void RemoveFaction(std::string);

            AssetList& GetAssetList(std::string);
            void AddAsset(AssetList&, const AssetDTO&);

        private:
            FactionAssetMap Map;
    };
}

#endif
