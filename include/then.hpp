//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_THEN_HPP
#define GOOS_PIMPL_THEN_HPP

#include "states.hpp"

namespace goospimpl
{
    class then
    {
    public:
        explicit then(States& s)
            : seq(s.seq), value(s.state), negate(s.negate)
        {}
        StateMachineHolder seq;
        std::string value;
        bool negate;
    };
}

#endif
