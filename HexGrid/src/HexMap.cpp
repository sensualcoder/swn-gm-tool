#include "HexMap.hpp"

#include <cmath>

namespace HexGrid
{
    HexMap::HexMap()
    {
        this->MapSet = std::unordered_set<Hex>();
    }

    int HexMap::size()
    {
        return this->MapSet.size();
    }

    void HexMap::clear()
    {
        this->MapSet.clear();
    }
}