#include "catch.hpp"

#include "any_value_of_type_matcher.hpp"

TEST_CASE("AnyValueOfType/1","check double type")
{
    using goospimpl::AnyValueOfTypeMatcher;

    AnyValueOfTypeMatcher<double> m;
    double value(36.0);
    REQUIRE(m.matches(value));
    int v2(36);
    REQUIRE(!m.matches(v2));
}

TEST_CASE("AnyValueOfType/2","check pointer type")
{
    using goospimpl::AnyValueOfTypeMatcher;

    AnyValueOfTypeMatcher<const int*> m;
    int v(0);
    const int* p = &v;
    REQUIRE(m.matches(p));
    double v2(36.0);
    const double* pd = &v2;
    REQUIRE(!m.matches(pd));
}

