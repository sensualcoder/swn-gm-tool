#ifndef MAP_GEN_HPP
#define MAP_GEN_HPP

#include <memory>

#include "Map.hpp"

namespace SwnGmTool
{
    template <class T>
    class MapGen
    {
        public:
            MapGen(Map<T>* = NULL);

        private:
            std::unique_ptr<Map<T>> MapPtr;
    };

    template <class T>
    MapGen<T>::MapGen(Map<T>* map)
    {
        this->MapPtr = std::unique_ptr<Map<T>>(map);
    }
}

#endif
