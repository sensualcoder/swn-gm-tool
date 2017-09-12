#include "FactionAssetMap.hpp"

namespace SwnGmTool
{
    std::list<FAC>::iterator FactionAssetMap::find(std::string name)
    {
        for(auto i = begin(); i != end(); i++)
            if(i->Faction.Name == name)
                return i;

        return end();
    }
}