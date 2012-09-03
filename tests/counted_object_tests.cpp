#include "catch.hpp"

#include "counted_instance.hpp"

namespace
{
    struct TestCounted : goospimpl::CountedInstance
    {
        TestCounted()
        {
            m_instanceCount++;
        }
        ~TestCounted()
        {
            m_instanceCount--;
        }
        static int m_instanceCount;
    };
    int TestCounted::m_instanceCount = 0;
}

TEST_CASE("Counted/1","")
{
    using goospimpl::CountedContent;

    CountedContent<TestCounted>* t = new CountedContent<TestCounted>;
    REQUIRE(t->addRef() == 2);
    REQUIRE(t->release() == 1);
    REQUIRE(t->m_instanceCount == 1);
    REQUIRE(t->release() == 0);
    REQUIRE(t->m_instanceCount == 0);
}
