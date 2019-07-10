#ifndef DICE_ROLL_HPP
#define DICE_ROLL_HPP

#include "DiceRollModel.hpp"

namespace SwnGmTool
{
    int roll_dice(const DiceRollModel& dice);
    bool is_none(const DiceRollModel& dice);
    std::string to_string(const DiceRollModel& dice);
}

#endif
