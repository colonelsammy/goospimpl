//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_STATE_MACHINE_HPP
#define GOOS_PIMPL_STATE_MACHINE_HPP

#include "counted_instance.hpp"
#include <sstream>
#include <string>
#include <vector>
#include <cassert>

namespace goospimpl
{
    struct StateMachine : CountedContent<CountedInstance>
    {
        StateMachine(const std::string& s)
            : m_state_name(s)
        {}
        StateMachine(const std::string& s, const std::string& initial_state)
            : m_state_name(s), m_current_state(initial_state), m_expected_state(initial_state)
        {}
        void change_state(const std::string& s) {m_current_state = s;}
        std::string state() const {return m_current_state;}
        void change_expected_state(const std::string& s) {m_expected_state = s;}
        std::string expected_state() const {return m_expected_state;}
        std::string name() const {return m_state_name;}
    private:
        std::string m_state_name;
        std::string m_current_state;
        std::string m_expected_state;
    };

    class StateMachineHolder : public CountedHolder<StateMachine>
    {
    public:
        StateMachineHolder()
        {}
        explicit StateMachineHolder(StateMachine* e)
            : CountedHolder(e)
        {}
        void change_state(const std::string& s)
        {
            assert(content);
            content->change_state(s);
        }
        std::string state() const
        {
            assert(content);
            return content->state();
        }
        void change_expected_state(const std::string& s)
        {
            assert(content);
            content->change_expected_state(s);
        }
        std::string expected_state() const
        {
            assert(content);
            return content->expected_state();
        }
        std::string name() const
        {
            assert(content);
            return content->name();
        }
    };

    struct StateChange
    {
        StateChange(const StateMachineHolder& sm, const std::string& s, bool n, bool c)
            : machine(sm), expected(s), negate(n), check(c), ok(false)
        {}
        bool isSatisfied() const
        {
            return ok;
        }
        bool process(const std::string& name)
        {
            if( check )
            {
                if( negate )
                {
                    ok = (expected != machine.state());
                }
                else
                {
                    ok = (expected == machine.state());
                }
                if( !ok )
                {
                    std::ostringstream oss;
                    oss << "In sequence '" << machine.name() << "', expected function '" << name << "' to be called at " << expected << " but "
                        << " was called at " << machine.state();
                    GOOS_PIMPL_INTERNAL_FAIL_MSG(oss.str());
                }
            }
            else
            {
                machine.change_state(expected);
                ok = true;
            }
            return ok;
        }
        StateMachineHolder machine;
        std::string expected;
        bool negate;
        bool check;
        bool ok;
    };

    class StateChangeHolder
    {
    public:
        StateChangeHolder()
        {}
        StateChangeHolder(const StateChangeHolder& rhs)
            : states(rhs.states)
        {}
        StateChangeHolder& operator=(StateChangeHolder rhs)
        {
            rhs.swap(*this);
            return *this;
        }
        void addStateChange(const StateMachineHolder& sm, const std::string& expected, bool negate)
        {
            states.push_back(StateChange(sm, expected, negate, false));
        }
        void addStateCheck(const StateMachineHolder& sm, const std::string& state, bool negate)
        {
            states.push_back(StateChange(sm, state, negate, true));
        }
        bool process(const std::string& name)
        {
            if( states.empty() ) return true;
            bool failed(false);
            for( std::vector<StateChange>::iterator iter = states.begin(); iter != states.end(); ++iter )
            {
                failed = !iter->process(name);
            }
            return !failed;
        }
        bool isSatisfied() const
        {
            bool failed(false);
            for( std::vector<StateChange>::const_iterator iter = states.begin(); iter != states.end(); ++iter )
            {
                failed |= !iter->isSatisfied();
            }
            return !failed;
        }
    private:
        void swap(StateChangeHolder& rhs)
        {
            std::swap(states, rhs.states);
        }

        std::vector<StateChange> states;
    };

    inline bool operator==(const StateMachineHolder& lhs, const std::string& rhs)
    {
        return lhs.name() == rhs;
    }
}

#endif
