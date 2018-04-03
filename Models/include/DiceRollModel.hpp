#ifndef DICE_ROLL_MODEL_HPP
#define DICE_ROLL_MODEL_HPP

#include <cstdint>

#include <cereal/cereal.hpp>

namespace SwnGmTool
{
    struct DiceRollModel
    {
        uint8_t DiceNum;
        uint8_t DiceType;
        uint8_t Modifier;
    };

    template<class Archive>
    void serialize(Archive& archive, DiceRollModel& d)
    {
        archive(cereal::make_nvp("DiceNum", d.DiceNum),
                cereal::make_nvp("DiceType", d.DiceType),
                cereal::make_nvp("Modifier", d.Modifier) );
    }
}

#endif
