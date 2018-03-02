#ifndef FACTION_CONTROL_HPP
#define FACTION_CONTROL_HPP

#include <cstdint>
#include <string>
#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

#include "AssetModel.hpp"
#include "ConfigModel.hpp"
#include "FactionModel.hpp"
#include "FactionAssetMap.hpp"

namespace SwnGmTool
{
    using Asset_List = std::list<AssetModel>;
    using Faction_List = std::vector<FactionModel>;

    struct FactionTemplate
    {
        uint8_t Attributes[3];
        uint8_t MaxHP;
        uint8_t MajorAssets;
        uint8_t MinorAssets;
    };

    const FactionTemplate NEW_FACTION_STATS       = { { 2, 1, 1 }, 8, 1, 0 };
    const FactionTemplate MINOR_FACTION_STATS     = { { 4, 3, 1 }, 15, 1, 1 };
    const FactionTemplate MAJOR_FACTION_STATS     = { { 6, 5, 3 }, 29, 2, 2 };
    const FactionTemplate REGIONAL_FACTION_STATS  = { { 8, 7, 5 }, 49, 4, 4 };

    class FactionControl
    {
        public:
            FactionControl() { }
            FactionControl(ConfigModel);
            ~FactionControl();

            int GetMapSize();
            void ClearMap();

            const Faction_List GetFactionList();
            const FactionModel GetFactionDetails(int);
            void AddFaction(const FactionModel&);
            void RemoveFaction(int);

            const Asset_List GetAssetList(int);
            void AddAsset(int, const AssetModel&);
            void RemoveAsset(int, int);
            void RemoveAllAssetsOfType(int, const AssetModel&);
            void ClearAssets(int);

            template <class Archive>
            void serialize(Archive& archive)
            {
                archive(cereal::make_nvp("Faction List", this->Map) );
            }

        private:
            FactionAssetMap Map;
    };
}

#endif
