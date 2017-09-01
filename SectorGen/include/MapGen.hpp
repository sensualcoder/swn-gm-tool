#ifndef MAP_GEN_HPP
#define MAP_GEN_HPP

#include <memory>

#include "Map.hpp"

namespace SwnGmTool
{
    class MapGen
    {
        public:
            MapGen(HexGrid::Map* = NULL);
            MapGen(int, int, HexGrid::Map* = NULL);

            HexGrid::Map GetMap();

        private:
            std::unique_ptr<HexGrid::Map> MapPtr;
    };

    MapGen::MapGen(HexGrid::Map* map)
    {
        this->MapPtr = (map == NULL) ? std::unique_ptr<HexGrid::Map>()
                        : std::unique_ptr<HexGrid::Map>(map);
    }

    MapGen::MapGen(int mapWidth, int mapHeight, HexGrid::Map* map)
    {
        this->MapPtr = (map == NULL) ? std::unique_ptr<HexGrid::Map>(new HexGrid::Map(mapWidth, mapHeight) )
                        : std::unique_ptr<HexGrid::Map>(map);
    }

    HexGrid::Map MapGen::GetMap()
    {
        return *(this->MapPtr);
    }
}

#endif
