#ifndef DRIVER_HPP
#define DRIVER_HPP

#include <functional>
#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

// Prevent spdlog from including fmt headers to prevent redefinition errors
#ifndef SPDLOG_FMT_EXTERNAL
#define SPDLOG_FMT_EXTERNAL
#endif

#include "spdlog/spdlog.h"

#include "AssetModel.hpp"
#include "MenuOptionFactory.hpp"
#include "SwnGmToolAPI.hpp"

namespace Driver
{
    class Driver
    {
        using DriverFunc = std::function<void(const Driver&)>;

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
            void ShowAssetList();
            void AddAsset();
            void RemoveAsset();
            void RemoveAllAssetsOfType();
            void RemoveAllAssetsAtLocation();
            void ClearAssetList();
            void ShowAssetDetails();
            void QuitAssetControl();

        private:        
            std::string GetInput(std::string);
            int GetIntInput(std::string, int, int);
            int GetIndexInput(std::string, int);
            void LogError(std::string);

            std::shared_ptr<spdlog::logger> ErrorLog;

            std::unique_ptr<SwnGmTool::SwnGmToolAPI> SGTAPI;

            std::map<SwnGmTool::AssetModel, SwnGmTool::AssetModel> AssetList;

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
