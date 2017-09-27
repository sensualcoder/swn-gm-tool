#include "FactionManager.hpp"

#include <fstream>
#include <iomanip>

#include <cereal/archives/json.hpp>

#include "SGTMenuOptions.hpp"

namespace SwnGmTool
{
    FactionManager::FactionManager()
    {
        this->FMFactionControl = FactionControl();
    }

    void FactionManager::ManageFactions()
    {
        this->IsRunning = true;

        while(this->IsRunning)
        {
            this->PrintFactionManagerMenu();
            this->SelectFactionManagerMenuOption();
        }
    }
    
    void FactionManager::PrintFactionManagerMenu(std::ostream& out)
    {
        this->PrintMenu(FactionManagerOptions, out);
    }

    void FactionManager::SelectFactionManagerMenuOption()
    {
        std::string input;
        std::getline(std::cin, input);

        switch(input[0])
        {
            case '1':
            {
                this->ShowFactionList();
                break;
            }
            case '2':
            {
                this->CreateFaction();
                break;
            }
            case '3':
            {
                this->RemoveFaction();
                break;
            }
            case '4':
            {
                this->ClearFactionList();
                break;
            }
            case 'S':
            {
                std::ofstream os("save.sgt");
                this->Save(os);
                break;
            }
            case 'L':
            {
                std::ifstream is("save.sgt");
                this->Load(is);
                break;
            }
            case 'Q':
            case 'q':
            default:
            {
                this->IsRunning = false;
                break;
            }
        }
    }

    void FactionManager::ShowFactionList(std::ostream& out)
    {
        out << "\nFaction list:\n";

        if(this->FMFactionControl.GetMapSize() == 0)
        {
            out << "Empty\n";
            return;
        }

        out << "ID" << std::setw(20) << "Name\n";

        auto list = this->FMFactionControl.GetFactionList();
        int index = 0;
        for(auto it: list)
        {
            out << index << std::setw(20) << it.Name << std::endl;
            index++;
        }
    }

    void FactionManager::CreateFaction()
    {
        std::cout << "\nEnter a name for the faction:\n";
        std::string name;
        std::getline(std::cin, name);
        this->FMFactionControl.AddFaction(name);
    }

    void FactionManager::RemoveFaction()
    {
        std::cout << "\nEnter the ID of the faction to remove:\n";
        std::string index;
        std::getline(std::cin, index);

        int i = std::stoi(index);
        if(i < 0 || i > this->FMFactionControl.GetMapSize() )
            return;

        this->FMFactionControl.RemoveFaction(i);
    }

    void FactionManager::ClearFactionList()
    {
        this->FMFactionControl.ClearMap();
    }

    void FactionManager::Save(std::ostream& out)
    {
        cereal::JSONOutputArchive archive(out);

        try
        {
            archive(this->FMFactionControl);
        }
        catch(std::exception ex)
        {
        }
    }

    void FactionManager::Load(std::istream& in)
    {
        cereal::JSONInputArchive archive(in);
        
        try
        {
            archive(this->FMFactionControl);
        }
        catch(std::exception ex)
        {
        }
    }

    void FactionManager::PrintMenu(const std::map<char, std::string>& options, std::ostream& out)
    {
        out << "\nChoose an option\n";
        
        for(auto i : options)
        {
            out << i.first << ") " << i.second << std::endl;
        }
    }
}