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
}