#include "ConfigManager.hpp"

#include <fmt/format.h>
#include <fmt/format.cc>
#include <fmt/printf.h>
#include <fmt/printf.cc>

#include "FileAccess.hpp"

namespace SwnGmTool
{
    ConfigManager::ConfigManager()
    {
        this->AppConfig = Config();
    }

    bool ConfigManager::Save(std::ostream& out)
    {
        FileAccess<Config> access;

        try
        {
            access.Save(out, this->AppConfig, "Config");
        }
        catch(std::exception ex)
        {
            fmt::print("Error saving config file\n");
            return false;
        }

        return true;
    }

    bool ConfigManager::Load(std::istream& in)
    {
        FileAccess<Config> access;
        
        try
        {
            access.Load(in, this->AppConfig);
        }
        catch(std::exception ex)
        {
            fmt::print("Error loading config file\n");
            return false;
        }

        return true;
    }
}