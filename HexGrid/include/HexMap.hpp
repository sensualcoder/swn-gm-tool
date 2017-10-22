#ifndef HEX_MAP_HPP
#define HEX_MAP_HPP

#include <cmath>
#include <unordered_set>

#include "Hex.hpp"

namespace HexGrid
{
    struct HexMap
    {
        HexMap();
        
        int size();
        void clear();

        std::unordered_set<Hex> MapSet;
    };
}

#endif
