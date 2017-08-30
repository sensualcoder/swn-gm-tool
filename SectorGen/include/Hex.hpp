#ifndef HEX_HPP
#define HEX_HPP

#include <cassert>
#include <functional>
#include <vector>

namespace SwnGmTool
{
    template <class T>
    struct Hex
    {
        const int v[3];

        std::vector<T> ElementList;

        Hex(int q, int r, int s) : v{q, r, s}
        {
            assert(q + r + s == 0);
        }

        inline int q() const { return v[0]; }
        inline int r() const { return v[1]; }
        inline int s() const { return v[2]; }
    };

    template <class T>
    bool operator==(Hex<T> a, Hex<T> b)
    {
        return a.q() == b.q() && a.r() == b.r() && a.s() == b.s();
    }

    template <class T>
    bool operator!=(Hex<T> a, Hex<T> b)
    {
        return !(a==b);
    }
}

template<class T>
struct std::hash<SwnGmTool::Hex<T>>
{
    size_t operator()(const SwnGmTool::Hex<T>& h) const
    {
        std::hash<int> int_hash;
        size_t hq = int_hash(h.q() );
        size_t hr = int_hash(h.r() );
        return hq ^ (hr + 0x9e3779b9 + (hq << 6) + (hq >> 2) );
    }
};

#endif
