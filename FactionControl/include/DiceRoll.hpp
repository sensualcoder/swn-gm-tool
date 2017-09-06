#ifndef DICE_ROLL_HPP
#define DICE_ROLL_HPP

#include <cstdint>
#include <ctime>
#include <string>

namespace SwnGmTool
{
    struct DiceRoll
    {
        uint8_t DiceNum;
        uint8_t DiceType;
        uint8_t Modifier;
    };

    void setup_randomizer()
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

    template<class Archive>
    void serialize(Archive& archive, DiceRoll& d)
    {
        archive(cereal::make_nvp("DiceNum", d.DiceNum),
                cereal::make_nvp("DiceType", d.DiceType),
                cereal::make_nvp("Modfifier", d.Modifier) );
    }
}

#endif
