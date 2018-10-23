#ifndef SWN_GM_TOOL_API_HPP
#define SWN_GM_TOOL_API_HPP

#include <memory>
#include <ostream>
#include <string>

#include <cereal/cereal.hpp>

#include "ConfigModel.hpp"
#include "FactionControl.hpp"
#include "FactionCreateModel.hpp"

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

            int GetFactionCount();
            void GetFactionList(std::ostream& = std::cout);
            void GetFactionDetails(int, std::ostream& = std::cout);
            void AddFaction(FactionModel);
            void AddFaction(FactionCreateModel);
            void RemoveFaction(int);
            void RemoveFaction(FactionModel);
            void ClearFactions();

            int GetAssetCount(int);
            std::stringstream GetAssetList(int);
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
    };
}

#endif
