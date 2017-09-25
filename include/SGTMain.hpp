#ifndef SGT_MAIN_HPP
#define SGT_MAIN_HPP

#include <iostream>
#include <map>
#include <string>

#include "FactionControl.hpp"

namespace SwnGmTool
{
    class SGTMain
    {
        public:
            static void run(int, char**);

            SGTMain();

        private:
            void PrintMenu(const std::map<char, std::string>&, std::ostream& = std::cout);

            void Run();
            void PrintMainMenu(std::ostream& = std::cout);
            void SelectMainMenuOption();

            void CreateFaction();
            void ManageFactions();
            void ShowFactionList(std::ostream& = std::cout);
            void PrintFactionManagerMenu(std::ostream& = std::cout);
            void SelectFactionManagerMenuOption();

            bool IsRunning;
            bool IsFM;
            FactionControl SGTFactionControl;
    };
}

#endif
