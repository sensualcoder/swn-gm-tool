#include "FactionTurn.hpp"

namespace FT
{
    FactionTurn::FactionTurn(size_t turnNumber) : CurrentTurnNumber(turnNumber)
    {
    }
    
    FactionTurn::~FactionTurn()
    {
    }

    void FactionTurn::OnNotify(const Event& event)
    {
    }

    void FactionTurn::Setup()
    {
    }

    void FactionTurn::StartTurn()
    {
    }

    void FactionTurn::EndTurn()
    {
        this->PreviousTurnStateList.push_back(this->CurrentTurnState);

        this->CurrentTurnState = FactionTurnState();

        ++CurrentTurnNumber;
    }
}
