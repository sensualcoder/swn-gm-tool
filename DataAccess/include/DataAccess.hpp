#ifndef DATA_ACCESS_HPP
#define DATA_ACCESS_HPP

#include <iostream>

namespace SwnGmTool
{
    template <class T>
    class DataAccess
    {
        public:
            DataAccess() {}

            virtual void Save(std::ostream&, T&) = 0;
            virtual void Load(std::istream&, T&) = 0;
    };
}

#endif
