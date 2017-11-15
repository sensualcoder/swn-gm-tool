#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <iostream>
#include <memory>
#include <vector>

#include <fmt/format.h>
#include <fmt/format.cc>
#include <fmt/ostream.h>
#include <fmt/ostream.cc>

#include "ConfigManager.hpp"
#include "FactionControl.hpp"
#include "MenuOptions.hpp"
#include "SectorGen.hpp"

namespace Driver
{
    struct SGTMain
    {
        std::unique_ptr<SwnGmTool::ConfigManager> CM;
        std::unique_ptr<SwnGmTool::FactionControl> FC;
        std::unique_ptr<SwnGmTool::SectorGen> SG;
    };

    class Driver
    {
        public:
            Driver();

            bool Init();
            void Run(std::ostream& = std::cout);

            void PrintMenu(const std::vector<MenuOption>&, std::ostream& = std::cout);
            void PrintMainMenu(std::ostream& = std::cout);
            void PrintFactionMenu(std::ostream& = std::cout);

            void GetMainMenuInput(std::istream& = std::cin);
            void GetFactionControlInput(std::istream& = std::cin);

            void RunFactionControl();
            void ShowFactionList(std::ostream& = std::cout);
            void AddFaction(std::ostream& = std::cout, std::istream& = std::cin);
            void RemoveFaction(std::istream& = std::cin);
            void ClearFactionlist();

            void RunAssetControl();
            void AddAsset();
            void RemoveAsset();
            void RemoveAllAssetsOfType();
            void ClearAssetList();

            void Save(std::ostream& out = std::cout);
            void Load(std::istream& in = std::cin);

        private:
            SGTMain Main;
            bool IsRunning;
            bool IsRunningFC;
            bool IsRunningAC;
    };
}

#endif
