#ifndef MAP_HPP
#define MAP_HPP

#include <vector>

#include "Hex.hpp"

namespace SwnGmTool
{
    template <class T>
    class Map
    {
        public:
            Map();

        private:
            std::vector<std::vector<T>> MapGrid;
    };

    template <class T>
    Map<T>::Map() : MapGrid(10, std::vector<T>(10))
    {
    }
}

#endif
