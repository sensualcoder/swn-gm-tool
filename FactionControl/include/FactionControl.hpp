#ifndef FACTION_CONTROL_HPP
#define FACTION_CONTROL_HPP

#include <cstdint>
#include <list>
#include <map>
#include <string>
#include <vector>

#include <cereal/cereal.hpp>

#include "AssetModel.hpp"
#include "FactionAssetMap.hpp"
#include "FactionModel.hpp"
#include "FactionCreateModel.hpp"

namespace SwnGmTool
{
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
            FactionControl(int = 0);
            ~FactionControl();

            int GetFactionCount() const;
            const FAC::Faction_List GetFactionList();
            const FactionModel GetFactionDetails(int);
            void AddFaction(const FactionModel&);
            void AddFaction(const FactionCreateModel&);
            int CalcHpFromAttributes(const FactionCreateModel&);
            int CalcIncomeFromAttributes(const FactionCreateModel&);
            void RemoveFaction(int);
            void ClearMap();

            const FAC::Asset_List GetAssetList(int);
            void AddAsset(int, const AssetModel&);
            void RemoveAsset(int, int);
            void RemoveAllAssetsOfType(int, const AssetModel&);
            void ClearAssets(int);

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
