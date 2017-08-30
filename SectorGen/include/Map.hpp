#ifndef MAP_HPP
#define MAP_HPP

#include <cmath>
#include <unordered_set>

#include "Hex.hpp"

namespace SwnGmTool
{
    template <class T>
    class Map
    {
        public:
            Map(int mapWidth, int mapHeight);

        private:
            std::unordered_set<T> MapSet;
    };

    template<class T>
    Map<T>::Map(int mapWidth, int mapHeight)
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
