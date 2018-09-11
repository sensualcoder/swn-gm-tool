#ifndef ASSET_MODEL_HPP
#define ASSET_MODEL_HPP

#include <cstdint>
#include <iostream>
#include <string>

#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>

#include "DiceRoll.hpp"
#include "DiceRollModel.hpp"

namespace SwnGmTool
{
    struct AssetModel
    {
        std::string Name;

        std::string RatingType;
        uint8_t RatingLevel;
        std::string AssetType;

        DiceRollModel Attack;
        std::string DefenderType;
        DiceRollModel Counter;

        uint8_t TechLevel;
        uint8_t Cost;

        uint8_t CurrentHP;
        uint8_t MaxHP;
    };

    inline std::string to_string(const AssetModel& a)
    {
        return (a.Name);
    }

    inline std::ostream& operator<<(std::ostream& os, const AssetModel& a)
    {
        os << to_string(a);
        return os;
    }

    inline bool operator==(const AssetModel& a, const AssetModel& b)
    {
        return a.Name == b.Name;
    }

    inline bool operator<(const AssetModel& a, const AssetModel& b)
    {
        return a.Name < b.Name;
    }

    template<class Archive>
    void serialize(Archive& archive, AssetModel& a)
    {
        archive(cereal::make_nvp("Name", a.Name),
                cereal::make_nvp("RatingType", a.RatingType),
                cereal::make_nvp("RatingLevel", a.RatingLevel),
                cereal::make_nvp("AssetType", a.AssetType),
                cereal::make_nvp("Attack", a.Attack),
                cereal::make_nvp("DefenderType", a.DefenderType),
                cereal::make_nvp("Counter", a.Counter),
                cereal::make_nvp("TechLevel", a.TechLevel),
                cereal::make_nvp("Cost", a.Cost),
                cereal::make_nvp("CurrentHP", a.CurrentHP),
                cereal::make_nvp("MaxHP", a.MaxHP) );
    }
}

template<>
struct std::equal_to<SwnGmTool::AssetModel>
{
    bool operator()(const SwnGmTool::AssetModel& a, const SwnGmTool::AssetModel& b) const
    {
        return a == b;
    };
};

#endif
