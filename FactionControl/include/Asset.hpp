#ifndef ASSET_HPP
#define ASSET_HPP

#include <string>

namespace SwnGmTool
{
    struct Asset
    {
        std::string Name;
    };
}

template<>
struct std::hash<SwnGmTool::Asset>
{
    size_t operator()(const SwnGmTool::Asset& a) const
    {
        std::hash<std::string> string_hash;
        return string_hash(a.Name);
    }
};


template<>
struct std::equal_to<SwnGmTool::Asset>
{
    bool operator()(const SwnGmTool::Asset& a, const SwnGmTool::Asset& b) const
    {
        return a.Name == b.Name;
    };
};

#endif
