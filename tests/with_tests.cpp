#include "catch.hpp"

#include "with.hpp"
#include "equals_matcher.hpp"
#include "equals_with_epsilon_matcher.hpp"
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

template <template <typename> class Matcher, typename T>
struct SingleValueDeducedMatcher
{
    SingleValueDeducedMatcher(const T& v)
        : m_value(v)
    {}
    SingleValueDeducedMatcher()
        : m_value()
    {}
    T m_value;
};

template <template <typename, typename> class Matcher, typename T1, typename T2>
struct MultipleValueDeducedMatcher
{
    MultipleValueDeducedMatcher(const T1& v1, const T2& v2)
        : m_v1(v1), m_v2(v2)
    {}
    T1 m_v1;
    T2 m_v2;
};

struct Params
{
    template<typename Convert, typename T>
    void addDeducedParameter(std::vector<goospimpl::MatcherHolder2>& params, const T& v)
    {
        params.push_back(goospimpl::MatcherHolder2::create<goospimpl::EqualsMatcher2, Convert>(v));
    }
    template<typename Convert, template <typename> class Matcher, typename U>
    void addDeducedParameter(std::vector<goospimpl::MatcherHolder2>& params, const SingleValueDeducedMatcher<Matcher, U>& v)
    {
        params.push_back(goospimpl::MatcherHolder2::create<Matcher, Convert>(v.m_value));
    }
    template<typename Convert, template <typename, typename> class Matcher, typename T1, typename T2>
    void addDeducedParameter(std::vector<goospimpl::MatcherHolder2>& params, const MultipleValueDeducedMatcher<Matcher, T1, T2>& v)
    {
        params.push_back(goospimpl::MatcherHolder2::create<Matcher, Convert, Convert>(v.m_v1, v.m_v2));
    }
};

template <typename U, typename EpsilonType>
MultipleValueDeducedMatcher<goospimpl::EqualsWithEpsilonMatcher2,U,EpsilonType> equal(const U& v, const EpsilonType& e)
{
    return MultipleValueDeducedMatcher<goospimpl::EqualsWithEpsilonMatcher2, U,EpsilonType>(v, e);
}

template <typename U>
SingleValueDeducedMatcher<goospimpl::EqualsMatcher2,U> equal(const U& v)
{
    return SingleValueDeducedMatcher<goospimpl::EqualsMatcher2, U>(v);
}

template <typename T1, typename T2>
MultipleValueDeducedMatcher<goospimpl::BetweenMatcher2,T1,T2> between(const T1& lower, const T2& upper)
{
    return MultipleValueDeducedMatcher<goospimpl::BetweenMatcher2,T1,T2>(lower, upper);
}

template <typename DeducedMatcher>
DeducedMatcher with(const DeducedMatcher& m)
{
    return m;
}

TEST_CASE("With/1","")
{
    using goospimpl::MatcherHolder2;
    using goospimpl::ValueHolder;
    std::vector<goospimpl::MatcherHolder2> paramsVector;

    Params p;
    p.addDeducedParameter<double>(paramsVector, 3);
    REQUIRE(paramsVector.size() == 1);
    ValueHolder dvalue(3.0);
    ValueHolder ivalue(3);
    REQUIRE(paramsVector[0].matches(dvalue));
    REQUIRE(!paramsVector[0].matches(ivalue));
    paramsVector.clear();

    p.addDeducedParameter<int>(paramsVector, 3);
    REQUIRE(!paramsVector[0].matches(dvalue));
    REQUIRE(paramsVector[0].matches(ivalue));
    paramsVector.clear();

    p.addDeducedParameter<double>(paramsVector, with(equal(3)));
    REQUIRE(paramsVector[0].matches(dvalue));
    REQUIRE(!paramsVector[0].matches(ivalue));
    paramsVector.clear();

    p.addDeducedParameter<double>(paramsVector, with(equal(2,1.1)));
    REQUIRE(paramsVector[0].matches(dvalue));
    REQUIRE(!paramsVector[0].matches(ivalue));
    paramsVector.clear();

    p.addDeducedParameter<int>(paramsVector, with(equal(2,1)));
    REQUIRE(!paramsVector[0].matches(dvalue));
    REQUIRE(paramsVector[0].matches(ivalue));
    paramsVector.clear();

    p.addDeducedParameter<int>(paramsVector, with(equal(2,0)));

    REQUIRE(!paramsVector[0].matches(dvalue));
    REQUIRE(!paramsVector[0].matches(ivalue));
    using goospimpl::Description;
    Description d;
    paramsVector[0].describe_to(d);
    REQUIRE(printToString(d) == "value \"2\"");
    Description mismatch;
    paramsVector[0].describe_mismatch(ivalue, mismatch);
    REQUIRE(printToString(mismatch) == "was \"3\" (+-\"0\")");
    Description dmismatch;
    paramsVector[0].describe_mismatch(dvalue, dmismatch);
    REQUIRE(printToString(dmismatch) == std::string("was of incompatible type '") + typeid(double).name() + "'");
    paramsVector.clear();

    p.addDeducedParameter<double>(paramsVector, with(between(2.9,3.1)));
    REQUIRE(paramsVector[0].matches(dvalue));
    REQUIRE(!paramsVector[0].matches(ivalue));
    paramsVector.clear();

    p.addDeducedParameter<double>(paramsVector, between(2,3));
    REQUIRE(paramsVector[0].matches(dvalue));
    REQUIRE(!paramsVector[0].matches(ivalue));
    paramsVector.clear();
}
