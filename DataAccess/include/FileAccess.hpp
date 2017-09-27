#ifndef FILE_ACCESS_HPP
#define FILE_ACCESS_HPP

#include "DataAccess.hpp"

#include <iostream>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

namespace SwnGmTool
{
    template<class T>
    class FileAccess : public DataAccess<T>
    {
        public:
            FileAccess() {}

            void Save(std::ostream& out, T& toSave) override
            {
                cereal::JSONOutputArchive archive(out);
                
                archive(toSave);
            }

            void Load(std::istream& in, T& toLoad) override
            {
                cereal::JSONInputArchive archive(in);
                
                archive(toLoad);
            }
    };
}

#endif
