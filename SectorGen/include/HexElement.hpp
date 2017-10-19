#ifndef HEX_ELEMENT_HPP
#define HEX_ELEMENT_HPP

#include <string>

namespace SwnGmTool
{
    struct HexElement
    {
        HexElement(std::string label) : Label(label) {} 

        std::string Label;
    };
}

#endif
