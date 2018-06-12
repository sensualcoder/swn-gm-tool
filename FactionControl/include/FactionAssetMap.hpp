#ifndef FACTION_ASSET_MAP_HPP
#define FACTION_ASSET_MAP_HPP

#include <list>
#include <map>
#include <string>
#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/memory.hpp>
#include <cereal/types/vector.hpp>

#include "AssetModel.hpp"
#include "FactionModel.hpp"

namespace SwnGmTool
{
    namespace FAC
    {
        using Asset_List = std::list<AssetModel>;
        using Asset_List_Ptr = std::shared_ptr<Asset_List>;
        using Faction_Ptr = std::shared_ptr<FactionModel>;
        using Faction_List = std::vector<FactionModel>;
        using FAC = std::pair<const FactionModel, Asset_List>;
    }

    class FactionAssetMap
    {
        public:
            FactionAssetMap(int);

            using fa_map = std::map<FAC::Faction_Ptr, FAC::Asset_List_Ptr>;
            using iterator = fa_map::iterator;
            using const_iterator = fa_map::const_iterator;

            iterator begin() { return this->Map.begin(); }
            iterator end() { return this->Map.end(); }
            const_iterator begin() const { return this->Map.begin(); }
            const_iterator end() const { return this->Map.end(); }
            const_iterator cbegin() const { return this->Map.cbegin(); }
            const_iterator cend() const { return this->Map.cend(); }

            void clear();
            void emplace(const FactionModel& faction, const FAC::Asset_List& assets);
            void erase(iterator it);
            size_t size();

            template <class Archive>
            void serialize(Archive& archive)
            {
                archive(cereal::make_nvp("Faction Asset Map", this->Map) );
            }

        private:
            fa_map Map;

            std::vector<FAC::Asset_List_Ptr> AssetLists;
            std::vector<FAC::Faction_Ptr> FactionList;
    };
}

#endif
