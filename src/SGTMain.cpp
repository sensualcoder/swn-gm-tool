#include "SGTMain.hpp"

#include "SGTMenuOptions.hpp"

namespace SwnGmTool
{
    void SGTMain::run(int argc, char* argv[])
    {
        std::cout << "SWN GM Tool\n";

        SGTMain main;

        main.Run();
    }

    SGTMain::SGTMain()
    {
        this->IsRunning = true;
        this->SGTFactionControl = FactionControl();
    }

    void SGTMain::PrintMenu(const std::map<char, std::string>& options, std::ostream& out)
    {
        out << "\nChoose an option\n";
        
        for(auto i : options)
        {
            out << i.first << ") " << i.second << std::endl;
        }
    }

    void SGTMain::Run()
    {
        while(this->IsRunning)
        {
            this->PrintMainMenu();
            this->SelectMainMenuOption();
        }
        
        std::cout << "\nQuitting\n";
    }

    void SGTMain::PrintMainMenu(std::ostream& out)
    {
        this->PrintMenu(MainMenuOptions, out);
    }

    void SGTMain::SelectMainMenuOption()
    {
        std::string input;
        std::getline(std::cin, input);

        switch(input[0])
        {
            case '1':
                this->IsFM = true;
                this->ManageFactions();
                break;
            case 'Q':
            case 'q':
                this->IsRunning = false;
                break;
            default:
                std::cout << "Select an option from the list\n";
                break;
        }
    }

    void SGTMain::CreateFaction()
    {
        std::cout << "\nEnter a name for the faction:\n";
        std::string name;
        std::getline(std::cin, name);
        this->SGTFactionControl.AddFaction(name);
    }

    void SGTMain::ManageFactions()
    {
        while(this->IsFM)
        {
            this->PrintFactionManagerMenu();
            this->SelectFactionManagerMenuOption();
        }
    }

    void SGTMain::ShowFactionList(std::ostream& out)
    {
        out << "\nFaction list:\n";

        if(this->SGTFactionControl.GetMapSize() == 0)
        {
            out << "Empty\n";
            return;
        }

        auto list = this->SGTFactionControl.GetFactionList();
        for(auto it: list)
        {
            out << it.Name << std::endl;
        }
    }

    void SGTMain::PrintFactionManagerMenu(std::ostream& out)
    {
        this->PrintMenu(FactionManagerOptions, out);
    }

    void SGTMain::SelectFactionManagerMenuOption()
    {
        std::string input;
        std::getline(std::cin, input);

        switch(input[0])
        {
            case '1':
                this->ShowFactionList();
                break;
            case '2':
                this->CreateFaction();
                break;
            case '3':
                //this->RemoveFaction();
                break;
            case '4':
                //this->ClearFactionList();
                break;
            case 'Q':
            case 'q':
            default:
                this->IsFM = false;
                break;
        }
    }
}