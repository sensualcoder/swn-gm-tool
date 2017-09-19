#include <iostream>

#include "SGTMain.hpp"

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

    void SGTMain::Run()
    {
        while(IsRunning)
        {
            this->PrintMainMenu();
            this->SelectMainMenuOption();
        }
        
        std::cout << "\nQuitting\n";
    }

    void SGTMain::PrintMainMenu()
    {
        std::cout << "\nChoose an option\n"
                  << "1) Create a new faction\n"
                  << "2) Manage factions\n"
                  << "Q) Quit\n";
    }

    void SGTMain::SelectMainMenuOption()
    {
        std::string input;
        std::getline(std::cin, input);

        switch(input[0])
        {
            case '1':
                this->CreateFaction();
                break;
            case '2':
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
        if(this->SGTFactionControl.GetMapSize() == 0)
        {
            std::cout << "\nNo factions to manage\n";
            return;
        }

        std::cout << "\nFaction List:\n";

        auto list = this->SGTFactionControl.GetFactionList();
        for(auto it: list)
        {
            std::cout << it.Name << std::endl;
        }

        this->PrintFactionManagerMenu();
        this->SelectFactionManagerMenuOption();
    }

    void SGTMain::PrintFactionManagerMenu()
    {
    }

    void SGTMain::SelectFactionManagerMenuOption()
    {
        std::string input;
        std::getline(std::cin, input);

        switch(input[0])
        {
            case 'Q':
            case 'q':
            default:
                break;
        }
    }
}