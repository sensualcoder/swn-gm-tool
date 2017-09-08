#include "FactionAssetMap.hpp"

namespace SwnGmTool
{
    FactionAssetMap::FactionAssetMap()
    {
        this->Head = this->Tail = nullptr;
        MapSize = 0;
    }
    
    FactionAssetMap::~FactionAssetMap()
    {
        this->clear();
    }

    FactionAssetMap::iterator FactionAssetMap::find(std::string name)
    {
        for(auto it = this->begin(); it != this->end(); it++)
        {
            if(it->Faction.GetFaction().Name == name)
                return it;
        }
    }

    void FactionAssetMap::clear()
    {
        for(auto it = this->begin(); it != this->end(); )
        {
            MapNode* cur = *it;
            it++;
            delete cur;
        }

        this->Head = this->Tail = nullptr;
        MapSize = 0;
    }

    FactionAssetMap::iterator FactionAssetMap::erase(iterator& it)
    {
        MapNode* toDelete = *it;

        if(*it == this->Head)
        {
            this->Head = this->Head->next;

            delete toDelete;
            MapSize--;
            return iterator(this->Head);
        }

        it->prev->next = it->next;

        if(it->next != nullptr)
            it->next->prev = it->prev;

        if(toDelete == this->Tail)
            this->Tail = it->prev;

        delete toDelete;
        MapSize--;
        return iterator(it->prev);
    }

    FactionAssetMap::iterator FactionAssetMap::push_back(const FactionManager& faction)
    {
        MapNode* node = new MapNode();
        node->Faction = faction;

        if(this->Head == nullptr)
        {
            this->Head = node;
            node->prev = nullptr;
            node->next = nullptr;
            this->Tail = this->Head;

            MapSize++;
            return iterator(this->Head);
        }
        
        this->Tail->next = node;
        node->prev = this->Tail;
        this->Tail = node;

        MapSize++;
        return iterator(this->Tail);
    }

    size_t FactionAssetMap::size()
    {
        return MapSize;
    }

    MapNode* FactionAssetMap::operator[](int index)
    {
    }

    MapNode* FactionAssetMap::operator[](std::string)
    {
    }
}