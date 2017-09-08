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
                MapNode* cur;

                public:
                    explicit iterator(MapNode* node) : cur(node) { }
                    iterator& operator++() { cur = cur->next; }
                    iterator operator++(int) { }
                    bool operator==(iterator rhs) { }
                    bool operator!=(iterator rhs) { }
                    reference operator*() { return cur; }
                    reference operator->() { return cur; }
            };
            
            FactionAssetMap();
            ~FactionAssetMap();

            iterator begin() { return iterator(Head); }
            iterator end() { return iterator(Tail); }
            iterator find(std::string);

            void clear();
            void erase(FactionManager&);
            void erase(iterator&);
            MapNode* insert(const FactionManager&);
            MapNode* insert(const std::vector<AssetDTO>&);
            size_t size();

            MapNode* operator[](std::string);
            MapNode* operator[](const FactionManager&);

        private:
            MapNode* Head;
            MapNode* Tail;

            size_t MapSize;
    };
}

#endif
