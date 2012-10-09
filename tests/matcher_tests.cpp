#include "catch.hpp"

#include "matcher.hpp"
#include "equals_matcher.hpp"
#include "equals_with_epsilon_matcher.hpp"
#include "any_value_of_type_matcher.hpp"
#include "any_value_of_any_type_matcher.hpp"
#include "catch_matcher_wrapper.hpp"

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
    using goospimpl::EqualsMatcher;
    using goospimpl::CloneableMatcher;
    using goospimpl::SingleValueMatcherType;
    using goospimpl::ValueHolder;

    std::auto_ptr<CloneableMatcher> matcher(SingleValueMatcherType<int, EqualsMatcher >::create(0));
    ValueHolder value(0);
    REQUIRE(matcher->matches(value));
}

TEST_CASE("CloneableMatcher/2","check matcher cloning")
{
    using goospimpl::EqualsMatcher;
    using goospimpl::CloneableMatcher;
    using goospimpl::SingleValueMatcherType;
    using goospimpl::ValueHolder;

    std::auto_ptr<CloneableMatcher> matcher(SingleValueMatcherType<double, EqualsMatcher >::create(1.234));
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

TEST_CASE("MatcherHolder/1","check single value int matcher creation")
{
    using goospimpl::EqualsMatcher;
    using goospimpl::MatcherHolder;
    using goospimpl::ValueHolder;

    MatcherHolder matcher = MatcherHolder::create<EqualsMatcher, int>(0);
    ValueHolder value(0);
    REQUIRE(matcher.matches(value));
}

TEST_CASE("MatcherHolder/2","check single value double matcher creation")
{
    using goospimpl::EqualsMatcher;
    using goospimpl::MatcherHolder;
    using goospimpl::ValueHolder;

    MatcherHolder matcher = MatcherHolder::create<EqualsMatcher, double>(1.234);
    ValueHolder value(3.142);
    REQUIRE(!matcher.matches(value));

    using goospimpl::Description;
    MatcherHolder matcher2(matcher);
    Description d;
    matcher2.describe_to(d);
    REQUIRE(printToString(d) == "value \"1.234\"");
    Description mismatch;
    matcher2.describe_mismatch(value, mismatch);
    REQUIRE(printToString(mismatch) == "was \"3.142\"");
}

TEST_CASE("MatcherHolder/3","check multi value int matcher creation")
{
    using goospimpl::EqualsWithEpsilonMatcher;
    using goospimpl::MatcherHolder;
    using goospimpl::ValueHolder;

    MatcherHolder matcher = MatcherHolder::create<EqualsWithEpsilonMatcher>(23, 1);
    ValueHolder value(21);
    REQUIRE(!matcher.matches(value));
    ValueHolder v2(22);
    REQUIRE(matcher.matches(v2));
    ValueHolder v3(23);
    REQUIRE(matcher.matches(v3));
    ValueHolder v4(24);
    REQUIRE(matcher.matches(v4));
    ValueHolder v5(25);
    REQUIRE(!matcher.matches(v5));
    ValueHolder vDouble(23.0);
    REQUIRE(!matcher.matches(vDouble));
}

TEST_CASE("MatcherHolder/4","check multi value double matcher creation")
{
    using goospimpl::EqualsWithEpsilonMatcher;
    using goospimpl::MatcherHolder;
    using goospimpl::ValueHolder;

    MatcherHolder matcher = MatcherHolder::create<EqualsWithEpsilonMatcher>(23.3, 1);
    ValueHolder value(23);
    REQUIRE(!matcher.matches(value));
    ValueHolder v2(23.0);
    REQUIRE(matcher.matches(v2));
    ValueHolder v3(22.2999);
    REQUIRE(!matcher.matches(v3));
    ValueHolder v4(22.3);
    REQUIRE(matcher.matches(v4));
    ValueHolder v5(24.29999);
    REQUIRE(matcher.matches(v5));
    ValueHolder v6(24.3);
    REQUIRE(matcher.matches(v6));
    ValueHolder v7(24.300001);
    REQUIRE(!matcher.matches(v7));
}

TEST_CASE("AnyValueOfTypeMatcher/1","")
{
    using goospimpl::AnyValueOfTypeMatcher;
    using goospimpl::MatcherHolder;
    using goospimpl::ValueHolder;

    MatcherHolder matcher = MatcherHolder::create<AnyValueOfTypeMatcher, double>();
    ValueHolder value(0.0);
    REQUIRE(matcher.matches(value));
    ValueHolder vInt(0);
    REQUIRE(!matcher.matches(vInt));
}

TEST_CASE("AnyValueOfAnyTypeMatcher/1","")
{
    using goospimpl::AnyValueOfAnyTypeMatcher;
    using goospimpl::MatcherHolder;
    using goospimpl::ValueHolder;

    MatcherHolder matcher = MatcherHolder::create<AnyValueOfAnyTypeMatcher, void*>();
    ValueHolder value(0.0);
    REQUIRE(matcher.matches(value));
    ValueHolder vInt(0);
    REQUIRE(matcher.matches(vInt));
}

TEST_CASE("CatchMatchers/1","")
{
    using goospimpl::ContainsMatcher;
    using goospimpl::MatcherHolder;
    using goospimpl::ValueHolder;

    MatcherHolder matcher = MatcherHolder::create<ContainsMatcher>(std::string("fox"));
    ValueHolder value("The quick brown fox jumped over the lazy dog");
    REQUIRE(matcher.matches(value));
    ValueHolder v2("The quick brown rat jumped over the lazy dog");
    REQUIRE(!matcher.matches(v2));
}

TEST_CASE("CatchMatchers/2","")
{
    using goospimpl::StartsWithMatcher;
    using goospimpl::MatcherHolder;
    using goospimpl::ValueHolder;

    MatcherHolder matcher = MatcherHolder::create<StartsWithMatcher>(std::string("The quick"));
    ValueHolder value("The quick brown fox jumped over the lazy dog");
    REQUIRE(matcher.matches(value));
    ValueHolder v2("The The quick brown rat jumped over the lazy dog");
    REQUIRE(!matcher.matches(v2));
}

TEST_CASE("CatchMatchers/3","")
{
    using goospimpl::EndsWithMatcher;
    using goospimpl::MatcherHolder;
    using goospimpl::ValueHolder;

    MatcherHolder matcher = MatcherHolder::create<EndsWithMatcher>(std::string("lazy dog"));
    ValueHolder value("The quick brown fox jumped over the lazy dog");
    REQUIRE(matcher.matches(value));
    ValueHolder v2("The quick brown fox jumped over the lazy cat");
    REQUIRE(!matcher.matches(v2));
}
