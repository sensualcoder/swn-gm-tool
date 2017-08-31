#include "Hex.hpp"

#include <cassert>
#include <cmath>
#include <vector>

namespace HexGrid
{
    const std::vector<Hex> hex_directions =
    {
        Hex(1, 0, -1), Hex(1, -1, 0), Hex(0, -1, 1),
        Hex(-1, 0, 1), Hex(-1, 1, 0), Hex(0, 1, -1)
    };

    bool operator==(Hex a, Hex b)
    {
        return a.q() == b.q() && a.r() == b.r() && a.s() == b.s();
    }

    bool operator!=(Hex a, Hex b)
    {
        return !(a==b);
    }

    Hex hex_add(Hex a, Hex b)
    {
        return Hex(a.q() + b.q(), a.r() + b.r(), a.s() + b.s() );
    }

    Hex hex_subtract(Hex a, Hex b)
    {
        return Hex(a.q() - b.q(), a.r() - b.r(), a.s() - b.s() );
    }

    Hex hex_multiply(Hex a, Hex b)
    {
        return Hex(a.q() * b.q(), a.r() * b.r(), a.s() * b.s() );
    }

    int hex_length(Hex hex)
    {
        return int((std::abs(hex.q() + std::abs(hex.r() + std::abs(hex.s() ) ) ) ) / 2);
    }

    int hex_distance(Hex a, Hex b)
    {
        return hex_length(hex_subtract(a, b) );
    }

    Hex hex_direction(int direction)
    {
        assert(0 <= direction && direction < 6);

        return hex_directions[direction];
    }

    Hex hex_neighbor(Hex hex, int direction)
    {
        return hex_add(hex, hex_direction(direction));
    }
}