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
        this->FM = FactionManager();
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
                this->FM.ManageFactions();
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
}