#ifndef FACTION_CONTROL_HPP
#define FACTION_CONTROL_HPP

#include <string>
#include <unordered_map>
#include <vector>

#include "Faction.hpp"
#include "Asset.hpp"

namespace SwnGmTool
{
    class FactionControl
    {
        public:
            const Faction& GetFaction(std::string);
            const std::vector<Faction> GetFactionList();
            void AddFaction(Faction);
            void RemoveFaction(std::string);
            void ClearFactionList();

            const std::vector<Asset> GetAssetList(std::string);
            void AddAsset(std::string, Asset);
            void RemoveAsset(std::string, std::string);
            void ClearAssetList(std::string);

            int GetMapSize();
            void ClearMap();

        private:
            std::unordered_map<Faction, std::vector<Asset> >::iterator FindFaction(std::string);
            std::vector<Asset>::iterator FindAsset(std::string, std::string);

            std::unordered_map<Faction, std::vector<Asset> > FactionAssetMap;
    };
}

#endif
