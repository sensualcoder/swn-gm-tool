#ifndef FACTION_CONTROL_HPP
#define FACTION_CONTROL_HPP

#include <cstdint>
#include <list>
#include <map>
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

    struct RatingXpHp
    {
        uint8_t XP;
        uint8_t HP;
    };

    const std::map<int, RatingXpHp> RatingXpHpTable
    {
        { 1, { 0, 1 } },
        { 2, { 2, 2 } },
        { 3, { 4, 4 } },
        { 4, { 6, 6 } },
        { 5, { 9, 9 } },
        { 6, { 12, 12 } },
        { 7, { 16, 16 } },
        { 8, { 20, 20 } }
    };

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
            int CalcHpFromAttributes(const FactionCreateModel&);
            int CalcIncomeFromAttributes(const FactionCreateModel&);
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
