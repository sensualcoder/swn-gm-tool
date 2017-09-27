#ifndef SGT_MAIN_HPP
#define SGT_MAIN_HPP

#include <iostream>
#include <map>
#include <string>

#include "FactionManager.hpp"

namespace SwnGmTool
{
    class SGTMain
    {
        public:
            static void run(int, char**);

        private:
            SGTMain();

            void PrintMenu(const std::map<char, std::string>&, std::ostream& = std::cout);

            void Run();
            void PrintMainMenu(std::ostream& = std::cout);
            void SelectMainMenuOption();

            bool IsRunning;
            FactionManager FM;
    };
}

#endif
