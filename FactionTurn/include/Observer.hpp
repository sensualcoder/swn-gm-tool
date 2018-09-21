#ifndef OBSERVER_HPP
#define OBSERVER_HPP

#include "Events.hpp"

namespace FT
{
    class Observer
    {
        public:
            virtual ~Observer() {}
            virtual void OnNotify(const Event &) = 0;
    };
}

#endif
