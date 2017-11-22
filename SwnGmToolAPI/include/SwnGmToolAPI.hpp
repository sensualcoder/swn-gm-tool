#ifndef SWN_GM_TOOL_API_HPP
#define SWN_GM_TOOL_API_HPP

#include <memory>
#include <string>

#include "ConfigModel.hpp"
#include "FactionControl.hpp"
#include "SectorGen.hpp"

namespace SwnGmTool
{
    class SwnGmToolAPI
    {
        public:
            static SwnGmToolAPI* CreateAPI(ConfigModel);

            ConfigModel GetConfig() { return this->SGTConfig; }
            Faction_List GetFactionList() { return this->SGTFactionControl->GetFactionList(); }
            void AddFaction(FactionModel model) { this->SGTFactionControl->AddFaction(model); }
            void ClearMap() { this->SGTFactionControl->ClearMap(); }

            template <class Archive>
            void serialize(Archive& archive)
            {
                archive(cereal::make_nvp("FactionControl", *this->SGTFactionControl) );
            }

        private:
            SwnGmToolAPI() { }

            bool Init(ConfigModel);

            ConfigModel SGTConfig;

            std::unique_ptr<FactionControl> SGTFactionControl;
            std::unique_ptr<SectorGen> SGTSectorGen;
    };
}

#endif
