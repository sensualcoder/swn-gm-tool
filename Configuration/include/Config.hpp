#ifndef CONFIG_HPP
#define CONFIG_HPP

#include <string>

#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>

namespace SwnGmTool
{
    struct Config
    {
        std::string Version;
        int DefaultFactionCount;
    };

    template<class Archive>
    void serialize(Archive& archive, Config& c)
    {
        archive(cereal::make_nvp("Version", c.Version),
                cereal::make_nvp("Default Faction Count", c.DefaultFactionCount) );
    }
}

#endif
