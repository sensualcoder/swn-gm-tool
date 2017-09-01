#include "Map.hpp"

namespace HexGrid
{
    Map::Map()
    {
    }

    Map::Map(int mapWidth, int mapHeight)
    {
        CreateMap(mapWidth, mapHeight);
    }

    void Map::CreateMap(int mapWidth, int mapHeight)
    {
        for(int q = 0; q < mapWidth; q++)
        {
            int q_offset = floor(q/2);
            for(int r = -q_offset; r < mapHeight - q_offset; r++)
            {
                MapSet.insert(Hex(q, r, -q-r));
            }
        }
    }

    std::unordered_set<Hex> Map::GetMap()
    {
        return MapSet;
    }
}