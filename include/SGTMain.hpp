#ifndef SGTMAIN_HPP
#define SGTMAIN_HPP

#include "FactionControl.hpp"

namespace SwnGmTool
{
    class SGTMain
    {
        public:
            static void run(int, char**);

            SGTMain();

        private:
            void Run();
            void PrintMainMenu();
            void SelectMainMenuOption();

            void CreateFaction();
            void ManageFactions();
            void PrintFactionManagerMenu();
            void SelectFactionManagerMenuOption();

            bool IsRunning;
            FactionControl SGTFactionControl;
    };
}

#endif
