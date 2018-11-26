#ifndef ASSET_HPP
#define ASSET_HPP

#include "AssetModel.hpp"

namespace FT
{
    using AssetModel = SwnGmTool::AssetModel;

    class Asset
    {
        public:
            Asset(const AssetModel& asset);

        private:
            AssetModel Model;
    };
}

#endif
