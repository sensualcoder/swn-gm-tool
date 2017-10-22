#ifndef PLANET_INFO_HPP
#define PLANET_INFO_HPP

#include <string>

namespace SwnGmTool
{
    struct PlanetInfo
    {
        std::string ShortName;
        std::string Name;
        std::string Description;
    };

    const std::list<PlanetInfo> AtmosphereTypes
    {
        {"Corrosive", "Corrosive", ""},
        {"Inert", "Inert gas", ""},
        {"Airless", "Airless or thin atmosphere", ""},
        {"Breathable", "Breathable mix", ""},
        {"Thick", "Thick atmosphere, breathable with a pressure mask", ""},
        {"Toxic", "Invasive, toxic atmosphere", ""},
        {"Corrosive & Toxic", "Corrosive and invasive atmosphere", ""}
    };

    const std::list<PlanetInfo> TemperatureTypes 
    {
    };

    const std::list<PlanetInfo> BiosphereTypes 
    {
    };

    const std::list<PlanetInfo> PopulationTypes
    {
    };

    const std::list<PlanetInfo> WorldTags
    {
    };
}

#endif