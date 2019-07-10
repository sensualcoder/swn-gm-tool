#include "DiceRoll.hpp"

#include <ctime>
#include <string>

#include "Random.hpp"

namespace SwnGmTool
{
    int roll_dice(const DiceRollModel& dice)
    {
        int roll = 0;

        std::uniform_int_distribution<int> dist { 1, dice.DiceType };

        for(int i = 0; i < dice.DiceNum; i++)
        {
            int t = dist(prng() );
            roll += t;
        }

        roll += dice.Modifier;

        return roll;
    }

    bool is_none(const DiceRollModel& dice)
    {
        return (dice.DiceNum == 0);
    }

    std::string to_string(const DiceRollModel& dice)
    {
        if(is_none(dice) )
            return "None";
        return (std::to_string(dice.DiceNum) + "d" + std::to_string(dice.DiceType) + 
            ((dice.Modifier != 0) ? ((dice.Modifier > 0) ? "+" : "-") + std::to_string(dice.Modifier) : "") );
    }
}
