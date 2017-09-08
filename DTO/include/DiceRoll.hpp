#ifndef DICE_ROLL_HPP
#define DICE_ROLL_HPP

#include <cstdint>
#include <ctime>
#include <string>

#include <cereal/cereal.hpp>

namespace SwnGmTool
{
    struct DiceRoll
    {
        uint8_t DiceNum;
        uint8_t DiceType;
        uint8_t Modifier;
    };

    template<class Archive>
    void serialize(Archive& archive, DiceRoll& d)
    {
        archive(cereal::make_nvp("DiceNum", d.DiceNum),
                cereal::make_nvp("DiceType", d.DiceType),
                cereal::make_nvp("Modfifier", d.Modifier) );
    }

    void setup_basic_randomizer();
    int roll_dice(const DiceRoll&);
    bool is_none(const DiceRoll&);
    std::string to_string(const DiceRoll&);
}

#endif
