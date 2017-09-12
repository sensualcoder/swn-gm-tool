#ifndef FACTION_CONTROL_HPP
#define FACTION_CONTROL_HPP

#include <string>
#include <vector>

#include "AssetDTO.hpp"
#include "FactionDTO.hpp"
#include "FactionAssetMap.hpp"

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

            FactionList& GetFactionList();
            FactionDTO& GetFaction(std::string);
            void AddFaction(std::string);
            void AddFaction(const FactionDTO&);
            void RemoveFaction(std::string);

            AssetList& GetAssetList(std::string);

        private:
            FactionAssetMap Map;
    };
}

#endif
