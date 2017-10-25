#ifndef PLANET_INFO_HPP
#define PLANET_INFO_HPP

#include <list>
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
        {"Corrosive",           "Corrosive", ""},
        {"Inert",               "Inert gas", ""},
        {"Airless",             "Airless or thin atmosphere", ""},
        {"Breathable",          "Breathable mix", ""},
        {"Thick",               "Thick atmosphere, breathable with a pressure mask", ""},
        {"Toxic",               "Invasive, toxic atmosphere", ""},
        {"Corrosive & Toxic",   "Corrosive and invasive atmosphere", ""}
    };

    const std::list<PlanetInfo> TemperatureTypes 
    {
        {"Frozen",          "Frozen", ""},
        {"Variable Cold",   "Variable cold-to-temperate", ""},
        {"Cold",            "Cold", ""},
        {"Temperate",       "Temperate", ""},
        {"Warm",            "Warm", ""},
        {"Variable Warm",   "Variable temperate-to-warm", ""},
        {"Burning",         "Burning", ""}
    };

    const std::list<PlanetInfo> BiosphereTypes 
    {
    };

    const std::list<PlanetInfo> PopulationTypes
    {
    };

    const std::list<PlanetInfo> TechLevels
    {
        {"TL0",     "Tech Level 0", ""},
        {"TL1",     "Tech Level 1", ""},
        {"TL2",     "Tech Level 2", ""},
        {"TL3",     "Tech Level 3", ""},
        {"TL4",     "Tech Level 4", ""},
        {"TL4+",    "Tech Level 4 w/ specialties / pretech", ""},
        {"TL5",     "Tech Level 5", ""}
    };
}

#endif