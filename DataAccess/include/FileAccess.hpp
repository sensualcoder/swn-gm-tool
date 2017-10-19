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
                try
                {
                    cereal::JSONOutputArchive archive(out);
                    
                    archive(toSave);
                }
                catch(cereal::RapidJSONException ex)
                {
                    std::cout << "Error saving: " << ex.what() << std::endl;
                }
            }

            void Load(std::istream& in, T& toLoad) override
            {
                try
                {
                    cereal::JSONInputArchive archive(in);
                
                    archive(toLoad);
                }
                catch(cereal::RapidJSONException ex)
                {
                    std::cout << "Error loading: " << ex.what() << std::endl;
                }
            }
    };
}

#endif
