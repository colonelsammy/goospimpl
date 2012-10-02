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
    template<>
    void addDeducedParameter<const char*>(std::vector<goospimpl::MatcherHolder2>& params, const SingleValueDeducedMatcher<goospimpl::EqualsMatcher2, const char*>& v)
    {
        params.push_back(goospimpl::MatcherHolder2::create<goospimpl::EqualsMatcher2, std::string>(v.m_value));
    }
    template<typename Convert, template <typename, typename> class Matcher, typename T1, typename T2>
    void addDeducedParameter(std::vector<goospimpl::MatcherHolder2>& params, const MultipleValueDeducedMatcher<Matcher, T1, T2>& v)
    {
        params.push_back(goospimpl::MatcherHolder2::create<Matcher, Convert, Convert>(v.m_v1, v.m_v2));
    }
};

struct A
{
    A(int v)
        : m_value(v)
    {}
    operator double() const {return m_value;}
    int m_value;
};

bool operator==(const A& lhs, const A& rhs)
{
    return lhs.m_value == rhs.m_value;
}

struct B
{
    B(int v)
        : m_value(v)
    {}
    operator int() const {return m_value;}
    int m_value;
};

bool operator==(const B& lhs, const B& rhs)
{
    return lhs.m_value == rhs.m_value;
}

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

#ifdef XXX
#if __cplusplus >= 201103
#define STATIC_ASSERT_PTR_NOT_SUPPORTED(b) static_assert(b,"Pointer types cannot be compared for equality - use pointer<> template to compare pointers")
#else

template <bool b>
struct pointer_equality_not_supported;

template <>
struct pointer_equality_not_supported<true>
{};

#define STATIC_ASSERT_PTR_NOT_SUPPORTED(b) pointer_equality_not_supported<b> ptr_not_supported;
#endif
#endif


template <typename U>
SingleValueDeducedMatcher<goospimpl::EqualsMatcher2,U*> equal(U* v)
{
    //STATIC_ASSERT_PTR_NOT_SUPPORTED(false);
    return SingleValueDeducedMatcher<goospimpl::EqualsMatcher2, U*>(v);
}

template <typename T1, typename T2>
MultipleValueDeducedMatcher<goospimpl::BetweenMatcher2,T1,T2> between(const T1& lower, const T2& upper)
{
    return MultipleValueDeducedMatcher<goospimpl::BetweenMatcher2,T1,T2>(lower, upper);
}

template <typename T1, typename T2>
MultipleValueDeducedMatcher<goospimpl::BetweenMatcher2,T1*,T2*> between(T1* lower, T2* upper)
{
    return MultipleValueDeducedMatcher<goospimpl::BetweenMatcher2,T1*,T2*>(lower, upper);
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

    A a(3);
    p.addDeducedParameter<double>(paramsVector, a);
    REQUIRE(paramsVector.size() == 1);
    REQUIRE(paramsVector[0].matches(dvalue));
    REQUIRE(!paramsVector[0].matches(ivalue));
    paramsVector.clear();

    B b(3);
    p.addDeducedParameter<double>(paramsVector, b);
    REQUIRE(paramsVector.size() == 1);
    REQUIRE(paramsVector[0].matches(dvalue));
    REQUIRE(!paramsVector[0].matches(ivalue));
    paramsVector.clear();

    p.addDeducedParameter<int>(paramsVector, b);
    REQUIRE(paramsVector.size() == 1);
    REQUIRE(!paramsVector[0].matches(dvalue));
    REQUIRE(paramsVector[0].matches(ivalue));
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

TEST_CASE("strings","")
{
    using goospimpl::MatcherHolder2;
    using goospimpl::ValueHolder;
    std::vector<goospimpl::MatcherHolder2> paramsVector;

    Params p;
    p.addDeducedParameter<const char*>(paramsVector, equal("The quick brown fox"));
    REQUIRE(paramsVector[0].matches(ValueHolder("The quick brown fox")));
}

TEST_CASE("arrays","")
{
    int values[] = {0,1,2};
    equal(values);

    using goospimpl::MatcherHolder2;
    using goospimpl::ValueHolder;
    std::vector<goospimpl::MatcherHolder2> paramsVector;

    Params p;
    p.addDeducedParameter<int * const>(paramsVector, equal(values));
    REQUIRE(paramsVector[0].matches(ValueHolder(values)));
    paramsVector.clear();

    p.addDeducedParameter<int* const>(paramsVector, between(values, values + 2));
    REQUIRE(paramsVector[0].matches(ValueHolder(values + 1)));
}

int findPositiveValues(int* v, int lower, int upper, int value)
{
    int count = 0;
    while( lower <= upper )
    {
        if( v[lower] == value )
        {
            ++count;
        }
        else if( v[lower] > value )
        {
            break;
        }
        ++lower;
    }
    return count;
}

int absDistinct(int* v, int sz, int value)
{
    int lower = 0;
    int upper = sz - 1;
    int count = findPositiveValues(v,lower, upper,(value < 0 ? -value : value));
    return count;
}

TEST_CASE("absDistinct","")
{
    int values[] = {-10,-5,0,4,5,9};
    int count = absDistinct(values, sizeof(values)/ sizeof(int), -5);
    count = absDistinct(values, sizeof(values)/ sizeof(int), 9);
    count = absDistinct(values, sizeof(values)/ sizeof(int), 10);
    count = absDistinct(values, sizeof(values)/ sizeof(int), 11);
    count = absDistinct(values, sizeof(values)/ sizeof(int), 3);
}

