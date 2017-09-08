#include "FactionAssetMap.hpp"

namespace SwnGmTool
{
    FactionAssetMap::FactionAssetMap()
    {
        Head = Tail = NULL;
        MapSize = 0;
    }
    
    FactionAssetMap::~FactionAssetMap()
    {
        this->clear();
    }

    FactionAssetMap::iterator FactionAssetMap::find(std::string name)
    {
    }

    void FactionAssetMap::clear()
    {
        if(MapSize == 0)
            return;

        for(auto it = this->begin(); it != this->end(); it++)
        {
            this->erase(it);
            MapSize--;
        }
    }

    void FactionAssetMap::erase(iterator& it)
    {
    }

    MapNode* FactionAssetMap::insert(const FactionManager&)
    {
    }

    size_t FactionAssetMap::size()
    {
        return MapSize;
    }
}