#ifndef SECTOR_GEN_HPP
#define SECTOR_GEN_HPP

#include "MapGen.hpp"
#include "SwnHex.hpp"

namespace SwnGmTool
{
    const int STD_MAP_WIDTH = 8;
    const int STD_MAP_HEIGHT = 10;

    class SectorGen : public MapGen
    {
        public:
            SectorGen(int = STD_MAP_WIDTH, int = STD_MAP_HEIGHT);
    };
}

#endif
