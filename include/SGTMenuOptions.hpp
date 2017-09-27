#ifndef SGT_MENU_OPTIONS_HPP
#define SGT_MENU_OPTIONS_HPP

#include <string>
#include <map>

namespace SwnGmTool
{
    const std::map<char, std::string> MainMenuOptions
    {
        { '1', "Manage Factions" },
        { 'Q', "Quit" }
    };

    const std::map<char, std::string> FactionManagerOptions
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
