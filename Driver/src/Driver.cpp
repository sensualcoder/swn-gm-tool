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
        SwnGmTool::ConfigModel config;

        std::ifstream is("DefaultConfig.json");
        SwnGmTool::FileAccess<SwnGmTool::ConfigModel> access;

        try
        {
            access.Load(is, config);
        }
        catch(cereal::RapidJSONException ex)
        {
            // TODO: Log config load error
            fmt::print("WARN: Loading from config file failed, falling back to default\n");

            config = SwnGmTool::ConfigModel
            { 
                .DefaultFactionCount = 5 
            };
        }

        this->SGTAPI = std::unique_ptr<SwnGmTool::SwnGmToolAPI>(new SwnGmTool::SwnGmToolAPI(config) );
        
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
                .OptionFunc = &Driver::RunFactionControl
            },
            {
                .Option = '2',
                .Label = "Manage Sector",
                .OptionFunc = nullptr
            },
            {
                .Option = 'Q',
                .Label = "Quit",
                .OptionFunc = &Driver::Quit
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
                .OptionFunc = &Driver::ShowFactionList
            },
            {
                .Option = '2',
                .Label = "Add Faction",
                .OptionFunc = &Driver::AddFaction
            },
            {
                .Option = '3',
                .Label = "Remove Faction",
                .OptionFunc = &Driver::RemoveFaction
            },
            {
                .Option = '4',
                .Label = "Clear Faction List",
                .OptionFunc = &Driver::ClearFactionList
            },
            {
                .Option = '5',
                .Label = "Show Faction Details",
                .OptionFunc = &Driver::ShowFactionDetails
            },
            {
                .Option = '6',
                .Label = "Manage Faction Assets",
                .OptionFunc = &Driver::RunAssetControl
            },
            {
                .Option = 'L',
                .Label = "Load from file",
                .OptionFunc = &Driver::Load
            },
            {
                .Option = 'S',
                .Label = "Save to file",
                .OptionFunc = &Driver::Save
            },
            {
                .Option = 'Q',
                .Label = "Quit Faction Manager",
                .OptionFunc = &Driver::QuitFactionControl
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
                .OptionFunc = &Driver::ShowAssetList
            },
            {
                .Option = 'Q',
                .Label = "Quit Asset Manager",
                .OptionFunc = &Driver::QuitAssetControl
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
            // TODO: Log init error
            
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

        access.Load(is, *this->SGTAPI);
    }

    void Driver::Save()
    {
        std::ofstream os("save.sgt");

        SwnGmTool::FileAccess<SwnGmTool::SwnGmToolAPI> access;

        access.Save(os, *this->SGTAPI, "Driver");
    }

    void Driver::Quit()
    {
        if(IsRunning)
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
                (this->*func)();
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
        fmt::print("\nAdd Faction\n");
        fmt::print("Enter a name\n");
        fmt::print("> ");

        std::string name;
        std::getline(std::cin, name);

        SwnGmTool::FactionModel faction
        { 
            .Name = name 
        };

        this->SGTAPI->AddFaction(faction);
    }

    void Driver::RemoveFaction()
    {
    }

    void Driver::ClearFactionList()
    {
        this->SGTAPI->ClearMap();

        fmt::print("\nFaction list cleared\n");
    }

    void Driver::ShowFactionDetails()
    {
    }

    void Driver::QuitFactionControl()
    {
        if(this->IsRunningFC)
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

        fmt::print("\nShow assets from which faction?\n");

        this->ShowFactionList();

        fmt::print("> ");

        std::string input;
        std::getline(std::cin, input);

        int choice = std::stoi(input);

        if(choice < 0 || choice >= count)
        {
            fmt::print("Invalid input\n");
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
    
    void Driver::ClearAssetList()
    {
    }

    void Driver::ShowAssetDetails()
    {
    }

    void Driver::QuitAssetControl()
    {
        if(this->IsRunningAC)
            this->IsRunningAC = false;
    }
}