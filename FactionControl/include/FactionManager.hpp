#ifndef FACTION_MANAGER_HPP
#define FACTION_MANAGER_HPP

#include "FactionDTO.hpp"

namespace SwnGmTool
{
    class FactionManager
    {
        public:
            FactionManager() {}
            FactionManager(const FactionManager&);
            FactionManager(FactionDTO);

            FactionDTO GetFaction() const;

        private:
            FactionDTO Faction;
    };
}

template<>
struct std::hash<SwnGmTool::FactionManager>
{
    size_t operator()(const SwnGmTool::FactionManager& f) const
    {
        std::hash<SwnGmTool::FactionDTO> faction_hash;
        const SwnGmTool::FactionDTO& faction = f.GetFaction();
        return faction_hash(faction);
    }
};

template<>
struct std::equal_to<SwnGmTool::FactionManager>
{
    size_t operator()(const SwnGmTool::FactionManager& a, const SwnGmTool::FactionManager& b) const
    {
        return a.GetFaction() == b.GetFaction();
    }
};

#endif
