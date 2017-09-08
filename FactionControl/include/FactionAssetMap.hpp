#ifndef FACTION_ASSET_MAP_HPP
#define FACTION_ASSET_MAP_HPP

#include <memory>
#include <string>

#include "AssetDTO.hpp"
#include "FactionManager.hpp"

namespace SwnGmTool
{
    struct MapNode
    {
        MapNode() : next(nullptr), prev(nullptr) {}

        FactionManager Faction;
        std::vector<AssetDTO> AssetList;

        MapNode* next;
        MapNode* prev;
    };

    class FactionAssetMap
    {
        public:
            class iterator : public std::iterator<std::random_access_iterator_tag, MapNode*> 
            {
                public:
                    explicit iterator(MapNode* node) : cur(node) { }
                    iterator operator++(int) { iterator it = *this; cur = cur->next; return it; }
                    bool operator==(iterator rhs) { return cur == rhs.cur; }
                    bool operator!=(iterator rhs) { return cur != rhs.cur; }
                    reference operator*() { return cur; }
                    reference operator->() { return cur; }

                private:
                    MapNode* cur;
            };
            
            FactionAssetMap();
            ~FactionAssetMap();

            iterator begin() const { return iterator(Head); }
            iterator end() const { return iterator(nullptr); }
            iterator find(std::string);

            void clear();
            iterator erase(FactionManager&);
            iterator erase(iterator&);
            iterator push_back(const FactionManager&);
            size_t size();

            MapNode* operator[](int);
            MapNode* operator[](std::string);

        private:
            MapNode* Head;
            MapNode* Tail;

            size_t MapSize;
    };
}

#endif
