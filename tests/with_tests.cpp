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

struct Params
{
    template<typename Convert, typename T>
    void addDeducedParameter(std::vector<goospimpl::MatcherHolder2>& params, const T& v)
    {
        params.push_back(goospimpl::MatcherHolder2::create<goospimpl::EqualsMatcher2, typename goospimpl::remove_reference<Convert>::type>(v));
    }
    template<typename Convert, template <typename> class Matcher, typename U>
    void addDeducedParameter(std::vector<goospimpl::MatcherHolder2>& params, const goospimpl::SingleValueDeducedMatcher<Matcher, U>& v)
    {
        params.push_back(goospimpl::MatcherHolder2::create<Matcher, typename goospimpl::remove_reference<Convert>::type>(v.m_value));
    }
    template<typename Convert, template <typename, typename> class Matcher, typename T1, typename T2>
    void addDeducedParameter(std::vector<goospimpl::MatcherHolder2>& params, const goospimpl::MultipleValueDeducedMatcher<Matcher, T1, T2>& v)
    {
        params.push_back(goospimpl::MatcherHolder2::create<Matcher, typename goospimpl::remove_reference<Convert>::type, typename goospimpl::remove_reference<Convert>::type>(v.m_v1, v.m_v2));
    }
};

template<>
void Params::addDeducedParameter<const char*, goospimpl::EqualsMatcher2, const char*>(std::vector<goospimpl::MatcherHolder2>& params, const goospimpl::SingleValueDeducedMatcher<goospimpl::EqualsMatcher2, const char*>& v)
{
    params.push_back(goospimpl::MatcherHolder2::create<goospimpl::EqualsMatcher2, std::string>(v.m_value));
}

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


TEST_CASE("With/1","")
{
    using goospimpl::MatcherHolder2;
    using goospimpl::ValueHolder;
    std::vector<goospimpl::MatcherHolder2> paramsVector;
    using goospimpl::with;
    using goospimpl::equal;
    using goospimpl::between;

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
    using goospimpl::equal;

    Params p;
    p.addDeducedParameter<const char*>(paramsVector, equal("The quick brown fox"));
    REQUIRE(paramsVector[0].matches(ValueHolder("The quick brown fox")));
}

TEST_CASE("arrays","")
{
    using goospimpl::between;
    using goospimpl::equal;
    int values[] = {0,1,2};
    equal(values);

    using goospimpl::MatcherHolder2;
    using goospimpl::ValueHolder;
    std::vector<goospimpl::MatcherHolder2> paramsVector;

    Params p;
    p.addDeducedParameter<int *>(paramsVector, equal(values));
    REQUIRE(paramsVector[0].matches(ValueHolder(values)));
    paramsVector.clear();

    p.addDeducedParameter<int*>(paramsVector, between(values, values + 2));
    REQUIRE(paramsVector[0].matches(ValueHolder(values + 1)));
}

namespace UnitTest
{
    class TestObject
    {
    public:
        TestObject()
            : m_str("fred"), m_value(27)
        {}
        bool matches(const TestObject& rhs) const
        {
            return (m_str == rhs.m_str &&
                m_value == rhs.m_value);
        }
        // Requirements: must be copy constructable
        TestObject(const TestObject& rhs)
            : m_str(rhs.m_str), m_value(rhs.m_value)
        {
        }
        // Requirements: must be (output) streamable
        void print(std::ostream& os) const
        {
            os << m_str << ", " << m_value;
        }
    private:
        // not assignable
        TestObject& operator=(const TestObject& rhs);

        std::string m_str;
        int m_value;
    };

    bool operator==(const TestObject& lhs, const TestObject& rhs)
    {
        return lhs.matches(rhs);
    }
    std::ostream& operator<<(std::ostream& os, const TestObject& rhs)
    {
        rhs.print(os);
        return os;
    }
}

TEST_CASE("objects","")
{
    UnitTest::TestObject t;
    using goospimpl::MatcherHolder2;
    using goospimpl::ValueHolder;
    using goospimpl::equal;

    std::vector<goospimpl::MatcherHolder2> paramsVector;

    Params p;
    p.addDeducedParameter<const UnitTest::TestObject&>(paramsVector, equal(t));
    REQUIRE(paramsVector[0].matches(ValueHolder(t)));
    paramsVector.clear();

    p.addDeducedParameter<const UnitTest::TestObject&>(paramsVector, with(equal(t)));
    REQUIRE(paramsVector[0].matches(ValueHolder(t)));
    paramsVector.clear();
}
