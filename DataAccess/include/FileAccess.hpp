#ifndef FILE_ACCESS_HPP
#define FILE_ACCESS_HPP

#include "DataAccess.hpp"

#include <iostream>
#include <string>

#include <cereal/cereal.hpp>
#include <cereal/archives/json.hpp>

#include <fmt/format.h>

namespace SwnGmTool
{
    template<class T>
    class FileAccess : public DataAccess<T>
    {
        public:
            FileAccess() {}

            void Save(std::ostream& out, T& toSave, std::string name) override
            {
                cereal::JSONOutputArchive archive(out);

                try
                {
                    archive(cereal::make_nvp(name, toSave) );
                }
                catch(cereal::RapidJSONException ex)
                {
                    //fmt::printf("Error saving: {0}\n", ex.what() );
                    throw(ex);
                }
            }

            void Load(std::istream& in, T& toLoad) override
            {
                cereal::JSONInputArchive archive(in);

                try
                {
                    archive(toLoad);
                }
                catch(cereal::RapidJSONException ex)
                {
                    //fmt::printf("Error loading: {0}\n", ex.what() );
                    throw(ex);
                }
            }
    };
}

#endif
