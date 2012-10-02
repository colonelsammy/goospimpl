#include "catch.hpp"

#include "value_holder.hpp"

namespace
{
    struct TestCounted
    {
        TestCounted(int v)
            : m_value(v)
        {
            m_instanceCount++;
        }
        ~TestCounted()
        {
            m_instanceCount--;
        }
        TestCounted(const TestCounted& rhs)
            : m_value(rhs.m_value)
        {
            m_instanceCount++;
        }
        TestCounted& operator=(const TestCounted& rhs)
        {
            if( this != &rhs )
            {
                m_value = rhs.m_value;
                //m_instanceCount++;
            }
            return *this;
        }
        static int m_instanceCount;
        int m_value;
    };
    int TestCounted::m_instanceCount = 0;
}

TEST_CASE("ValueHolder/Copies underlying object","copy initialisation")
{
    using goospimpl::ValueHolder;

    ValueHolder* pv = new ValueHolder((TestCounted(1)));
    REQUIRE(TestCounted::m_instanceCount == 1);
    ValueHolder* pv2 = new ValueHolder(*pv);
    REQUIRE(TestCounted::m_instanceCount == 2);
    delete pv;
    REQUIRE(TestCounted::m_instanceCount == 1);
    delete pv2;
    REQUIRE(TestCounted::m_instanceCount == 0);
}

TEST_CASE("ValueHolder/Assignment copies underlying object","assignment")
{
    using goospimpl::ValueHolder;

    ValueHolder* pv = new ValueHolder((TestCounted(2)));
    ValueHolder* pv1 = new ValueHolder((TestCounted(1)));
    ValueHolder* pv2 = new ValueHolder();

    const TestCounted& v0 = pv->value<TestCounted>();
    REQUIRE(v0.m_value == 2);
    const TestCounted& v1 = pv1->value<TestCounted>();
    REQUIRE(v0.m_value == 2);
    REQUIRE_THROWS(pv2->value<TestCounted>());
    *pv2 = *pv1;
    REQUIRE(TestCounted::m_instanceCount == 3);
    REQUIRE(pv2->value<TestCounted>().m_value == 1);
    *pv2 = *pv;
    REQUIRE(TestCounted::m_instanceCount == 3);
    REQUIRE(pv2->value<TestCounted>().m_value == 2);
    delete pv;
    REQUIRE(TestCounted::m_instanceCount == 2);
    delete pv2;
    REQUIRE(TestCounted::m_instanceCount == 1);
    delete pv1;
    REQUIRE(TestCounted::m_instanceCount == 0);
}

TEST_CASE("ValueHolder/Assignment of different types","assignment")
{
    using goospimpl::ValueHolder;

    ValueHolder* pv = new ValueHolder((TestCounted(2)));
    ValueHolder* pv1 = new ValueHolder(1);
    ValueHolder* pv2 = new ValueHolder();

    *pv2 = *pv1;
    REQUIRE(TestCounted::m_instanceCount == 1);
    REQUIRE(pv2->value<int>() == 1);
    REQUIRE_THROWS(pv2->value<TestCounted>().m_value);
    *pv2 = *pv;
    REQUIRE(TestCounted::m_instanceCount == 2);
    REQUIRE(pv2->value<TestCounted>().m_value == 2);
    REQUIRE_THROWS(pv2->value<int>());
    delete pv;
    delete pv2;
    delete pv1;
    REQUIRE(TestCounted::m_instanceCount == 0);
}

TEST_CASE("ValueHolder/Check string handling","strings of different types")
{
    using goospimpl::ValueHolder;

    const char* testString = "fred";

    ValueHolder* pv = new ValueHolder(testString);
    std::string t = pv->value<const char*>();
    REQUIRE(t == "fred");
    const char* ps = pv->value<const char*>();
    REQUIRE(ps == testString);
}

