#include "catch.hpp"

#include "equals_with_epsilon_matcher.hpp"

namespace
{
    std::string printToString(const goospimpl::Description& d)
    {
        std::ostringstream oss;
        d.print(oss);
        return oss.str();
    }
}

TEST_CASE("EqualsEpsilon/1","check double mismatch messages")
{
    using goospimpl::EqualsWithEpsilonMatcher;
    using goospimpl::Description;

    EqualsWithEpsilonMatcher<double, int> m(2.1419999, 1);
    double value(3.142);
    REQUIRE(!m.matches(value));
    Description d;
    m.describe_to(d);
    REQUIRE(printToString(d) == "value \"2.142\"");
    Description mismatch;
    m.describe_mismatch(value, mismatch);
    REQUIRE(printToString(mismatch) == "was \"3.142\" (+-\"1\")");
}

TEST_CASE("EqualsEpsilon/2", "check pointer equality")
{
    using goospimpl::EqualsWithEpsilonMatcher;

    int values[] = {1,2,3,4,5,6,7,8,9};
    int* value = &values[4];    // middle value
    EqualsWithEpsilonMatcher<int*, ptrdiff_t> m(value, 3);
    REQUIRE(m.matches(&values[1]));
    REQUIRE(!m.matches(&values[0]));
    REQUIRE(m.matches(&values[7]));
    REQUIRE(!m.matches(&values[8]));
}

