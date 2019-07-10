#ifndef SECTOR_GEN_HPP
#define SECTOR_GEN_HPP

#include <list>
#include <memory>

#include "HexMap.hpp"
#include "Planet.hpp"
#include "SwnHex.hpp"

namespace SwnGmTool
{
    const int STD_MAP_WIDTH = 8;
    const int STD_MAP_HEIGHT = 10;
    const int MIN_STAR_MOD = 20;

    class SectorGen
    {
        public:
            SectorGen(int = STD_MAP_WIDTH, int = STD_MAP_HEIGHT);

            void CreateFTVRMap(int, int);

            void GenerateSector(int = MIN_STAR_MOD);
            void ClearSector();

            Planet GenerateRandomPlanet();

            int GetMapSize();
            int GetSystemListSize();

            std::list<SwnHex> GetSystemList() const;
            std::list<Planet> GetPlanetList() const;

        private:
            int MapWidth;
            int MapHeight;

            HexGrid::HexMap SectorMap;
            std::list<SwnHex> SystemList;
    };
}

#endif
