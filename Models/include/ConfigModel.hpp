#ifndef CONFIG_MODEL_HPP
#define CONFIG_MODEL_HPP

#include <string>

#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>

namespace SwnGmTool
{
    struct ConfigModel
    {
        ConfigModel() : Version("0"), DefaultFactionCount(0) { }

        std::string Version;
        int DefaultFactionCount;
    };

    template<class Archive>
    void serialize(Archive& archive, ConfigModel& c)
    {
        archive(cereal::make_nvp("Version", c.Version),
                cereal::make_nvp("Default Faction Count", c.DefaultFactionCount) );
    }
}

#endif
