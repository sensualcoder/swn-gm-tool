#include "Driver.hpp"

#include <fstream>

#include <fmt/format.h>
#include <fmt/format.cc>

#include "FileAccess.hpp"

namespace Driver
{
    Driver::Driver()
    {
        this->IsRunning = false;
        this->IsRunningFC = false;
        this->IsRunningAC = false;
    }

    bool Driver::Init()
    {
        try
        {
            // Init spdlog
            this->ErrorLog = spdlog::rotating_logger_mt("error_logger", "logs/errors", 1024 * 1024 * 5, 3);
            spdlog::drop_all();
        }
        catch(const spdlog::spdlog_ex& ex)
        {
            fmt::print("Log init failure:\n\t{0}\n", ex.what() );
            return false;
        }
        catch(const std::exception& ex)
        {
            this->ErrorLog->error(ex.what() );
        }

        SwnGmTool::ConfigModel config;

        // Init config
        std::ifstream inConf("Config/DefaultConfig.json");
        SwnGmTool::FileAccess<SwnGmTool::ConfigModel> confAccess;

        try
        {
            confAccess.Load(inConf, config);
        }        
        catch(cereal::RapidJSONException ex)
        {
            this->ErrorLog->warn("WARN: Loading from config file failed, falling back to default");

            config = SwnGmTool::ConfigModel
            { 
                .DefaultFactionCount = 5 
            };
        }
        catch(const std::exception& ex)
        {
            this->ErrorLog->error(ex.what() );
        }

        // Init the SwnGmTool API
        this->SGTAPI = std::unique_ptr<SwnGmTool::SwnGmToolAPI>(new SwnGmTool::SwnGmToolAPI(config) );
        
        // Load default asset list
        std::ifstream inAsset("Config/DefaultAssets.json");
        SwnGmTool::FileAccess<std::map<SwnGmTool::AssetModel, SwnGmTool::AssetModel> > assetAccess;

        try
        {
            assetAccess.Load(inAsset, AssetList);
        }
        catch(cereal::RapidJSONException ex)
        {
            this->ErrorLog->warn("WARN: Loading from default asset list file failed");
        }
        catch(const std::exception& ex)
        {
            this->ErrorLog->error(ex.what() );
        }
        
        // Build the menu option map
        this->BuildOptionMap();

        return true;
    }

    void Driver::BuildOptionMap()
    {
        std::unique_ptr<MenuOptionFactory<DriverFunc> > optionFactory;

        // Main Menu options
        std::vector<MenuOptionMap<DriverFunc> > mainMenuOptions
        {
            {
                .Option = '1',
                .Label = "Manage Factions",
                .OptionFunc = std::bind(&Driver::RunFactionControl, this)
            },
            {
                .Option = '2',
                .Label = "Manage Sector",
                .OptionFunc = nullptr
            },
            {
                .Option = 'Q',
                .Label = "Quit",
                .OptionFunc = std::bind(&Driver::Quit, this)
            }
        };

        optionFactory->BuildMenuOptionMapFromList(
            mainMenuOptions,
            this->MainMenuOptions,
            this->MainMenuOptionMap
        );

        // Faction Manager options
        std::vector<MenuOptionMap<DriverFunc> > factionManagerMenuOptions
        {
            {
                .Option = '1',
                .Label = "Show Faction List",
                .OptionFunc = std::bind(&Driver::ShowFactionList, this)
            },
            {
                .Option = '2',
                .Label = "Add Faction",
                .OptionFunc = std::bind(&Driver::AddFaction, this)
            },
            {
                .Option = '3',
                .Label = "Remove Faction",
                .OptionFunc = std::bind(&Driver::RemoveFaction, this)
            },
            {
                .Option = '4',
                .Label = "Clear Faction List",
                .OptionFunc = std::bind(&Driver::ClearFactionList, this)
            },
            {
                .Option = '5',
                .Label = "Show Faction Details",
                .OptionFunc = std::bind(&Driver::ShowFactionDetails, this)
            },
            {
                .Option = '6',
                .Label = "Manage Faction Assets",
                .OptionFunc = std::bind(&Driver::RunAssetControl, this)
            },
            {
                .Option = 'L',
                .Label = "Load from file",
                .OptionFunc = std::bind(&Driver::Load, this)
            },
            {
                .Option = 'S',
                .Label = "Save to file",
                .OptionFunc = std::bind(&Driver::Save, this)
            },
            {
                .Option = 'Q',
                .Label = "Quit Faction Manager",
                .OptionFunc = std::bind(&Driver::QuitFactionControl, this)
            }
        };

        optionFactory->BuildMenuOptionMapFromList(
            factionManagerMenuOptions,
            this->FactionManagerOptions,
            this->FactionManagerOptionMap
        );

        // Asset Manager options
        std::vector<MenuOptionMap<DriverFunc> > assetManagerMenuOptions
        {
            {
                .Option = '1',
                .Label = "Show Asset List",
                .OptionFunc = std::bind(&Driver::ShowAssetList, this)
            },
            {
                .Option = '2',
                .Label = "Add Asset",
                .OptionFunc = std::bind(&Driver::AddAsset, this)
            },
            {
                .Option = '3',
                .Label = "Remove Asset",
                .OptionFunc = std::bind(&Driver::RemoveAsset, this)
            },
            {
                .Option = '4',
                .Label = "Remove all Assets of Type",
                .OptionFunc = std::bind(&Driver::RemoveAllAssetsOfType, this)
            },
            {
                .Option = '5',
                .Label = "Remove all Assets at Location",
                .OptionFunc = std::bind(&Driver::RemoveAllAssetsAtLocation, this)
            },
            {
                .Option = '6',
                .Label = "Clear Asset List",
                .OptionFunc = std::bind(&Driver::ClearAssetList, this)
            },
            {
                .Option = '7',
                .Label = "Show Asset Detail",
                .OptionFunc = std::bind(&Driver::ShowAssetDetails, this)
            },
            {
                .Option = 'Q',
                .Label = "Quit Asset Manager",
                .OptionFunc = std::bind(&Driver::QuitAssetControl, this)
            }
        };

        optionFactory->BuildMenuOptionMapFromList(
            assetManagerMenuOptions,
            this->AssetManagerOptions,
            this->AssetManagerOptionMap
        );
    }

    void Driver::Run()
    {
        if(this->Init() != true)
        {
            this->ErrorLog->error("Error on init");         
            return;
        }

        fmt::print("Stars Without Number GM Tool\n");

        this->IsRunning = true;

        while(this->IsRunning)
        {
            this->PrintMainMenu();
            this->GetMainMenuInput();
        }

        fmt::print("\nQuitting...\n");
    }

    void Driver::Load()
    {
        std::ifstream is("save.sgt");

        SwnGmTool::FileAccess<SwnGmTool::SwnGmToolAPI> access;

        try
        {
            access.Load(is, *this->SGTAPI);
        }
        catch(const std::exception& ex)
        {
            fmt::print("Unable to load from file\n");
            this->ErrorLog->error("Unable to load from file\nStack trace:\n{0}", ex.what() );
            return;
        }
    }

    void Driver::Save()
    {
        std::ofstream os("save.sgt");

        SwnGmTool::FileAccess<SwnGmTool::SwnGmToolAPI> access;

        try
        {
            access.Save(os, *this->SGTAPI, "Driver");
        }
        catch(const std::exception& ex)
        {
            fmt::print("Unable to save to file\n");
            this->ErrorLog->error("Unable to save to file\nStack trace:\n{0}", ex.what() );
            return;
        }
    }

    void Driver::Quit()
    {
        IsRunning = false;
    }

    void Driver::PrintMenu(const std::vector<MenuOption>& options)
    {
        fmt::print("\nChoose an option\n");

        for(auto i : options)
        {
            fmt::print("{0}) {1}\n", i.Option, i.Label);
        }
        
        fmt::print("> ");
    }

    void Driver::PrintMainMenu()
    {
        this->PrintMenu(MainMenuOptions);
    }

    void Driver::PrintFactionMenu()
    {
        this->PrintMenu(FactionManagerOptions);
    }

    void Driver::PrintAssetMenu()
    {
        this->PrintMenu(AssetManagerOptions);
    }

    void Driver::GetMenuInput(std::map<char, DriverFunc>& options)
    {
        std::string input;
        std::getline(std::cin, input);

        auto funcIndex = options.find(std::toupper(input[0]) );

        if(funcIndex != options.end() )
        {
            auto func = funcIndex->second;
            
            if(func != nullptr)
            {
                func(*this);
            }
        }
        else
        {
            fmt::print("\nInvalid option\n");
        }
    }

    void Driver::GetMainMenuInput()
    {
        this->GetMenuInput(this->MainMenuOptionMap);
    }

    void Driver::GetFactionControlInput()
    {
        this->GetMenuInput(this->FactionManagerOptionMap);
    }

    void Driver::GetAssetControlInput()
    {
        this->GetMenuInput(this->AssetManagerOptionMap);
    }

    void Driver::RunFactionControl()
    {
        this->IsRunningFC = true;
        
        while(this->IsRunningFC)
        {
            this->PrintFactionMenu();
            this->GetFactionControlInput();
        }
    }

    void Driver::ShowFactionList()
    {
        auto list = this->SGTAPI->GetFactionList();

        fmt::print("\nFaction List:\n");

        if(list.size() <= 0)
        {
            fmt::print("Empty\n");
            return;
        }

        fmt::print("{0:<10} {1:20}\n", "Index", "Name");

        for(int i = 0; i < list.size(); i++)
        {
            fmt::print("{0:<10} {1:20}\n", i, list[i].Name);
        }
    }

    void Driver::AddFaction()
    {
        SwnGmTool::FactionCreateModel faction;

        fmt::print("\nAdd Faction\n");

        faction.Name = this->GetInput("Enter a name");

        try
        {
            faction.Force = this->GetIntInput("Enter Force", 1, 8);
            faction.Cunning = this->GetIntInput("Enter Cunning", 1, 8);
            faction.Wealth = this->GetIntInput("Enter Wealth", 1, 8);
        }
        catch(const std::exception& ex)
        {
            fmt::print("Unable to create faction\n");
            this->ErrorLog->error("Unable to create faction\nStack trace:\n{0}", ex.what() );
            return;
        }

        this->SGTAPI->AddFaction(faction);
    }

    void Driver::RemoveFaction()
    {
    }

    void Driver::ClearFactionList()
    {
        this->SGTAPI->ClearFactions();

        fmt::print("\nFaction list cleared\n");
    }

    void Driver::ShowFactionDetails()
    {
        this->ShowFactionList();
        int i;
        
        try
        {
            i = this->GetIndexInput("\nEnter faction index", this->SGTAPI->GetFactionCount() );
        }
        catch(const std::exception& ex)
        {
            fmt::print("Invalid index\n");
            this->ErrorLog->error("Invalid index\nStack trace:\n{0}", ex.what() );
            return;
        }

        auto item = this->SGTAPI->GetFactionDetails(i);

        fmt::print("\nFaction Details\n");
        fmt::print("{0:<15} {1:>10}\n", "Name:", item.Name);
        fmt::print("{0:<15} {1:>10}\n", "Description:", item.Description);
        fmt::print("{0:<15} {1:>10}\n", "Force:", item.Force);
        fmt::print("{0:<15} {1:>10}\n", "Cunning:", item.Cunning);
        fmt::print("{0:<15} {1:>10}\n", "Wealth:", item.Wealth);
        fmt::print("{0:<15} {1:>10}\n", "Income:", item.Income);
        fmt::print("{0:<15} {1:>10}\n", "FacCreds:", item.FacCreds);
        fmt::print("{0:<15} {1:>10}/{2}\n", "HP:", item.CurrentHP, item.MaxHP);
        fmt::print("{0:<15} {1:>10}\n", "Exp:", item.Exp);
    }

    void Driver::QuitFactionControl()
    {
        this->IsRunningFC = false;
    }

    void Driver::RunAssetControl()
    {
        this->IsRunningAC = true;

        while(IsRunningAC)
        {
            this->PrintAssetMenu();
            this->GetAssetControlInput();
        }
    }

    void Driver::ShowAssetList()
    {
        int count = this->SGTAPI->GetFactionCount();

        if(count == 0)
        {
            fmt::print("\nFaction List is empty\n");
            return;
        }

        this->ShowFactionList();

        int choice;

        try
        {
            choice = this->GetIndexInput("\nShow assets from which faction?", this->SGTAPI->GetFactionCount() );
        }
        catch(const std::exception& ex)
        {
            fmt::print("Invalid index\n");
            this->ErrorLog->error("Invalid index\nStack trace:\n{0}", ex.what() );
            return;
        }

        auto list = this->SGTAPI->GetAssetList(choice);

        fmt::print("\nAsset List\n");

        if(list.size() <= 0)
        {
            fmt::print("Empty\n");
            return;
        }

        fmt::print("{0:<10} {1:20}\n", "Index", "Name");

        int i = 0;
        for(auto l : list)
        {
            fmt::print("{0:<10} {1:20}\n", i, l.Name);
            i++;
        }
    }
    
    void Driver::AddAsset()
    {
    }
    
    void Driver::RemoveAsset()
    {
    }
    
    void Driver::RemoveAllAssetsOfType()
    {
    }

    void Driver::RemoveAllAssetsAtLocation()
    {
    }
    
    void Driver::ClearAssetList()
    {
    }

    void Driver::ShowAssetDetails()
    {
    }

    void Driver::QuitAssetControl()
    {
        this->IsRunningAC = false;
    }

    // Private methods

    std::string Driver::GetInput(std::string prompt)
    {
        fmt::print("{0}\n", prompt);
        fmt::print("> ");

        std::string input;
        std::getline(std::cin, input);

        return input;
    }

    int Driver::GetIntInput(std::string prompt, int min, int max)
    {
        std::string input = this->GetInput(prompt);

        int i;

        try
        {
            i = std::stoi(input);
        }
        catch(const std::exception& ex)
        {
            std::string error = fmt::format("Value entered was invalid: {0}\n", input);
            this->LogError(error);
            
            throw ex;
        }

        if(i < min || i > max)
        {
            std::string error = fmt::format("Value should be between {0} and {1}, was: {2}", min, max, i);
            this->LogError(error);

            throw std::exception();
        }

        return i;
    }

    int Driver::GetIndexInput(std::string prompt, int max)
    {
        return this->GetIntInput(prompt, 0, max - 1);
    }

    void Driver::LogError(std::string error)
    {
        fmt::print(error + "\n");
        this->ErrorLog->error(error);
    }
}