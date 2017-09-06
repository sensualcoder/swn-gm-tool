#ifndef FACTION_HPP
#define FACTION_HPP

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

    struct Faction
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

    template<class Archive>
    void serialize(Archive& archive, Faction& f)
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
struct std::hash<SwnGmTool::Faction>
{
    size_t operator()(const SwnGmTool::Faction& f) const
    {
        std::hash<std::string> string_hash;
        return string_hash(f.Name);
    }
};

template<>
struct std::equal_to<SwnGmTool::Faction>
{
    bool operator()(const SwnGmTool::Faction& a, const SwnGmTool::Faction& b) const
    {
        return a.Name == b.Name;
    };
};

#endif
