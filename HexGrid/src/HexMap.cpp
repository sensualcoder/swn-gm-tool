#include "HexMap.hpp"

#include <cmath>

namespace HexGrid
{
    HexMap::HexMap()
    {
    }

    HexMap::HexMap(int mapWidth, int mapHeight)
    {
        CreateMap(mapWidth, mapHeight);
    }

    void HexMap::CreateMap(int mapWidth, int mapHeight)
    {
        for(int q = 0; q < mapWidth; q++)
        {
            int q_offset = std::floor(q/2);
            for(int r = -q_offset; r < mapHeight - q_offset; r++)
            {
                MapSet.insert(Hex(q, r, -q-r));
            }
        }
    }

    const std::unordered_set<Hex>& HexMap::GetMap()
    {
        return MapSet;
    }
}