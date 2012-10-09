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

void functionWithTemporaries()
{
    using goospimpl::ValueHolder;

    ValueHolder* pv = new ValueHolder((TestCounted(2)));
    ValueHolder* pv1 = new ValueHolder((TestCounted(1)));
    ValueHolder* pv2 = new ValueHolder();

    const TestCounted& v0 = pv->value<TestCounted>();   // creates a temporary, bound to the const ref
    REQUIRE(v0.m_value == 2);
    const TestCounted& v1 = pv1->value<TestCounted>();   // creates a temporary, bound to the const ref
    REQUIRE(v1.m_value == 1);
    REQUIRE_THROWS(pv2->value<TestCounted>());
    *pv2 = *pv1;
    REQUIRE(TestCounted::m_instanceCount == 5);
    REQUIRE(pv2->value<TestCounted>().m_value == 1);
    *pv2 = *pv;
    REQUIRE(TestCounted::m_instanceCount == 5);
    REQUIRE(pv2->value<TestCounted>().m_value == 2);
    delete pv;
    REQUIRE(TestCounted::m_instanceCount == 4);
    delete pv2;
    REQUIRE(TestCounted::m_instanceCount == 3);
    delete pv1;
    REQUIRE(TestCounted::m_instanceCount == 2);
    // temporaries wil be released here...
}

TEST_CASE("ValueHolder/Assignment copies underlying object","assignment")
{
    functionWithTemporaries();
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
    std::string t = pv->value<std::string>();
    REQUIRE(t == "fred");
    // won't compile
    //const char* ps = pv->value<const char*>();
}

namespace UnitTest
{
    class TestValueObject
    {
    public:
        TestValueObject()
            : m_str("fred"), m_value(27)
        {}
        bool matches(const TestValueObject& rhs) const
        {
            return (m_str == rhs.m_str &&
                m_value == rhs.m_value);
        }
        // Requirements: must be copy constructable
        TestValueObject(const TestValueObject& rhs)
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
        TestValueObject(TestValueObject&& rhs)
            : m_str(std::move(rhs.m_str)), m_value(std::move(rhs.m_value))
        {
        }
#endif
    private:
        // not assignable
        TestValueObject& operator=(const TestValueObject& rhs);
#if __cplusplus >= 201103
        TestValueObject& operator=(TestValueObject&& rhs);
#endif

        std::string m_str;
        int m_value;
    };

        // Requirements: must be comparable for equals
    bool operator==(const TestValueObject& lhs, const TestValueObject& rhs)
    {
        return lhs.matches(rhs);
    }
    // Requirements: must be streamable
    std::ostream& operator<<(std::ostream& os, const TestValueObject& rhs)
    {
        rhs.print(os);
        return os;
    }
}

template <typename T>
void addReference(const UnitTest::TestValueObject& v, T t)
{
    using goospimpl::ValueHolder;
    ValueHolder* pv = new ValueHolder(v);
    T vt = pv->value<T>();
    REQUIRE(vt == t);
    delete pv;
}

template <typename T>
T createRef()
{
    T t;
    return t;
}

#if __cplusplus >= 201103
template <typename T>
void addRvalueReference(const UnitTest::TestValueObject&& v, T t)
{
    using goospimpl::ValueHolder;
    ValueHolder* pv = new ValueHolder(v);
    T vt = pv->value<T>();
    REQUIRE(vt == t);
    delete pv;
}
#endif

TEST_CASE("ValueHolder/Check object handling","check that objects can be constructed by value and by reference")
{
    UnitTest::TestValueObject t;
    addReference<UnitTest::TestValueObject>(t, t);
    addReference<const UnitTest::TestValueObject>(t, t);
    addReference<const UnitTest::TestValueObject&>(t, t);
#if __cplusplus >= 201103
    addRvalueReference<UnitTest::TestValueObject>(createRef<UnitTest::TestValueObject>(), t);
    addRvalueReference<const UnitTest::TestValueObject>(createRef<UnitTest::TestValueObject>(), t);
    addRvalueReference<const UnitTest::TestValueObject&>(createRef<UnitTest::TestValueObject>(), t);
#endif
}

template <typename T>
void addPointer(const UnitTest::TestValueObject* v, T* t)
{
    using goospimpl::ValueHolder;
    ValueHolder* pv = new ValueHolder(v);
    const T* vt = pv->value<const T*>();
    REQUIRE(vt == t);
    delete pv;
}

template <typename T>
void addConstPointer(const UnitTest::TestValueObject* const v, T* t)
{
    using goospimpl::ValueHolder;
    ValueHolder* pv = new ValueHolder(v);
    const T* vt = pv->value<const T*>();
    REQUIRE(vt == t);
    delete pv;
}

TEST_CASE("ValueHolder/Check pointer","check that pointers can be stored and returned")
{
    UnitTest::TestValueObject* t = new UnitTest::TestValueObject();
    addPointer<UnitTest::TestValueObject>(t, t);
    addPointer<const UnitTest::TestValueObject>(t, t);
    addConstPointer<UnitTest::TestValueObject>(t, t);
    addConstPointer<const UnitTest::TestValueObject>(t, t);
    delete t;
}
