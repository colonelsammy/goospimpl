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
    struct Action;

    struct Expectation : CountedContent<CountedInstance>
    {
        virtual bool parametersMatch(const std::string& name, const FunctionHolder& fn, const std::vector<ValueHolder>& r, ValueHolder& rv) = 0;
        virtual bool isSatisfied() const = 0;
        virtual bool isComplete() const = 0;
        virtual void addReturnValueAction(Action* a) = 0;
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
        void addStateChange(const StateMachineHolder& sm, const std::string& s, bool negate) {states.addStateChange(sm, s, negate);}
        void addStateCheck(const StateMachineHolder& sm, const std::string& s, bool negate) {states.addStateCheck(sm, s, negate);}
        bool parametersMatch(const std::string& name, const FunctionHolder& fn, const std::vector<ValueHolder>& r, ValueHolder& rv)
        {
            assert(content);
            return (content->parametersMatch(name, fn, r, rv) && states.process(name) );
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
        void addReturnValueAction(Action* a)
        {
            assert(content);
            content->addReturnValueAction(a);
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
