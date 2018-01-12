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

        std::ifstream is("conf.json");
        SwnGmTool::FileAccess<SwnGmTool::ConfigModel> access;

        try
        {
            access.Load(is, config);
        }
        catch(cereal::RapidJSONException ex)
        {
            // TODO: Log config load error

            config = SwnGmTool::ConfigModel();
        }

        this->SGTAPI = std::unique_ptr<SwnGmTool::SwnGmToolAPI>(new SwnGmTool::SwnGmToolAPI(config) );
        
        return true;
    }

    void Driver::Run()
    {
        if(this->Init() == false)
        {
            // TODO: Log init error
            
            return;
        }

        fmt::print("Stars Without Number GM Tool\n");
        fmt::print("SWN Version {0}\n", this->SGTAPI->GetConfig().Version);

        this->IsRunning = true;

        while(this->IsRunning)
        {
            this->PrintMainMenu();
            this->GetMainMenuInput();
        }

        fmt::print("\nQuitting...\n");
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

    void Driver::GetMainMenuInput(std::istream& in)
    {
        std::string input;
        std::getline(in, input);

        switch(input[0])
        {
            case '1':
            {
                this->RunFactionControl();
                break;
            }
            case 'Q':
            case 'q':
            {
                IsRunning = false;
                break;
            }
        }
    }

    void Driver::GetFactionControlInput(std::istream& in)
    {
        std::string input;
        std::getline(in, input);

        switch(input[0])
        {
            case '1':
            {
                this->ShowFactionList();
                break;
            }
            case '2':
            {
                this->AddFaction();
                break;
            }
            case '4':
            {
                this->ClearFactionlist();
                break;
            }
            case 'S':
            case 's':
            {
                std::ofstream os("save.sgt");
                this->Save(os);
                break;
            }
            case 'L':
            case 'l':
            {
                std::ifstream is("save.sgt");
                this->Load(is);
                break;
            }
            case 'Q':
            case 'q':
            {
                IsRunningFC = false;
                break;
            }
        }
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

    void Driver::AddFaction(std::istream& in)
    {
        fmt::print("\nAdd Faction\n");
        fmt::print("Enter a name\n");
        fmt::print("> ");

        std::string name;
        std::getline(in, name);

        SwnGmTool::FactionModel faction { name };

        this->SGTAPI->AddFaction(faction);
    }

    void Driver::ClearFactionlist()
    {
        this->SGTAPI->ClearMap();
    }

    void Driver::Save(std::ostream& out)
    {
        SwnGmTool::FileAccess<SwnGmTool::SwnGmToolAPI> access;

        access.Save(out, *this->SGTAPI, "Driver");
    }

    void Driver::Load(std::istream& in)
    {
        SwnGmTool::FileAccess<SwnGmTool::SwnGmToolAPI> access;

        access.Load(in, *this->SGTAPI);
    }
}