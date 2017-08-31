#ifndef SWN_HEX_HPP
#define SWN_HEX_HPP

#include <vector>

#include "Hex.hpp"
#include "HexElement.hpp"

namespace SwnGmTool
{
    struct SwnHex : public HexGrid::Hex
    {
        SwnHex(int q, int r, int s) : HexGrid::Hex{q, r, s} {}

        std::vector<HexElement> ElementList;
    };

    bool operator==(SwnHex a, SwnHex b)
    {
        return a == b;
    }

    bool operator!=(SwnHex a, SwnHex b)
    {
        return !(a==b);
    }
}

template <>
struct std::hash<SwnGmTool::SwnHex> : public std::hash<HexGrid::Hex>
{
};

#endif
