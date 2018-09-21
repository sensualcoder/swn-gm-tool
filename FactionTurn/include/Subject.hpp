#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <vector>

#include "Events.hpp"
#include "Observer.hpp"

namespace FT
{
    class Subject
    {
        public:
            void AddObserver(Observer* observer);
            void RemoveObserver(Observer* observer);

        protected:
            void Notify(const Event& event);

        private:
            std::vector<Observer*> Observers;
    };
}

#endif
