#ifndef SECTOR_GEN_HPP
#define SECTOR_GEN_HPP

#include "MapGen.hpp"
#include "Planet.hpp"
#include "SwnHex.hpp"

namespace SwnGmTool
{
    class SectorGen : public MapGen<SwnHex<Planet>>
    {
    };
}

#endif
