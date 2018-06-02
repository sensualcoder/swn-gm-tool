#ifndef FACTION_ASSET_MAP_HPP
#define FACTION_ASSET_MAP_HPP

#include <list>
#include <map>
#include <string>
#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/list.hpp>
#include <cereal/types/map.hpp>
#include <cereal/types/vector.hpp>

#include "AssetModel.hpp"
#include "FactionModel.hpp"

namespace SwnGmTool
{
    namespace FAC
    {
        using Asset_List = std::list<AssetModel>;
        using Faction_List = std::vector<FactionModel>;
        using FAC = std::pair<const FactionModel, Asset_List>;
    }

    class FactionAssetMap
    {
        public:
            using fa_map = std::map<FactionModel, FAC::Asset_List>;
            using iterator = fa_map::iterator;
            using const_iterator = fa_map::const_iterator;

            iterator begin() { return this->Map.begin(); }
            iterator end() { return this->Map.end(); }
            const_iterator begin() const { return this->Map.begin(); }
            const_iterator end() const { return this->Map.end(); }
            const_iterator cbegin() const { return this->Map.cbegin(); }
            const_iterator cend() const { return this->Map.cend(); }

            void clear() { this->Map.clear(); }
            void emplace(const FactionModel& faction, const FAC::Asset_List& assets) { this->Map.emplace(faction, assets); }
            void erase(iterator it) { this->Map.erase(it); }
            size_t size() { return this->Map.size(); }

            template <class Archive>
            void serialize(Archive& archive)
            {
                archive(cereal::make_nvp("Faction Asset Map", this->Map) );
            }

        private:
            fa_map Map;
    };
}

#endif
