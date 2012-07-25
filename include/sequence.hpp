//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_SEQUENCE_HPP
#define GOOS_PIMPL_SEQUENCE_HPP

#include "state_machine.hpp"
#include <cassert>

namespace goospimpl
{
    class Sequence
    {
    public:
        explicit Sequence(const StateMachineHolder& s)
            : seq(s)
        {}
        std::string expectedValue() const
        {
            return seq.expected_state();
        }
        void next()
        {
            std::string current = seq.expected_state();
            int expected_order(0);
            std::istringstream iss(current);
            iss >> expected_order;
            expected_order++;
            std::ostringstream oss;
            oss << expected_order;
            seq.change_expected_state(oss.str());
        }
        StateMachineHolder seq;
    };

    class inSequence
    {
    public:
        explicit inSequence(Sequence& s)
            : value(s)
        {
        }
        Sequence& value;
    private:
        inSequence(const inSequence&);
        inSequence& operator=(inSequence);
    };
}

#endif
