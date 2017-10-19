#include "HexMap.hpp"

#include <cmath>

namespace HexGrid
{
    HexMap::HexMap()
    {
        this->MapSet = std::unordered_set<Hex>();
    }

    int HexMap::Size()
    {
        return this->MapSet.size();
    }
}