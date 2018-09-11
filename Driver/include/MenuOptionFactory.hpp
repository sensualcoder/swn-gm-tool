#ifndef MENU_OPTION_FACTORY_HPP
#define MENU_OPTION_FACTORY_HPP

#include <map>
#include <string>
#include <vector>

namespace Driver
{
    struct MenuOption
    {
        char Option;
        std::string Label;
    };

    template<typename T>
    struct MenuOptionMap
    {
        char Option;
        std::string Label;
        T OptionFunc;
    };

    template <typename T>
    struct MenuOptionFactory
    {
        static void ParseMenuOptionMap(const MenuOptionMap<T>&, std::vector<MenuOption>&, std::map<char, T>&);
        static void BuildMenuOptionMapFromList(const std::vector<MenuOptionMap<T> >&, std::vector<MenuOption>&, std::map<char, T>&);
    };

    template<typename T>
    void MenuOptionFactory<T>::ParseMenuOptionMap(const MenuOptionMap<T>& map, std::vector<MenuOption>& options, std::map<char, T>& functions)
    {
        options.push_back( MenuOption { map.Option, map.Label } );
        functions[map.Option] = map.OptionFunc;
    }

    template<typename T>
    void MenuOptionFactory<T>::BuildMenuOptionMapFromList(const std::vector<MenuOptionMap<T> >& list, std::vector<MenuOption>& options, std::map<char, T>& functions)
    {
        for(auto i : list)
        {
            ParseMenuOptionMap(i, options, functions);
        }
    }
}

#endif