#ifndef FACTION_CONTROL_HPP
#define FACTION_CONTROL_HPP

#include <cstdint>
#include <string>
#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

#include "AssetModel.hpp"
#include "Config.hpp"
#include "FactionModel.hpp"
#include "FactionAssetMap.hpp"

namespace SwnGmTool
{
    typedef std::list<AssetModel> Asset_List;
    typedef std::vector<FactionModel> Faction_List;

    class FactionControl
    {
        public:
            FactionControl() { }
            FactionControl(Config);
            ~FactionControl();

            int GetMapSize();
            void ClearMap();

            const Faction_List GetFactionList();
            void AddFaction(std::string);
            void AddFaction(const FactionModel&);
            void RemoveFaction(int);
            void RemoveFaction(std::string);

            const Asset_List GetAssetList(std::string);
            void AddAsset(int, const AssetModel&);
            void RemoveAsset(int, int);
            void RemoveAllAssetsOfType(int, const AssetModel&);

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
