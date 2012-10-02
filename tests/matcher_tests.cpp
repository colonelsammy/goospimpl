#include "catch.hpp"

#include "matcher.hpp"
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

TEST_CASE("CloneableMatcher/1","")
{
    using goospimpl::EqualsMatcher2;
    using goospimpl::CloneableMatcher;
    using goospimpl::SingleValueMatcherType;
    using goospimpl::ValueHolder;

    std::auto_ptr<CloneableMatcher> matcher(SingleValueMatcherType<int, EqualsMatcher2 >::create(0));
    ValueHolder value(0);
    REQUIRE(matcher->matches(value));
}

TEST_CASE("CloneableMatcher/2","")
{
    using goospimpl::EqualsMatcher2;
    using goospimpl::CloneableMatcher;
    using goospimpl::SingleValueMatcherType;
    using goospimpl::ValueHolder;

    std::auto_ptr<CloneableMatcher> matcher(SingleValueMatcherType<double, EqualsMatcher2 >::create(1.234));
    ValueHolder value(3.142);
    REQUIRE(!matcher->matches(value));

    using goospimpl::Description;
    std::auto_ptr<const CloneableMatcher> matcher2(matcher->clone());
    Description d;
    matcher2->describe_to(d);
    REQUIRE(printToString(d) == "value \"1.234\"");
    Description mismatch;
    matcher2->describe_mismatch(value, mismatch);
    REQUIRE(printToString(mismatch) == "was \"3.142\"");
}

TEST_CASE("MatcherHolder/1","")
{
    using goospimpl::EqualsMatcher2;
    using goospimpl::MatcherHolder2;
    using goospimpl::ValueHolder;

    MatcherHolder2 matcher = MatcherHolder2::create<EqualsMatcher2, int>(0);
    ValueHolder value(0);
    REQUIRE(matcher.matches(value));
}

TEST_CASE("MatcherHolder/2","")
{
    using goospimpl::EqualsMatcher2;
    using goospimpl::MatcherHolder2;
    using goospimpl::ValueHolder;

    MatcherHolder2 matcher = MatcherHolder2::create<EqualsMatcher2, double>(1.234);
    ValueHolder value(3.142);
    REQUIRE(!matcher.matches(value));

    using goospimpl::Description;
    MatcherHolder2 matcher2(matcher);
    Description d;
    matcher2.describe_to(d);
    REQUIRE(printToString(d) == "value \"1.234\"");
    Description mismatch;
    matcher2.describe_mismatch(value, mismatch);
    REQUIRE(printToString(mismatch) == "was \"3.142\"");
}

