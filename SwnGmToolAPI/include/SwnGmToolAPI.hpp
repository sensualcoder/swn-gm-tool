#ifndef SWN_GM_TOOL_API_HPP
#define SWN_GM_TOOL_API_HPP

#include <memory>
#include <string>

#include <cereal/cereal.hpp>

#include "ConfigModel.hpp"
#include "FactionControl.hpp"
#include "SectorGen.hpp"

namespace SwnGmTool
{
    class SwnGmToolAPI
    {
        public:
            SwnGmToolAPI(ConfigModel);
            SwnGmToolAPI(SwnGmToolAPI &&) noexcept;
            SwnGmToolAPI& operator=(SwnGmToolAPI &&) noexcept;
            ~SwnGmToolAPI();

            ConfigModel GetConfig();

            Faction_List GetFactionList();
            void AddFaction(FactionModel);
            void ClearMap();

            Asset_List GetAssetList(int);
            void AddAsset(int, AssetModel);
            void RemoveAsset(int, int);
            void ClearAssets(int);

            template <class Archive>
            void serialize(Archive& archive)
            {
                archive(cereal::make_nvp("Faction Control", *this->SGTFactionControl) );
            }

        private:
            ConfigModel SGTConfig;

            std::unique_ptr<FactionControl> SGTFactionControl;
            std::unique_ptr<SectorGen> SGTSectorGen;
    };
}

#endif
