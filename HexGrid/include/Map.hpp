#ifndef MAP_HPP
#define MAP_HPP

#include <cmath>
#include <unordered_set>

#include "Hex.hpp"

namespace HexGrid
{
    class Map
    {
        public:
            Map();
            Map(int, int mapHeight);
            void CreateMap(int mapWidth, int mapHeight);
            
            std::unordered_set<Hex> GetMap();

        private:
            std::unordered_set<Hex> MapSet;
    };
}

#endif
