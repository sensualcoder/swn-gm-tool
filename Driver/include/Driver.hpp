#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

#include "MenuOptionFactory.hpp"
#include "SwnGmToolAPI.hpp"

namespace Driver
{
    class Driver
    {
        using DriverFunc = void (Driver::*)();

        public:
            Driver();

            // Main driver methods
            bool Init();
            void BuildOptionMap();
            void Run();
            void Load();
            void Save();
            void Quit();

            // Menu methods
            void PrintMenu(const std::vector<MenuOption>&);
            void PrintMainMenu();
            void PrintFactionMenu();
            void PrintAssetMenu();
            void GetMenuInput(std::map<char, DriverFunc>&);
            void GetMainMenuInput();
            void GetFactionControlInput();
            void GetAssetControlInput();

            // Faction Control methods
            void RunFactionControl();
            void ShowFactionList();
            void AddFaction();
            void RemoveFaction();
            void ClearFactionList();
            void ShowFactionDetails();
            void QuitFactionControl();

            // Asset Manager methods
            void RunAssetControl();
            void AddAsset();
            void RemoveAsset();
            void RemoveAllAssetsOfType();
            void ClearAssetList();
            void QuitAssetControl();

        private:        
            std::unique_ptr<SwnGmTool::SwnGmToolAPI> SGTAPI;

            std::vector<MenuOption> MainMenuOptions;
            std::map<char, DriverFunc> MainMenuOptionMap;

            std::vector<MenuOption> FactionManagerOptions;
            std::map<char, DriverFunc> FactionManagerOptionMap;
            
            std::vector<MenuOption> AssetManagerOptions;
            std::map<char, DriverFunc> AssetManagerOptionMap;
            
            bool IsRunning;
            bool IsRunningFC;
            bool IsRunningAC;
    };
}

#endif
