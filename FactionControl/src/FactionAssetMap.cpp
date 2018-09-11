#include "FactionAssetMap.hpp"

namespace SwnGmTool
{    
    FactionAssetMap::FactionAssetMap(int size)
    {
        AssetLists.reserve(size);
        FactionList.reserve(size);
    }

    void FactionAssetMap::clear()
    {
        this->Map.clear();
        this->AssetLists.clear();
        this->FactionList.clear();
    }

    void FactionAssetMap::emplace(const FactionModel& faction, const FAC::Asset_List& assets) 
    {
        auto factionPos = this->FactionList.insert(this->FactionList.end(), 
                std::make_shared<FactionModel>(faction) );
        auto assetPos = this->AssetLists.insert(this->AssetLists.end(),
                std::make_shared<FAC::Asset_List>(assets) );

        this->Map[*factionPos] = *assetPos;
    }
    
    void FactionAssetMap::erase(iterator it)
    {
        if(it == this->Map.end() )
            return;

        for(auto item = this->AssetLists.begin(); item != this->AssetLists.end(); )
        {
            if(*item == it->second)
                this->AssetLists.erase(item);
            else   
                item++;
        }

        for(auto item = this->FactionList.begin(); item != this->FactionList.end();)
        {
            if(*item == it->first)
                this->FactionList.erase(item);
            else
                item++;
        }

        this->Map.erase(it);
    }

    size_t FactionAssetMap::size() const
    {
        return this->Map.size();
    }
}