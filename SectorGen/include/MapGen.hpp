#ifndef MAP_GEN_HPP
#define MAP_GEN_HPP

#include <memory>

#include "HexMap.hpp"

namespace SwnGmTool
{
    class MapGen
    {
        public:
            MapGen(HexGrid::HexMap* = NULL);
            MapGen(int, int, HexGrid::HexMap* = NULL);

            HexGrid::HexMap GetMap();

        private:
            std::unique_ptr<HexGrid::HexMap> MapPtr;
    };

    MapGen::MapGen(HexGrid::HexMap* map)
    {
        this->MapPtr = (map == NULL) ? std::unique_ptr<HexGrid::HexMap>()
                        : std::unique_ptr<HexGrid::HexMap>(map);
    }

    MapGen::MapGen(int mapWidth, int mapHeight, HexGrid::HexMap* map)
    {
        this->MapPtr = (map == NULL) ? std::unique_ptr<HexGrid::HexMap>(new HexGrid::HexMap(mapWidth, mapHeight) )
                        : std::unique_ptr<HexGrid::HexMap>(map);
    }

    HexGrid::HexMap MapGen::GetMap()
    {
        return *(this->MapPtr);
    }
}

#endif
