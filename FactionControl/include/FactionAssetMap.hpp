#ifndef FACTION_ASSET_MAP_HPP
#define FACTION_ASSET_MAP_HPP

#include <list>
#include <string>
#include <vector>

#include "AssetDTO.hpp"
#include "FactionDTO.hpp"

namespace SwnGmTool
{
    typedef std::list<AssetDTO> Asset_List;

    struct FactionAssetControl
    {
        FactionDTO Faction;
        Asset_List AssetList;
    };

    typedef FactionAssetControl FAC;

    class FactionAssetMap : public std::vector<FAC>
    {
        public:
            std::vector<FAC>::iterator find(std::string);
    };
}

#endif
