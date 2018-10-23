#ifndef FACTION_MODEL_HPP
#define FACTION_MODEL_HPP

#include <cstdint>
#include <string>

#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>

namespace SwnGmTool
{
    struct FactionModel
    {
        std::string Name;
        std::string Description;

        uint8_t Force, Cunning, Wealth;
        uint8_t Income, Treasury;
        uint8_t CurrentHp, MaxHp;
        uint8_t Experience;
    };

    inline bool operator==(const FactionModel& a, const FactionModel& b)
    {
        return a.Name == b.Name;
    }

    inline bool operator<(const FactionModel& a, const FactionModel& b)
    {
        return a.Name < b.Name;
    }

    template<class Archive>
    void serialize(Archive& archive, FactionModel& f)
    {
        archive(cereal::make_nvp("Name", f.Name), 
                cereal::make_nvp("Description", f.Description),
                cereal::make_nvp("Force", f.Force),
                cereal::make_nvp("Cunning", f.Cunning),
                cereal::make_nvp("Wealth", f.Wealth),
                cereal::make_nvp("Income", f.Income),
                cereal::make_nvp("Treasury", f.Treasury),
                cereal::make_nvp("CurrentHP", f.CurrentHp),
                cereal::make_nvp("MaxHP", f.MaxHp), 
                cereal::make_nvp("Experience", f.Experience) );
    }
}

template<>
struct std::equal_to<SwnGmTool::FactionModel>
{
    bool operator()(const SwnGmTool::FactionModel& a, const SwnGmTool::FactionModel& b) const
    {
        return a == b;
    };
};

#endif
