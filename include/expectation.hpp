//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_EXPECTAION_HPP
#define GOOS_PIMPL_EXPECTAION_HPP

#include "counted_instance.hpp"
#include "state_machine.hpp"
#include "value_holder.hpp"
#include <vector>
#include <string>
#include <cassert>

namespace goospimpl
{
    class FunctionHolder;
    struct action;

    struct Expectation : CountedContent<CountedInstance>
    {
        virtual bool parameters_match(const std::string& name, const FunctionHolder& fn, const std::vector<ValueHolder>& r, ValueHolder& rv) = 0;
        virtual bool isSatisfied() const = 0;
        virtual bool isComplete() const = 0;
        virtual void add_return_value_action(action* a) = 0;
    };

    class ExpectationHolder : public CountedHolder<ExpectationHolder, Expectation>
    {
    public:
        ExpectationHolder()
        {}
        explicit ExpectationHolder(Expectation* e)
            : CountedHolder(e)
        {}
        ExpectationHolder(const ExpectationHolder& rhs)
            : CountedHolder(rhs), states(rhs.states)
        {}
        ExpectationHolder& operator=(ExpectationHolder rhs)
        {
            rhs.swap(*this);
            return *this;
        }
        void add_state_change(const StateMachineHolder& sm, const std::string& s, bool negate) {states.add_state_change(sm, s, negate);}
        void add_state_check(const StateMachineHolder& sm, const std::string& s, bool negate) {states.add_state_check(sm, s, negate);}
        bool parameters_match(const std::string& name, const FunctionHolder& fn, const std::vector<ValueHolder>& r, ValueHolder& rv)
        {
            assert(content);
            return (content->parameters_match(name, fn, r, rv) && states.process(name) );
        }
        bool isSatisfied() const
        {
            assert(content);
            return content->isSatisfied() && states.isSatisfied();
        }
        bool isComplete() const
        {
            assert(content);
            return content->isComplete();
        }
        void add_return_value_action(action* a)
        {
            assert(content);
            content->add_return_value_action(a);
        }
    private:
        void swap(ExpectationHolder& rhs)
        {
            std::swap(states, rhs.states);
            rhs.swapCountedHolder(*this);
        }

        StateChangeHolder states;
    };
}

#endif
