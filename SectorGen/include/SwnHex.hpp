#ifndef SWN_HEX_HPP
#define SWN_HEX_HPP

#include <list>
#include <string>

#include "Hex.hpp"
#include "Planet.hpp"

namespace SwnGmTool
{
    struct SwnHex
    {
        SwnHex(const HexGrid::Hex& src, std::string name = "") 
            : HexRef(src), SystemName(name) {}

        std::string SystemName;
        std::list<Planet> Planets;

        HexGrid::Hex HexRef;
    };
}

#endif
