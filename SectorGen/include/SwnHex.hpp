#ifndef SWN_HEX_HPP
#define SWN_HEX_HPP

#include <vector>

#include "Hex.hpp"

namespace SwnGmTool
{
    template<class T>
    struct SwnHex : public HexGrid::Hex
    {
        SwnHex(int q, int r, int s) : HexGrid::Hex{q, r, s} {}

        std::vector<T> ElementList;
    };

    template<class T>
    bool operator==(SwnHex<T> a, SwnHex<T> b)
    {
        return a == b;
    }

    template<class T>
    bool operator!=(SwnHex<T> a, SwnHex<T> b)
    {
        return !(a==b);
    }
}

template <class T>
struct std::hash<SwnGmTool::SwnHex<T>> : public std::hash<HexGrid::Hex>
{
};

#endif
