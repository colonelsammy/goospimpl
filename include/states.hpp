//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_STATES_HPP
#define GOOS_PIMPL_STATES_HPP

#include "state_machine.hpp"
#include <cassert>

namespace goospimpl
{
    class States
    {
    public:
        explicit States(const StateMachineHolder& s)
            : seq(s), negate(false)
        {}
        States& startsAs(const std::string& s)
        {
            seq.change_state(s);
            state = s;
            return *this;
        }
        States& is(const std::string& s)
        {
            negate = false;
            state = s;
            return *this;
        }
        States& isNot(const std::string& s)
        {
            negate = true;
            state = s;
            return *this;
        }
        StateMachineHolder seq;
        bool negate;
        std::string state;
    };
}

#endif
