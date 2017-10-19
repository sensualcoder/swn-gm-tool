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
        
        int Size();

        std::unordered_set<Hex> MapSet;
    };
}

#endif
