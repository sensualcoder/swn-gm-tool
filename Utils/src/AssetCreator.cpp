#include "AssetCreator.hpp"

#include <iterator>

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

#include "FileAccess.hpp"

namespace Tools
{
    void AssetCreator::Add(const SwnGmTool::AssetModel& asset)
    {
        this->AssetList.push_back(asset);
    }

    void AssetCreator::Remove(int index)
    {
        auto it = this->AssetList.begin();
        std::advance(it, index);

        this->AssetList.erase(it);
    }

    void AssetCreator::Clear()
    {
        this->AssetList.clear();
    }

    void AssetCreator::Load(std::istream in)
    {
        SwnGmTool::FileAccess<std::vector<SwnGmTool::AssetModel> > access;

        access.Load(in, this->AssetList);
    }

    void AssetCreator::Save(std::ostream out, std::string name)
    {
        SwnGmTool::FileAccess<std::vector<SwnGmTool::AssetModel> > access;

        access.Save(out, this->AssetList, name);
    }
}