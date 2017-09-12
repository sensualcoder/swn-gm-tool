#ifndef FACTION_ASSET_MAP_HPP
#define FACTION_ASSET_MAP_HPP

#include <list>
#include <string>
#include <vector>

#include "AssetDTO.hpp"
#include "FactionDTO.hpp"

namespace SwnGmTool
{
    typedef std::vector<AssetDTO> Asset_List;

    struct FactionAssetControl
    {
        FactionDTO Faction;
        Asset_List AssetList;
    };

    typedef FactionAssetControl FAC;

    class FactionAssetMap : public std::list<FAC>
    {
        public:
            std::list<FAC>::iterator find(std::string);
    };
}

#endif
