//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_EXPECTATIONS_HPP
#define GOOS_PIMPL_EXPECTATIONS_HPP

#include "sequence.hpp"
#include "allowing.hpp"
#include "one_of.hpp"
#include "exactly.hpp"
#include "when.hpp"
#include "then.hpp"
#include "will.hpp"

namespace goospimpl
{
    class Expectations
    {
    public:
        Expectations()
        {}
        Expectations& operator,(const oneOf& rhs)
        {
            expectations.push_back(rhs.expectation);
            return *this;
        }
        Expectations& operator,(const exactly& rhs)
        {
            expectations.push_back(rhs.expectation);
            return *this;
        }
        Expectations& operator,(const allowing& rhs)
        {
            expectations.push_back(rhs.expectation);
            return *this;
        }
        Expectations& operator,(const inSequence& rhs)
        {
            if( !expectations.empty() )
            {
                expectations.back().add_state_check(rhs.value.seq, rhs.value.expectedValue(), false);
                rhs.value.next();
                expectations.back().add_state_change(rhs.value.seq, rhs.value.expectedValue(), false);
            }
            return *this;
        }
        Expectations& operator,(const then& rhs)
        {
            if( !expectations.empty() )
            {
                expectations.back().add_state_change(rhs.seq, rhs.value, rhs.negate);
            }
            return *this;
        }
        Expectations& operator,(const when& rhs)
        {
            if( !expectations.empty() )
            {
                expectations.back().add_state_check(rhs.seq, rhs.value, rhs.negate);
            }
            return *this;
        }
        Expectations& operator,(const will& rhs)
        {
            if( !expectations.empty() )
            {
                expectations.back().add_return_value_action(rhs.act);
            }
            return *this;
        }
        void append(const Expectations& e)
        {
            if( !e.expectations.empty() )
            {
                size_t currentSize = expectations.size();
                expectations.resize(currentSize + e.expectations.size());
                std::copy(e.expectations.begin(), e.expectations.end(), expectations.begin() + currentSize);
            }
        }
        void checkFunctionParameters(const std::string& name, const FunctionHolder& fn, const std::vector<ValueHolder>& parameters, ValueHolder& rv)
        {
            bool matched(false);
            for( std::vector<ExpectationHolder>::iterator iter = expectations.begin(); iter != expectations.end(); ++iter )
            {
                if( iter->isComplete() )
                    continue;
                matched = iter->parameters_match(name, fn, parameters, rv);
                if( matched )
                {
                    unmatched.push_back(name);
                    break;
                }
            }
            if( !matched )
            {
                std::ostringstream oss;
                oss << "Function '" << name << "(";
                for( std::vector<ValueHolder>::const_iterator iter = parameters.begin(); iter != parameters.end(); ++iter )
                {
                }
                oss << ")' was called but was not expected.";
                GOOS_PIMPL_INTERNAL_FAIL_MSG(oss.str());
            }
        }
        bool assertIsSatisfied() const
        {
            bool failed(false);
            for( std::vector<ExpectationHolder>::const_iterator iter = expectations.begin(); iter != expectations.end(); ++iter )
            {
                failed |= !iter->isSatisfied();
            }
            failed |= (unmatched.empty());
            return !failed;
        }
    private:
        std::vector<ExpectationHolder> expectations;
        std::vector<std::string> unmatched;
    };
}

#endif
