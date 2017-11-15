#ifndef DATA_ACCESS_HPP
#define DATA_ACCESS_HPP

#include <iostream>
#include <string>

namespace SwnGmTool
{
    template <class T>
    class DataAccess
    {
        public:
            DataAccess() {}

            virtual void Save(std::ostream&, T&, std::string) = 0;
            virtual void Load(std::istream&, T&) = 0;
    };
}

#endif
