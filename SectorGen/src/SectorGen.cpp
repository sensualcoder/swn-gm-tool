#include "SectorGen.hpp"

#include <ctime>
#include <random>

#include "Random.hpp"

namespace SwnGmTool
{
    SectorGen::SectorGen(int mapWidth, int mapHeight) 
        : SectorMap(HexGrid::HexMap() ), MapWidth(mapWidth), MapHeight(mapHeight)
    {
        this->CreateFTVRMap(mapWidth, mapHeight);
    }

    // Creates a map with flat-topped hexagons in a vertical rectangular configuration (FTVR).
    // TODO: Add in functions to create other map styles (triangular, hexagonal, etc.) and pointy-topped hexagon orientation.
    void SectorGen::CreateFTVRMap(int mapWidth, int mapHeight)
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
        std::uniform_int_distribution<int> star_dist {1, 10};

        int total_stars = star_dist(prng() ) + starsMod;

        for(int i = 0; i < total_stars; i++)
        {
            std::uniform_int_distribution<int> q_dist {0, this->MapWidth};   
            int q = q_dist(prng() );
            
            int q_offset = std::floor( (q+1)/2);
            
            std::uniform_int_distribution<int> r_dist {0, this->MapHeight - q_offset};
            int r = r_dist(prng() );

            auto hex = this->SectorMap.MapSet.find(HexGrid::Hex(q, r) );

            if(hex != this->SectorMap.MapSet.end() )
            {
                this->SystemList.push_back(SwnHex(*hex) );
            }
        }

        for(auto system : this->SystemList)
        {
            std::uniform_int_distribution<int> planet_dist {0, 4};
            int planets = planet_dist(prng() );

            for(int i = 0; i < planets; i++)
            {
                system.Planets.push_back(Planet() );
            }
        }
    }

    void SectorGen::ClearSector()
    {
        this->SectorMap.clear();
        this->SystemList.clear();
    }

    Planet SectorGen::GenerateRandomPlanet()
    {
        Planet planet;

        return planet;
    }

    int SectorGen::GetMapSize()
    {
        return this->SectorMap.size();
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
