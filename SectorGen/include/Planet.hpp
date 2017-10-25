#ifndef PLANET_HPP
#define PLANET_HPP

#include <list>

#include "HexElement.hpp"
#include "PlanetInfo.hpp"
#include "PlanetTags.hpp"

namespace SwnGmTool
{
    struct Planet : public HexElement
    {
        Planet(std::string name = "") : HexElement(name) {}

        PlanetInfo Atmosphere;
        PlanetInfo Temperature;
        PlanetInfo Biosphere;
        PlanetInfo Population;
        PlanetInfo TechLevel;

        std::list<PlanetTag> Tags;
    };
}

#endif
