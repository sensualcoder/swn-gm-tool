#ifndef CONFIG_MANAGER_HPP
#define CONFIG_MANAGER_HPP

#include <string>

#include "Config.hpp"

namespace SwnGmTool
{
    class ConfigManager
    {
        public:
            ConfigManager();

            inline Config GetConfig() const { return this->AppConfig; }
            bool Save(std::ostream&);
            bool Load(std::istream&);

        private:
            Config AppConfig;
    };
}

#endif
