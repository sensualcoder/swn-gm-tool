#include "Hex.hpp"

#include <cmath>
#include <vector>

const std::vector<HexGrid::Hex> hex_directions =
{
    HexGrid::Hex(1, 0, -1), HexGrid::Hex(1, -1, 0), HexGrid::Hex(0, -1, 1),
    HexGrid::Hex(-1, 0, 1), HexGrid::Hex(-1, 1, 0), HexGrid::Hex(0, 1, -1)
};

bool operator==(HexGrid::Hex a, HexGrid::Hex b)
{
    return a.q() == b.q() && a.r() == b.r() && a.s() == b.s();
}

bool operator!=(HexGrid::Hex a, HexGrid::Hex b)
{
    return !(a==b);
}

HexGrid::Hex hex_add(HexGrid::Hex a, HexGrid::Hex b)
{
    return HexGrid::Hex(a.q() + b.q(), a.r() + b.r(), a.s() + b.s() );
}

HexGrid::Hex hex_subtract(HexGrid::Hex a, HexGrid::Hex b)
{
    return HexGrid::Hex(a.q() - b.q(), a.r() - b.r(), a.s() - b.s() );
}

HexGrid::Hex hex_multiply(HexGrid::Hex a, HexGrid::Hex b)
{
    return HexGrid::Hex(a.q() * b.q(), a.r() * b.r(), a.s() * b.s() );
}

int hex_length(HexGrid::Hex hex)
{
    return int((std::abs(hex.q() + std::abs(hex.r() + std::abs(hex.s() ) ) ) ) / 2);
}

int hex_distance(HexGrid::Hex a, HexGrid::Hex b)
{
    return hex_length(hex_subtract(a, b) );
}

HexGrid::Hex hex_direction(int direction)
{
    return hex_directions[direction];
}

HexGrid::Hex hex_neighbor(HexGrid::Hex hex, int direction)
{
    return hex_add(hex, hex_direction(direction));
}