#include "catch.hpp"

#include "equals_matcher.hpp"

namespace
{
    std::string printToString(const goospimpl::Description& d)
    {
        std::ostringstream oss;
        d.print(oss);
        return oss.str();
    }
}

TEST_CASE("Equals/1","")
{
    using goospimpl::EqualsMatcher2;

    EqualsMatcher2<double> m;
    double value(0.0);
    REQUIRE(m.matches(value));
}

TEST_CASE("Equals/2","")
{
    using goospimpl::EqualsMatcher2;

    EqualsMatcher2<double> m(3.142);
    double value(3.142);
    REQUIRE(m.matches(value));
}

TEST_CASE("Equals/3","")
{
    using goospimpl::EqualsMatcher2;
    using goospimpl::Description;

    EqualsMatcher2<double> m;
    double value(3.142);
    REQUIRE(!m.matches(value));
    Description d;
    m.describe_to(d);
    REQUIRE(printToString(d) == "value \"0\"");
    Description mismatch;
    m.describe_mismatch(value, mismatch);
    REQUIRE(printToString(mismatch) == "was \"3.142\"");
}
