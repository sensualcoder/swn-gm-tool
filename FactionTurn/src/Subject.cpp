#include "Subject.hpp"

namespace FT
{
    void Subject::AddObserver(Observer* observer)
    {
        this->Observers.push_back(observer);
    }

    void Subject::RemoveObserver(Observer* observer)
    {
        for(auto i = this->Observers.begin(); i != this->Observers.end(); )
        {
            if(*i == observer)
            {
                this->Observers.erase(i);
            }
            else
            {
                ++i;
            }
        }
    }

    void Subject::Notify(const Event& event)
    {
        for(auto i: this->Observers)
        {
            i->OnNotify(event);
        }
    }
}