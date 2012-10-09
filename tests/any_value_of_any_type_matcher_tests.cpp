#include "catch.hpp"

#include "any_value_of_any_type_matcher.hpp"

TEST_CASE("AnyValueOfAnyType/1","check double type")
{
    using goospimpl::AnyValueOfAnyTypeMatcher;

    AnyValueOfAnyTypeMatcher<void*> m;   // matcher should always have type 'void'
    double value(36.0);
    REQUIRE(m.matches(value));
    int v2(36);
    REQUIRE(m.matches(v2));
    int v(0);
    const int* p = &v;
    REQUIRE(m.matches(p));
    double vDouble(36.0);
    const double* pd = &vDouble;
    REQUIRE(m.matches(pd));
    void * pv = 0;
    REQUIRE(m.matches(pv));
}

