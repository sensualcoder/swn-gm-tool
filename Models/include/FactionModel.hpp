#ifndef FACTION_MODEL_HPP
#define FACTION_MODEL_HPP

#include <cstdint>
#include <string>
#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/string.hpp>
#include <cereal/types/vector.hpp>

namespace SwnGmTool
{
    struct FactionModel
    {
        std::string Name;
        std::string Description;

        uint8_t Force;
        uint8_t Cunning;
        uint8_t Wealth;

        uint8_t Income;
        uint8_t FacCreds;

        uint8_t CurrentHP;
        uint8_t MaxHP;

        uint8_t Exp;

        std::vector<std::string> Tags;
    };

    inline bool operator==(const FactionModel& a, const FactionModel& b)
    {
        return a.Name == b.Name;
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
                cereal::make_nvp("FacCreds", f.FacCreds),
                cereal::make_nvp("CurrentHP", f.CurrentHP),
                cereal::make_nvp("MaxHP", f.MaxHP), 
                cereal::make_nvp("Exp", f.Exp),
                cereal::make_nvp("Tags", f.Tags) );
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
