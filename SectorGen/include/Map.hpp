#ifndef MAP_HPP
#define MAP_HPP

#include <cmath>
#include <unordered_set>

#include "Hex.hpp"

namespace SwnGmTool
{
    const int STD_MAP_WIDTH = 8;
    const int STD_MAP_HEIGHT = 10;

    template <class T>
    class Map
    {
        public:
            Map(int = STD_MAP_WIDTH, int mapHeight = STD_MAP_HEIGHT);
            void CreateMap(int mapWidth, int mapHeight);
            
            std::unordered_set<T> GetMap();

        private:
            std::unordered_set<T> MapSet;
    };

    template<class T>
    std::unordered_set<T> Map<T>::GetMap()
    {
        return MapSet;
    }

    template<class T>
    Map<T>::Map(int mapWidth, int mapHeight)
    {
        CreateMap(mapWidth, mapHeight);
    }

    template<class T>
    void Map<T>::CreateMap(int mapWidth, int mapHeight)
    {
        for(int q = 0; q < mapWidth; q++)
        {
            int q_offset = floor(q/2);
            for(int r = -q_offset; r < mapHeight - q_offset; r++)
            {
                MapSet.insert(T(q, r, -q-r));
            }
        }
    }
}

#endif
