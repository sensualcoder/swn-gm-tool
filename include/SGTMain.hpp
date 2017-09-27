#ifndef SGT_MAIN_HPP
#define SGT_MAIN_HPP

#include <iostream>
#include <string>
#include <vector>

#include "SGTMenuOptions.hpp"
#include "FactionManager.hpp"

namespace SwnGmTool
{
    class SGTMain
    {
        public:
            static void run(int, char**);

        private:
            SGTMain();

            void PrintMenu(const std::vector<MenuOption>&, std::ostream& = std::cout);

            void Run();
            void PrintMainMenu(std::ostream& = std::cout);
            void SelectMainMenuOption();

            bool IsRunning;
            FactionManager FM;
    };
}

#endif
