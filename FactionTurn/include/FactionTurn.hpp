#ifndef FACTION_TURN_HPP
#define FACTION_TURN_HPP

#include <string>
#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

#include "Faction.hpp"

namespace FT
{
    class Faction;

    struct Asset
    {
        std::string Name;
    };

    struct Action
    {
    };

    struct CombatAction : public Action
    {
    };

    /** FactionTurnState
     *  Stores the state of each faction turn
     */
    struct FactionTurnState
    {
        std::vector<Faction> FactionList;
        std::vector<Action> ResolvedActions;
    };

    class FactionTurn
    {
        public:
            FactionTurn(size_t = 0);
            FactionTurn(const FactionTurn &) = delete;
            FactionTurn(FactionTurn &&) = delete;

            template<class Archive>
            void serialize(Archive& archive)
            {
                archive(cereal::make_nvp("Current Turn Number", this->CurrentTurnNumber),
                        cereal::make_nvp("Current Turn State", this->CurrentTurnState),
                        cereal::make_nvp("Turn States", this->PreviousTurnStateList) );
            }

        private:
            size_t CurrentTurnNumber;
            FactionTurnState CurrentTurnState;
            std::vector<FactionTurnState> PreviousTurnStateList;
    };
}

#endif
