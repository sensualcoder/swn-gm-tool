#ifndef ASSET_CREATOR_HPP
#define ASSET_CREATOR_HPP

#include <iostream>
#include <map>
#include <string>

#include "AssetModel.hpp"

namespace Tools
{
    class AssetCreator
    {
        public:
            void Add(const SwnGmTool::AssetModel&);
            void Remove(int);
            void Clear();

            void Load(std::istream);
            void Save(std::ostream, std::string);

        private:
            std::vector<SwnGmTool::AssetModel> AssetList;
    };
}

#endif
