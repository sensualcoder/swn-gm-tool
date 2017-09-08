#ifndef FACTION_MANAGER_HPP
#define FACTION_MANAGER_HPP

#include <string>

#include "FactionDTO.hpp"

namespace SwnGmTool
{
    class FactionManager
    {
        public:
            FactionManager();
            FactionManager(std::string);
            FactionManager(const FactionManager&);
            FactionManager(const FactionDTO&);

            FactionDTO GetFaction() const;
            void SetFaction(const FactionDTO&);

        private:
            FactionDTO Faction;
    };
}

template<>
struct std::equal_to<SwnGmTool::FactionManager>
{
    size_t operator()(const SwnGmTool::FactionManager& a, const SwnGmTool::FactionManager& b) const
    {
        return a.GetFaction() == b.GetFaction();
    }
};

#endif
