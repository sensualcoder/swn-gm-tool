#include "Driver.hpp"

#include <fstream>

#include "FileAccess.hpp"

namespace Driver
{
    Driver::Driver()
    {
        this->Main = SGTMain();
        this->IsRunning = false;
        this->IsRunningFC = false;
        this->IsRunningAC = false;
    }

    bool Driver::Init()
    {
        this->Main.CM = std::unique_ptr<SwnGmTool::ConfigManager>(new SwnGmTool::ConfigManager() );
        
        try
        {
            std::ifstream config = std::ifstream("conf.json");
            this->Main.CM->Load(config);

            this->Main.FC = std::unique_ptr<SwnGmTool::FactionControl>(new SwnGmTool::FactionControl(this->Main.CM->GetConfig() ) );
            this->Main.SG = std::unique_ptr<SwnGmTool::SectorGen>(new SwnGmTool::SectorGen() );
        }
        catch(...)
        {
            return false;
        }
        
        return true;
    }

    void Driver::Run(std::ostream& out)
    {
        if(this->Init() == false)
        {
            return;
        }

        out << "Stars Without Number GM Tool\n";
        out << fmt::format("SWN Version {0}\n", this->Main.CM->GetConfig().Version);

        this->IsRunning = true;

        while(this->IsRunning)
        {
            this->PrintMainMenu();
            this->GetMainMenuInput();
        }

        out << "\nQuitting...\n";
    }

    void Driver::PrintMenu(const std::vector<MenuOption>& options, std::ostream& out)
    {
        out << "\nChoose an option\n";
        
        for(auto i : options)
        {
            out << i.Option << ") " << i.Label << std::endl;
        }
    }

    void Driver::PrintMainMenu(std::ostream& out)
    {
        this->PrintMenu(MainMenuOptions, out);
    }

    void Driver::PrintFactionMenu(std::ostream& out)
    {
        this->PrintMenu(FactionManagerOptions, out);
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
            default:
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

    void Driver::ShowFactionList(std::ostream& out)
    {
        auto list = this->Main.FC->GetFactionList();

        out << "\nFaction List:\n";

        if(list.size() <= 0)
        {
            out << "Empty\n";
            return;
        }

        out << fmt::format("{0:<10} {1:20}\n", "Index", "Name");

        for(int i = 0; i < list.size(); i++)
        {
            out << fmt::format("{0:<10} {1:20}\n", i, list[i].Name);
        }
    }

    void Driver::AddFaction(std::ostream& out, std::istream& in)
    {
        out << "\nAdd Faction\n";
        out << "Enter a name\n";
        out << "Name: ";

        std::string name;
        std::getline(in, name);

        SwnGmTool::FactionModel faction { name };

        this->Main.FC->AddFaction(faction);
    }

    void Driver::ClearFactionlist()
    {
        this->Main.FC->ClearMap();
    }

    void Driver::Save(std::ostream& out)
    {
        SwnGmTool::FileAccess<SwnGmTool::FactionControl> access;

        access.Save(out, *this->Main.FC, "Driver");
    }

    void Driver::Load(std::istream& in)
    {
        SwnGmTool::FileAccess<SwnGmTool::FactionControl> access;

        access.Load(in, *this->Main.FC);
    }
}