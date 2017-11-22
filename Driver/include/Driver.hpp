#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <iostream>
#include <memory>
#include <vector>

#include "spdlog/spdlog.h"

#include "MenuOptions.hpp"
#include "SwnGmToolAPI.hpp"

namespace Driver
{
    class Driver
    {
        public:
            Driver();

            bool Init();
            void Run();

            void PrintMenu(const std::vector<MenuOption>&);
            void PrintMainMenu();
            void PrintFactionMenu();

            void GetMainMenuInput(std::istream& = std::cin);
            void GetFactionControlInput(std::istream& = std::cin);

            void RunFactionControl();
            void ShowFactionList();
            void AddFaction(std::istream& = std::cin);
            void RemoveFaction(std::istream& = std::cin);
            void ClearFactionlist();

            void RunAssetControl();
            void AddAsset();
            void RemoveAsset();
            void RemoveAllAssetsOfType();
            void ClearAssetList();

            void Save(std::ostream& = std::cout);
            void Load(std::istream& in = std::cin);

        private:
            std::shared_ptr<spdlog::logger> _clogger;          
            std::unique_ptr<SwnGmTool::SwnGmToolAPI> SGTAPI;
            
            bool IsRunning;
            bool IsRunningFC;
            bool IsRunningAC;
    };
}

#endif
