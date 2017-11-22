#ifndef MENU_OPTIONS_HPP
#define MENU_OPTIONS_HPP

#include <string>
#include <vector>

namespace Driver
{
    struct MenuOption
    {
        char Option;
        std::string Label;
    };

    const std::vector<MenuOption> MainMenuOptions
    {
        { '1', "Manage Factions" },
        { '2', "Manage Sector" },
        { 'Q', "Quit" }
    };

    const std::vector<MenuOption> FactionManagerOptions
    {
        { '1', "Show Faction List" },
        { '2', "Create Faction" },
        { '3', "Remove Faction" },
        { '4', "Clear Faction List" },
        { 'S', "Save to file"},
        { 'L', "Load from file"},
        { 'Q', "Return to main menu" }
    };
}

#endif
