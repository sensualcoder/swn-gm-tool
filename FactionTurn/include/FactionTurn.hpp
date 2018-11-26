#ifndef FACTION_TURN_HPP
#define FACTION_TURN_HPP

#include <map>
#include <memory>
#include <string>
#include <vector>

#include <cereal/cereal.hpp>
#include <cereal/types/vector.hpp>

#include "Actions.hpp"
#include "Faction.hpp"
#include "Observer.hpp"

namespace FT
{
    // Enums, structs, const values and objects

    /** FactionTurnState
     *  Stores the state of each faction turn
     */
    struct FactionTurnState
    {
        std::vector<Faction> Factions;
        std::vector<Action> ResolvedActions;
    };

    // Class definition
    /** FactionTurn
     */
    class FactionTurn : public Observer
    {
        public:
            FactionTurn(const FactionTurn &) = delete;
            FactionTurn(FactionTurn &&) = delete;

            FactionTurn(size_t turnNumber = 0);
            ~FactionTurn();

            void Setup();
            void StartTurn();
            void EndTurn();

            // Inherited from Observer
            void OnNotify(const Event&) override;

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
