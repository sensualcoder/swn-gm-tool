#ifndef FACTION_CONTROL_HPP
#define FACTION_CONTROL_HPP

#include <cstdint>
#include <string>
#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/vector.hpp>

#include "AssetDTO.hpp"
#include "FactionDTO.hpp"
#include "FactionAssetMap.hpp"

namespace SwnGmTool
{
    typedef std::list<AssetDTO> Asset_List;
    typedef std::vector<FactionDTO> Faction_List;

    class FactionControl
    {
        public:
            FactionControl(uint8_t = 5);
            ~FactionControl();

            int GetMapSize();
            void ClearMap();

            Faction_List GetFactionList();
            FactionDTO& GetFaction(std::string);
            void AddFaction(std::string);
            void AddFaction(const FactionDTO&);
            void RemoveFaction(int);
            void RemoveFaction(std::string);

            Asset_List& GetAssetList(std::string);

            template <class Archive>
            void serialize(Archive& archive)
            {
                archive(this->Map);
            }

        private:
            FactionAssetMap Map;
    };
}

#endif
