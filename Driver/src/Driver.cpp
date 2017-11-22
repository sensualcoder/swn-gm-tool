#include "Driver.hpp"

#include <fstream>

#include "FileAccess.hpp"

namespace Driver
{
    Driver::Driver()
    {
        _clogger = spdlog::stdout_color_st("Driver");
        _clogger->set_pattern("%v");

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
            //TODO: Log config load error

            config = SwnGmTool::ConfigModel();
        }

        this->SGTAPI = std::unique_ptr<SwnGmTool::SwnGmToolAPI>(SwnGmTool::SwnGmToolAPI::CreateAPI(config) );
        
        return true;
    }

    void Driver::Run()
    {
        if(this->Init() == false)
        {
            return;
        }

        _clogger->info("Stars Without Number GM Tool");
        _clogger->info("SWN Version {0}", this->SGTAPI->GetConfig().Version);

        this->IsRunning = true;

        while(this->IsRunning)
        {
            this->PrintMainMenu();
            this->GetMainMenuInput();
        }

        _clogger->info("\nQuitting...");
    }

    void Driver::PrintMenu(const std::vector<MenuOption>& options)
    {
        _clogger->info("\nChoose an option");
        
        for(auto i : options)
        {
            _clogger->info("{0}) {1}", i.Option, i.Label);
        }
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

        _clogger->info("\nFaction List:");

        if(list.size() <= 0)
        {
            _clogger->info("Empty");
            return;
        }

        _clogger->info("{0:<10} {1:20}", "Index", "Name");

        for(int i = 0; i < list.size(); i++)
        {
            _clogger->info("{0:<10} {1:20}", i, list[i].Name);
        }
    }

    void Driver::AddFaction(std::istream& in)
    {
        _clogger->info("\nAdd Faction");
        _clogger->info("Enter a name");

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