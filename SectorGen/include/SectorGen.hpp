#ifndef SECTOR_GEN_HPP
#define SECTOR_GEN_HPP

#include "MapGen.hpp"
#include "Planet.hpp"

namespace SwnGmTool
{
    class SectorGen : public MapGen<Planet>
    {
    };
}

#endif
