//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_MOCKERY_HPP
#define GOOS_PIMPL_MOCKERY_HPP

#include "expectations.hpp"
#include "mock_class.hpp"

namespace goospimpl
{
    class Mockery
    {
    public:
        Mockery()
        {}
        ~Mockery()
        {
            assertIsSatisfied();
        }
        template <typename C>
        C& mock()
        {
            MockHolder holder = createMockClass<C>(&expectations);
            mocks.push_back(holder);
            return holder.mockReference<C>();
        }
        Sequence sequence(const std::string& s)
        {
            std::vector<StateMachineHolder>::iterator existing = std::find(sequences.begin(), sequences.end(), s);
            if( existing == sequences.end() )
            {
                StateMachineHolder h(new StateMachine(s, "0"));
                sequences.push_back(h);
                return Sequence(sequences.back());
            }
            return Sequence(*existing);
        }
        States states(const std::string& s)
        {
            std::vector<StateMachineHolder>::iterator existing = std::find(state_machines.begin(), state_machines.end(), s);
            if( existing == state_machines.end() )
            {
                StateMachineHolder h(new StateMachine(s));
                state_machines.push_back(h);
                return States(state_machines.back());
            }
            return States(*existing);
        }
        void checking(const Expectations& e)
        {
            expectations.append(e);
        }
        void assertIsSatisfied()
        {
            REQUIRE(expectations.assertIsSatisfied());
        }
    private:
        Expectations expectations;
        std::vector<MockHolder> mocks;
        std::vector<StateMachineHolder> sequences;
        std::vector<StateMachineHolder> state_machines;
    };
}

#endif
