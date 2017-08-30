#ifndef HEX_ELEMENT_HPP
#define HEX_ELEMENT_HPP

#include <string>

namespace SwnGmTool
{
    struct HexElement
    {
        std::string Name;

        HexElement(std::string Name) : Name(Name) {} 
    };
}

#endif
