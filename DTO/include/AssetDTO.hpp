#ifndef ASSET_DTO_HPP
#define ASSET_DTO_HPP

#include <cstdint>
#include <iostream>
#include <string>

#include <cereal/cereal.hpp>

#include "DiceRoll.hpp"

namespace SwnGmTool
{
    const std::string RatingType[] =
    {
        "Force",
        "Cunning",
        "Wealth"
    };

    const std::string AssetTypes[] =
    {
        "Military Unit",
        "Special Forces",
        "Special",
        "Facility",
        "Tactic",
        "Starship",
        "Logistics Facility"
    };

    struct AssetDTO
    {
        std::string Name;

        std::string RatingType;
        uint8_t RatingLevel;
        std::string AssetType;

        DiceRoll Attack;
        std::string Defender;
        DiceRoll Counter;

        uint8_t TechLevel;
        uint8_t Cost;

        uint8_t CurrentHP;
        uint8_t MaxHP;
    };

    inline std::string to_string(const AssetDTO& a)
    {
        return (a.Name + " " + a.RatingType + " " + a.AssetType + " " + to_string(a) + " " + to_string(a.Counter) );
    }

    inline std::ostream& operator<<(std::ostream& os, const AssetDTO& a)
    {
        os << to_string(a);
        return os;
    }

    inline bool operator==(const AssetDTO& a, const AssetDTO& b)
    {
        return a.Name == b.Name;
    }

    template<class Archive>
    void serialize(Archive& archive, AssetDTO& a)
    {
        archive(cereal::make_nvp("Name", a.Name),
                cereal::make_nvp("RatingType", a.RatingType),
                cereal::make_nvp("RatingLevel", a.RatingLevel),
                cereal::make_nvp("AssetType", a.AssetType),
                cereal::make_nvp("Attack", a.Attack),
                cereal::make_nvp("Defender", a.Defender),
                cereal::make_nvp("Counter", a.Counter),
                cereal::make_nvp("TechLevel", a.TechLevel),
                cereal::make_nvp("Cost", a.Cost),
                cereal::make_nvp("CurrentHP", a.CurrentHP),
                cereal::make_nvp("MaxHP", a.MaxHP) );
    }
}

template<>
struct std::equal_to<SwnGmTool::AssetDTO>
{
    bool operator()(const SwnGmTool::AssetDTO& a, const SwnGmTool::AssetDTO& b) const
    {
        return a == b;
    };
};

#endif
