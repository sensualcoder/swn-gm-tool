#ifndef FACTION_MANAGER_HPP
#define FACTION_MANAGER_HPP

#include <iostream>
#include <map>

#include "FactionControl.hpp"

namespace SwnGmTool
{
    class FactionManager
    {
        public:
            FactionManager();
            void ManageFactions();

            void PrintFactionManagerMenu(std::ostream& = std::cout);
            void SelectFactionManagerMenuOption();
            void ShowFactionList(std::ostream& = std::cout);
            void CreateFaction();
            void RemoveFaction();
            void ClearFactionList();

            void Save(std::ostream& = std::cout);
            void Load(std::istream& = std::cin);

        private:
            void PrintMenu(const std::map<char, std::string>&, std::ostream& = std::cout);

            bool IsRunning;
            FactionControl FMFactionControl;
    };
}

#endif
