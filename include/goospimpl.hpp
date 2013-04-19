//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_HPP
#define GOOS_PIMPL_HPP

//#define GOOS_PIMPL_INTERNAL_FAIL_MSG( msg ) INTERNAL_CATCH_MSG( msg, Catch::ResultWas::ExplicitFailure, false, "FAIL" )
#define GOOS_PIMPL_INTERNAL_FAIL_MSG( msg ) INTERNAL_CATCH_MSG( msg, Catch::ResultWas::Warning, Catch::ResultDisposition::ContinueOnFailure, "WARN" )

#include "mock_class.hpp"
#include "mockery.hpp"
#include "expectations.hpp"
#include "when.hpp"
#include "then.hpp"
#include "sequence.hpp"
#include "states.hpp"
#include "will.hpp"
#include "allowing.hpp"
#include "at_least.hpp"
#include "one_of.hpp"
#include "exactly.hpp"
#include "with.hpp"
#include "expectation.hpp"
#include "expected_function_count_equals.hpp"
#include "expected_function_count_at_least.hpp"
#include "state_machine.hpp"
#include "action.hpp"
#include "description.hpp"
#include "matcher.hpp"
#include "equals_matcher.hpp"
#include "equals_with_epsilon_matcher.hpp"
#include "between_matcher.hpp"
#include "any_value_of_type_matcher.hpp"
#include "any_value_of_any_type_matcher.hpp"
#include "catch_matcher_wrapper.hpp"
#include "function_call.hpp"

#endif
