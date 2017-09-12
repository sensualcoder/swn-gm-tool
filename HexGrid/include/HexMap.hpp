#ifndef HEX_MAP_HPP
#define HEX_MAP_HPP

#include <unordered_set>

#include "Hex.hpp"

namespace HexGrid
{
    class HexMap
    {
        public:
            HexMap();
            HexMap(int, int mapHeight);
            void CreateMap(int mapWidth, int mapHeight);
            
            const std::unordered_set<Hex>& GetMap();

        private:
            std::unordered_set<Hex> MapSet;
    };
}

#endif
