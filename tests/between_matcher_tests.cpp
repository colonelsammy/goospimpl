#include "catch.hpp"

#include "between_matcher.hpp"

namespace
{
    std::string printToString(const goospimpl::Description& d)
    {
        std::ostringstream oss;
        d.print(oss);
        return oss.str();
    }
}

TEST_CASE("Between/1","check double mismatch messages")
{
    using goospimpl::BetweenMatcher;
    using goospimpl::Description;

    BetweenMatcher<double, double> m(2.142, 2.145);
    REQUIRE(!m.matches(2.141999));
    REQUIRE(m.matches(2.142));
    REQUIRE(m.matches(2.144));
    REQUIRE(m.matches(2.144999));
    REQUIRE(m.matches(2.145));
    const double value(2.1450001);
    REQUIRE(!m.matches(value));
    Description d;
    m.describe_to(d);
    REQUIRE(printToString(d) == "value between \"2.142\" and \"2.145\"");
    Description mismatch;
    m.describe_mismatch(value, mismatch);
    REQUIRE(printToString(mismatch) == "was \"2.145\"");
}

TEST_CASE("Between/2", "check pointer equality")
{
    using goospimpl::BetweenMatcher;

    int values[] = {1,2,3,4,5,6,7,8,9};
    BetweenMatcher<int*, int*> m(&values[1], &values[7]);
    REQUIRE(m.matches(&values[1]));
    REQUIRE(!m.matches(&values[0]));
    REQUIRE(m.matches(&values[7]));
    REQUIRE(!m.matches(&values[8]));
}

TEST_CASE("Between/3", "check const pointer equality")
{
    using goospimpl::BetweenMatcher;

    const int values[] = {1,2,3,4,5,6,7,8,9};
    BetweenMatcher<const int*, const int*> m(&values[1], &values[7]);
    REQUIRE(m.matches(&values[1]));
    REQUIRE(!m.matches(&values[0]));
    REQUIRE(m.matches(&values[7]));
    REQUIRE(!m.matches(&values[8]));
}

