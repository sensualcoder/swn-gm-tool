#ifndef DICE_ROLL_HPP
#define DICE_ROLL_HPP

#include "DiceRollModel.hpp"

namespace SwnGmTool
{
    void setup_basic_randomizer();
    int roll_dice(const DiceRollModel&);
    bool is_none(const DiceRollModel&);
    std::string to_string(const DiceRollModel&);
}

#endif
