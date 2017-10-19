#ifndef HEX_HPP
#define HEX_HPP

#include <functional>

namespace HexGrid
{
    struct Hex
    {
        Hex(int q, int r) : v{q, r, -q-r} {}
        Hex(int q, int r, int s) : v{q, r, s} {}

        inline int q() const { return v[0]; }
        inline int r() const { return v[1]; }
        inline int s() const { return v[2]; }

        const int v[3];
    };
}

template <>
struct std::hash<HexGrid::Hex>
{
    size_t operator()(const HexGrid::Hex& h) const
    {
        std::hash<int> int_hash;
        size_t hq = int_hash(h.q() );
        size_t hr = int_hash(h.r() );
        return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2) );
    }
};

template<>
struct std::equal_to<HexGrid::Hex>
{
    bool operator()(const HexGrid::Hex& a, const HexGrid::Hex& b) const
    {
        return a.q() == b.q() && a.r() == b.r() && a.s() == b.s();
    };
};

#endif
