#include "Driver.hpp"

#include <chrono>
#include <fstream>

#include <cereal/archives/json.hpp>

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
            std::string log_file("logs/log_");
            time_t log_time = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now() );
            log_file += std::to_string(log_time);
            
            this->Logger = spdlog::rotating_logger_mt("file_logger", log_file, 1024 * 1024 * 5, 3);
            spdlog::drop_all();
        }
        catch(const spdlog::spdlog_ex& ex)
        {
            fmt::print("Log init failure:\n\t{0}\n", ex.what() );
            return false;
        }
        catch(const std::exception& ex)
        {
            fmt::print("Log init failure:\n\t{0}\n", ex.what() );
            return false;
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
            this->Logger->warn("Loading from config file failed, falling back to default\n");

            config = SwnGmTool::ConfigModel
            { 
                .DefaultFactionCount = 5 
            };
        }
        catch(const std::exception& ex)
        {
            this->Logger->error("Loading from config file failed:\n\t{0}\n", ex.what() );
        }

        // Init the SwnGmTool API
        this->SGTAPI = std::make_unique<SwnGmTool::SwnGmToolAPI>(config);
        
        // Load default asset list
        std::ifstream inAsset("Config/DefaultAssets.json");
        SwnGmTool::FileAccess<std::vector<SwnGmTool::AssetModel> > assetAccess;

        try
        {
            assetAccess.Load(inAsset, AssetList);
        }
        catch(cereal::RapidJSONException ex)
        {
            this->Logger->warn("Loading from default asset list file failed:\n\t{0}\n", ex.what() );
        }
        catch(const std::exception& ex)
        {
            this->Logger->error("Loading from asset list file failed:\n\t{0}\n", ex.what() );
        }
        
        // Build the menu option map
        this->BuildOptionMap();

        return true;
    }

    void Driver::BuildOptionMap()
    {
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

        MenuOptionFactory<DriverFunc>::BuildMenuOptionMapFromList(
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

        MenuOptionFactory<DriverFunc>::BuildMenuOptionMapFromList(
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

        MenuOptionFactory<DriverFunc>::BuildMenuOptionMapFromList(
            assetManagerMenuOptions,
            this->AssetManagerOptions,
            this->AssetManagerOptionMap
        );
    }

    void Driver::Run()
    {
        if(this->Init() != true)
        {
            this->Logger->error("Error on init");         
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
            this->Logger->error("Unable to load from file\nStack trace:\n{0}", ex.what() );
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
            this->Logger->error("Unable to save to file\nStack trace:\n{0}", ex.what() );
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

    void Driver::GetMenuInput(const std::map<char, DriverFunc>& options)
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
        std::stringstream stream;
        this->SGTAPI->GetFactionList(stream);     
        cereal::JSONInputArchive archive(stream);

        SwnGmTool::FAC::Faction_List list;
        archive(list);

        fmt::print("\nFaction List:\n");

        if(list.size() <= 0)
        {
            fmt::print("Empty\n");
            return;
        }

        fmt::print("{0:<10} {1:20}\n", "Index", "Name");

        for(size_t i = 0; i < list.size(); ++i)
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
            this->Logger->error("Unable to create faction\nStack trace:\n{0}", ex.what() );
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
            this->Logger->error("Invalid index\nStack trace:\n{0}", ex.what() );
            return;
        }

        std::stringstream stream;
        this->SGTAPI->GetFactionDetails(i, stream);
        cereal::JSONInputArchive archive(stream);

        SwnGmTool::FactionModel item;
        archive(item);

        fmt::print("\nFaction Details\n");
        fmt::print("{0:<15} {1:>10}\n", "Name:", item.Name);
        fmt::print("{0:<15} {1:>10}\n", "Description:", item.Description);
        fmt::print("{0:<15} {1:>10}\n", "Force:", item.Force);
        fmt::print("{0:<15} {1:>10}\n", "Cunning:", item.Cunning);
        fmt::print("{0:<15} {1:>10}\n", "Wealth:", item.Wealth);
        fmt::print("{0:<15} {1:>10}\n", "Income:", item.Income);
        fmt::print("{0:<15} {1:>10}\n", "FacCreds:", item.Treasury);
        fmt::print("{0:<15} {1:>10}/{2}\n", "HP:", item.CurrentHp, item.MaxHp);
        fmt::print("{0:<15} {1:>10}\n", "Exp:", item.Experience);
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
            this->Logger->error("Invalid index\nStack trace:\n{0}", ex.what() );
            return;
        }

        auto listStr = this->SGTAPI->GetAssetList(choice);
        cereal::JSONInputArchive archive(listStr);

        SwnGmTool::FAC::Asset_List list;
        archive(list);

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
        int count = this->SGTAPI->GetFactionCount();

        if(count == 0)
        {
            fmt::print("\nFaction List is empty\n");
            return;
        }

        int index = this->GetIndexInput("Select which asset list to clear\n", count);

        this->SGTAPI->ClearAssets(index);

        fmt::print("\nAsset list cleared\n");
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
            this->Logger->error(error);
            
            throw ex;
        }

        if(i < min || i > max)
        {
            std::string error = fmt::format("Value should be between {0} and {1}, was: {2}", min, max, i);
            this->Logger->error(error);

            throw std::exception();
        }

        return i;
    }

    int Driver::GetIndexInput(std::string prompt, int max)
    {
        return this->GetIntInput(prompt, 0, max - 1);
    }
}