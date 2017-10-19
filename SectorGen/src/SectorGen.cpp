#include "SectorGen.hpp"

#include <ctime>

namespace SwnGmTool
{
    SectorGen::SectorGen(int mapWidth, int mapHeight) 
        : SectorMap(HexGrid::HexMap() ), MapWidth(mapWidth), MapHeight(mapHeight)
    {
        this->CreateMap(mapWidth, mapHeight);
    }

    void SectorGen::CreateMap(int mapWidth, int mapHeight)
    {
        for(int q = 0; q < mapWidth; q++)
        {
            int q_offset = std::floor( (q+1)/2);
            for(int r = -q_offset; r < mapHeight - q_offset; r++)
            {
                this->SectorMap.MapSet.insert(HexGrid::Hex(q, r, -q-r) );
            }
        }
    }

    void SectorGen::GenerateSector(int starsMod)
    {
        std::srand(std::time(0) );

        int total_stars = (1 + (std::rand() % 10)) + starsMod;

        for(int i = 0; i < total_stars; i++)
        {
            int q = std::rand() % this->MapWidth;
            int q_offset = std::floor( (q+1)/2);
            int r = std::rand() % this->MapHeight - q_offset;

            auto hex = this->SectorMap.MapSet.find(HexGrid::Hex(q, r) );

            if(hex != this->SectorMap.MapSet.end() )
                this->SystemList.push_back(SwnHex(*hex) );
        }

        for(auto system : this->SystemList)
        {
            int planets = std::rand() % 3 + 1;

            for(int i = 0; i < planets; i++)
            {
                system.Planets.push_back(Planet() );
            }
        }
    }

    int SectorGen::GetMapSize()
    {
        return this->SectorMap.Size();
    }

    int SectorGen::GetSystemListSize()
    {
        return this->SystemList.size();
    }

    std::list<SwnHex> SectorGen::GetSystemList() const
    {
        return this->SystemList;
    }

    std::list<Planet> SectorGen::GetPlanetList() const
    {
        std::list<Planet> planetList;

        for(auto system : this->SystemList)
        {
            for(auto planet : system.Planets)
            {
                planetList.push_back(planet);
            }
        }

        return planetList;
    }
}
