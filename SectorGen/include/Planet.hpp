#ifndef PLANET_HPP
#define PLANET_HPP

#include "HexElement.hpp"

namespace SwnGmTool
{
    struct Planet : public HexElement
    {
        Planet(std::string name = "") : HexElement(name) {}
    };
}

#endif
