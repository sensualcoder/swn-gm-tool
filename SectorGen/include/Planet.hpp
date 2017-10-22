#ifndef PLANET_HPP
#define PLANET_HPP

#include <list>

#include "HexElement.hpp"
#include "PlanetInfo.hpp"

namespace SwnGmTool
{
    struct Planet : public HexElement
    {
        Planet(std::string name = "") : HexElement(name) {}

        PlanetInfo Atmosphere;
        PlanetInfo Temperature;
        PlanetInfo Biosphere;
        PlanetInfo Population;
        int TechLevel;

        std::list<PlanetInfo> Tags;
    };
}

#endif
