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
#include "FactionCreateModel.hpp"
#include "FactionAssetMap.hpp"

namespace SwnGmTool
{
    using Asset_List = std::list<AssetModel>;
    using Faction_List = std::vector<FactionModel>;

    class FactionControl
    {
        public:
            FactionControl() { }
            FactionControl(ConfigModel);
            ~FactionControl();

            const int GetFactionCount();
            const Faction_List GetFactionList();
            const FactionModel GetFactionDetails(int);
            void AddFaction(const FactionModel&);
            void AddFaction(const FactionCreateModel&);
            void RemoveFaction(int);
            void ClearMap();

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
