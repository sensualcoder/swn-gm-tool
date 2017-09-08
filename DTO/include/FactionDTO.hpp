#ifndef FACTION_DTO_HPP
#define FACTION_DTO_HPP

#include <cstdint>
#include <string>
#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

namespace SwnGmTool
{
    const std::string FactionTags[] =
    {
        "Colonists",
        "Deep Rooted",
        "Eugenics Cult",
        "Exchange Consulate",
        "Fanatical",
        "Imperialists",
        "Machiavellian",
        "Mercenary Group",
        "Perimeter Agency",
        "Pirates",
        "Plutocratic",
        "Perceptor Archive",
        "Psychic Academy",
        "Savage",
        "Scavengers",
        "Secretive",
        "Technical Expertise",
        "Theocratic",
        "Warlike"
    };

    struct FactionDTO
    {
        std::string Name;
        std::string Homeworld;

        uint8_t Force;
        uint8_t Cunning;
        uint8_t Wealth;

        uint8_t FacCreds;

        uint8_t CurrentHP;
        uint8_t MaxHP;

        uint8_t Exp;

        std::vector<std::string> Tags;
    };

    inline bool operator==(const FactionDTO& a, const FactionDTO& b)
    {
        return a.Name == b.Name;
    }

    template<class Archive>
    void serialize(Archive& archive, FactionDTO& f)
    {
        archive(cereal::make_nvp("Name", f.Name), 
                cereal::make_nvp("Homeworld", f.Homeworld),
                cereal::make_nvp("Force", f.Force),
                cereal::make_nvp("Cunning", f.Cunning),
                cereal::make_nvp("Wealth", f.Wealth),
                cereal::make_nvp("FacCreds", f.FacCreds),
                cereal::make_nvp("CurrentHP", f.CurrentHP),
                cereal::make_nvp("MaxHP", f.MaxHP), 
                cereal::make_nvp("Exp", f.Exp),
                cereal::make_nvp("Tags", f.Tags) );
    }
}

template<>
struct std::hash<SwnGmTool::FactionDTO>
{
    size_t operator()(const SwnGmTool::FactionDTO& f) const
    {
        std::hash<std::string> string_hash;
        return string_hash(f.Name);
    }
};

template<>
struct std::equal_to<SwnGmTool::FactionDTO>
{
    bool operator()(const SwnGmTool::FactionDTO& a, const SwnGmTool::FactionDTO& b) const
    {
        return a == b;
    };
};

#endif
