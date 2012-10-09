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

TEST_CASE("Equals/1","check empty double")
{
    using goospimpl::EqualsMatcher;

    EqualsMatcher<double> m;
    double value(0.0);
    REQUIRE(m.matches(value));
}

TEST_CASE("Equals/2","check double value")
{
    using goospimpl::EqualsMatcher;

    EqualsMatcher<double> m(3.142);
    double value(3.142);
    REQUIRE(m.matches(value));
}

TEST_CASE("Equals/3","check double mismatch messages")
{
    using goospimpl::EqualsMatcher;
    using goospimpl::Description;

    EqualsMatcher<double> m;
    double value(3.142);
    REQUIRE(!m.matches(value));
    Description d;
    m.describe_to(d);
    REQUIRE(printToString(d) == "value \"0\"");
    Description mismatch;
    m.describe_mismatch(value, mismatch);
    REQUIRE(printToString(mismatch) == "was \"3.142\"");
}

namespace UnitTest
{
    class TestEqualityObject
    {
    public:
        TestEqualityObject()
            : m_str("fred"), m_value(27)
        {}
        TestEqualityObject(const std::string& s, int v)
            : m_str(s), m_value(v)
        {}
        bool equals(const TestEqualityObject& rhs) const
        {
            return (m_str == rhs.m_str &&
                m_value == rhs.m_value);
        }
        // Requirements: must be copy constructable
        TestEqualityObject(const TestEqualityObject& rhs)
            : m_str(rhs.m_str), m_value(rhs.m_value)
        {
        }
        // Requirements: must be (output) streamable
        void print(std::ostream& os) const
        {
            os << m_str << ", " << m_value;
        }
#if __cplusplus >= 201103
        // Requirements: must be moveable
        TestEqualityObject(TestEqualityObject&& rhs)
            : m_str(std::move(rhs.m_str)), m_value(std::move(rhs.m_value))
        {
        }
#endif
    private:
        // not assignable
        TestEqualityObject& operator=(const TestEqualityObject& rhs);
#if __cplusplus >= 201103
        TestEqualityObject& operator=(TestEqualityObject&& rhs);
#endif

        std::string m_str;
        int m_value;
    };

        // Requirements: must be comparable for equals
    bool operator==(const TestEqualityObject& lhs, const TestEqualityObject& rhs)
    {
        return lhs.equals(rhs);
    }
    // Requirements: must be streamable
    std::ostream& operator<<(std::ostream& os, const TestEqualityObject& rhs)
    {
        rhs.print(os);
        return os;
    }
}

TEST_CASE("Equals/4", "check empty object equality")
{
    using goospimpl::EqualsMatcher;

    UnitTest::TestEqualityObject value;
    EqualsMatcher<UnitTest::TestEqualityObject> m;
    REQUIRE(m.matches(value));
}

TEST_CASE("Equals/5", "check object equality")
{
    using goospimpl::EqualsMatcher;

    UnitTest::TestEqualityObject value("Joe", 36);
    EqualsMatcher<UnitTest::TestEqualityObject> m(UnitTest::TestEqualityObject("Joe", 36));
    REQUIRE(m.matches(value));
}

TEST_CASE("Equals/6", "check object mismatch messages")
{
    using goospimpl::EqualsMatcher;
    using goospimpl::Description;

    UnitTest::TestEqualityObject value("Joe", 36);
    EqualsMatcher<UnitTest::TestEqualityObject> m(UnitTest::TestEqualityObject("Ben", 36));

    REQUIRE(!m.matches(value));
    Description d;
    m.describe_to(d);
    REQUIRE(printToString(d) == "value \"Ben, 36\"");
    Description mismatch;
    m.describe_mismatch(value, mismatch);
    REQUIRE(printToString(mismatch) == "was \"Joe, 36\"");
}

TEST_CASE("Equals/7", "check pointer equality")
{
    using goospimpl::EqualsMatcher;

    UnitTest::TestEqualityObject* value = new UnitTest::TestEqualityObject("Joe", 36);
    EqualsMatcher<UnitTest::TestEqualityObject*> m(value);
    REQUIRE(m.matches(value));
    EqualsMatcher<const UnitTest::TestEqualityObject*> m2(value);
    REQUIRE(m2.matches(value));
    EqualsMatcher<const UnitTest::TestEqualityObject* const> m3(value);
    REQUIRE(m.matches(value));
}

TEST_CASE("Equals/8", "check void pointer equality")
{
    using goospimpl::EqualsMatcher;

    int value(-1);
    void* p = static_cast<void*>(&value);
    EqualsMatcher<void*> m(p);
    REQUIRE(m.matches(&value));
    EqualsMatcher<const void*> m2(p);
    REQUIRE(m2.matches(&value));
    EqualsMatcher<const void* const> m3(p);
    REQUIRE(m.matches(&value));
    REQUIRE(!m.matches(NULL));
}

