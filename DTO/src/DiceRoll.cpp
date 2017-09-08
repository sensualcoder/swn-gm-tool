#include "DiceRoll.hpp"

namespace SwnGmTool
{
    void setup_basic_randomizer()
    {
        std::srand(std::time(0) );
    }

    int roll_dice(const DiceRoll& d)
    {
        int roll = 0;

        for(int i = 0; i < d.DiceNum; i++)
        {
            int t = 1 + std::rand() % d.DiceType;
            roll += t;
        }

        roll += d.Modifier;

        return roll;
    }

    bool is_none(const DiceRoll& d)
    {
        return (d.DiceNum == 0);
    }

    std::string to_string(const DiceRoll& d)
    {
        if(is_none(d) )
            return "None";
        return (std::to_string(d.DiceNum) + "d" + std::to_string(d.DiceType) + 
            ((d.Modifier != 0) ? ((d.Modifier > 0) ? "+" : "-") + std::to_string(d.Modifier) : "") );
    }
}
