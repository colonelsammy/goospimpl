//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_EXPECTED_FUNCTION_COUNT_EQUALS_HPP
#define GOOS_PIMPL_EXPECTED_FUNCTION_COUNT_EQUALS_HPP

#include "expectation.hpp"
#include "matcher.hpp"
#include "function_call.hpp"
#include "action.hpp"
#include "description.hpp"

#include <vector>
#include <string>
#include <cassert>

namespace goospimpl
{
    class ExpectedFunctionCountEquals : public Expectation
    {
    public:
        ExpectedFunctionCountEquals(const FunctionHolder& f, const std::vector<MatcherHolder>& p, size_t expected)
            :fn_holder(f), params(p), expectedCount(expected), call_count(0), act(NULL)
        {}
        ExpectedFunctionCountEquals(const ExpectedFunctionCountEquals& rhs)
            : fn_holder(rhs.fn_holder), params(rhs.params), expectedCount(rhs.expectedCount), call_count(rhs.call_count), act(rhs.act? rhs.act->clone() :NULL)
        {
        }
        virtual bool parametersMatch(const std::string& name, const FunctionHolder& fn, const std::vector<ValueHolder>& r, ValueHolder& rv)
        {
            bool match(false);
            if( fn_holder.compare(fn) )
            {
                bool ok(params.size() == r.size());
                if( ok )
                {
                    size_t count = 1;
                    std::vector<ValueHolder>::const_iterator ia = r.begin();
                    for( std::vector<MatcherHolder>::const_iterator ip = params.begin(); ip != params.end(); ++ip, ++ia )
                    {
                        ok = ip->matches(*ia);
                        if(!ok )
                        {
                            Description desc;
                            ip->describe_to(desc);
                            Description mismatch_desc;
                            ip->describe_mismatch(*ia, mismatch_desc);
                            std::ostringstream oss;
                            oss << "expected " << desc << " but " << mismatch_desc
                                << " : parameter " << count << " of function '" + name + "'";
                            GOOS_PIMPL_INTERNAL_FAIL_MSG(oss.str());
                            break;
                        }
                        ++count;
                    }
                    if( ok )
                    {
                        match = true;
                        call_count++;
                        if( act )
                        {
                            rv = act->invoke();
                        }
                        else
                        {
                            rv = fn_holder.defaultReturnValue();
                        }
                    }
                }
                else
                {
                    std::ostringstream oss;
                    oss << "function '" + name + "' expected " << params.size() << " parameters but had "
                        << r.size();
                    GOOS_PIMPL_INTERNAL_FAIL_MSG(oss.str());
                }
            }
            return match;
        }
        virtual bool isSatisfied() const
        {
            return (call_count == expectedCount);
        }
        virtual bool isComplete() const
        {
            return isSatisfied();
        }
        virtual void addReturnValueAction(Action* a)
        {
            assert(act == NULL);
            act = a;
        }
    private:
        FunctionHolder fn_holder;
        std::vector<MatcherHolder> params;
        size_t expectedCount;
        size_t call_count;
        Action* act;
    };
}

#endif
