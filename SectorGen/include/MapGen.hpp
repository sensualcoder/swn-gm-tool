#ifndef MAP_GEN_HPP
#define MAP_GEN_HPP

#include <memory>

#include "Map.hpp"

namespace SwnGmTool
{
    template <class T>
    class MapGen
    {
        public:
            MapGen(HexGrid::Map<T>* = NULL);
            MapGen(int, int, HexGrid::Map<T>* = NULL);

            HexGrid::Map<T>* GetMap();

        private:
            std::unique_ptr<HexGrid::Map<T>> MapPtr;
    };

    template <class T>
    MapGen<T>::MapGen(HexGrid::Map<T>* map)
    {
        this->MapPtr = (map == NULL) ? std::unique_ptr<HexGrid::Map<T>>()
                        : std::unique_ptr<HexGrid::Map<T>>(map);
    }

    template <class T>
    MapGen<T>::MapGen(int mapWidth, int mapHeight, HexGrid::Map<T>* map)
    {
        this->MapPtr = (map == NULL) ? std::unique_ptr<HexGrid::Map<T> >(new HexGrid::Map<T>(mapWidth, mapHeight) )
                        : std::unique_ptr<HexGrid::Map<T>>(map);
    }

    template <class T>
    HexGrid::Map<T>* MapGen<T>::GetMap()
    {
        return *MapPtr;
    }
}

#endif
