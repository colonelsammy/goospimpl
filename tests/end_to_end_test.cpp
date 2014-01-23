#include "catch.hpp"

template <typename T>
class Mock;

class Mockery
{
public:
    Mockery()
    {}

    template <typename Interface>
    Mock<Interface>& gmock()
    {
        Mock<Interface>* p = new Mock<Interface>();
        return *p;
    }

    template <typename Interface>
    Interface& mock()
    {
        Interface* p = new Mock<Interface>();
        return *p;
    }
    
    template <typename T>
    void checking(const T& a)
    {
    }
};

template <typename T>
struct action
{
    action(const T& t)
        : v(t)
    {}
    T v;
};

template <typename T>
action<T> returnValue(const T& v)
{
    return action<T>(v);
}

class MockInterface
{
public:
    virtual ~MockInterface() {}
    virtual int foo(int) = 0;
};

template <typename Interface>
class Mock : public Interface
{
    friend class Mockery;
public:
    Mock()
        : m_expectations(self()), m_expected(0)
    {}
    template <typename T>
    class MethodExpectation
    {
    public:
        MethodExpectation()
            : m_expected(0)
        {}
        template <typename U>
        MethodExpectation& will(const U& action)
        {
            std::vector<U> a;
            a.push_back(action);
            return *this;
        }
        template <typename U>
        MethodExpectation& WillOnce(const U& action)
        {
            std::vector<U> a;
            a.push_back(action);
            return *this;
        }
        MethodExpectation<T>& Times(int count)
        {
            m_expected = count;
            return *this;
        }
    private:
        Expectations& m_obj;
        int m_expected;
    };
    class Expectations
    {
    public:
        template <typename T>
        class MethodExpectation
        {
            friend class Expectations;
        public:
            MethodExpectation(Expectations& e)
                : m_obj(e)
            {}
            template <typename U>
            Expectations& operator,(const std::vector<action<U> >& rhs)
            {
                for( typename std::vector<action<U> >::const_iterator it = rhs.begin(); it != rhs.end(); ++it )
                {
                    m_obj.m_obj.m_actions.push_back(action<T>(it->v));
                }
                return m_obj;
            }
            template <typename U>
            Expectations& will(const U& action)
            {
                std::vector<U> a;
                a.push_back(action);
                return operator,(a);
            }
            template <typename U>
            Expectations& WillOnce(const U& action)
            {
                std::vector<U> a;
                a.push_back(action);
                return operator,(a);
            }
            MethodExpectation<T>& Times(int count)
            {
                m_obj.m_obj.m_expected = count;
                return *this;
            }
        private:
            Expectations& m_obj;
        };
    public:
        Expectations(Mock& m)
            : m_obj(m)
        {}
        MethodExpectation<int> foo(int v)
        {
            m_obj.m_v.push_back(v);
            return MethodExpectation<int>(*this);
        }
        template <typename U>
        Expectations& operator,(MethodExpectation<U>& rhs)
        {
            return rhs.m_obj;
        }
        template <typename T>
        Expectations& operator,(T& rhs)
        {
            return rhs;
        }
        template <typename T>
        Expectations& operator,(const std::vector<action<T> >& rhs)
        {
            m_obj.m_actions = rhs;
            return *this;
        }
        template <typename T>
        Expectations& Returns(const T& t)
        {
            return *this;
        }
    private:
        Mock& m_obj;
    };
    class Cardinality
    {
    public:
        Cardinality(int c)
            : m_count(c)
        {}
        Expectations::MethodExpectation<int>& foo(int v)
        {
            return m_expect1_foo.addMethod();
        }
    private:
        int m_count;
    };
    Expectations& expect(int count)
    {
        m_expected = count;
        return m_expectations;
    }

    template <typename R>
    class MethodExpectations
    {
    public:
        typename Expectations::MethodExpectation<R>& addMethod()
        {
            Expectations::MethodExpectation<R> > tmp;
            m_expectations.push_back(tmp);
            return m_expectations.back();
        }
    private:
        std::vector<typename Expectations::MethodExpectation<R> > m_expectations;
    };
    
    // MOCK_METHOD1(foo, int(int));
public:
    virtual int foo(int v)
    {
        assert(v == m_v[0]);
        return m_actions[0].v;
    }
private:
    MethodExpectations<int> m_expect1_foo;
    //
private:
    // The only use of this method is safe...we are guaranteed that
    // the Expectations will not use the Mock object in its constructor.
    Mock& self()
    {
        return *this;
    }

    Expectations m_expectations;
    int m_expected;
    std::vector<int> m_v;
    std::vector<action<int> > m_actions;
};

template <typename T>
typename Mock<T>::Expectations oneOf(T& mock)
{
    Mock<T>& t = dynamic_cast<Mock<T>&>(mock);
    return t.expect(1);
}

template <typename T>
std::vector<T> will(const T& action)
{
    std::vector<T> a;
    a.push_back(action);
    return a;
}

struct exactly
{
    explicit exactly(int t)
        : m_count(t)
    {}
    template <typename T>
    typename Mock<T>::Expectations of(T& mock)
    {
        Mock<T>& t = dynamic_cast<Mock<T>&>(mock);
        return t.expect(m_count);
    }
    int m_count;
};

struct Ax
{
    explicit Ax(int t)
        : v(t)
    {}
    operator int() const
    {
        return v;
    }
    int v;
};

TEST_CASE("End to end 'jMock' test")
{
    Mockery context;
    MockInterface& mock1 = context.mock<MockInterface>();
    MockInterface& mock2 = context.mock<MockInterface>();

    // Either syntax is ok....
    SECTION("Traditional jMock style syntax")
    {
        context.checking(
                            (
                                oneOf(mock1).foo(42), will(returnValue(Ax(27))),
                                exactly(2).of(mock2).foo(666), will(returnValue(1))
                            )
                        );
        
        REQUIRE(mock1.foo(42) == 27);
        REQUIRE(mock2.foo(666) == 1);
    }
    
    SECTION("Modified syntax that reads left to right...")
    {
        context.checking(
                            (
                                oneOf(mock1).foo(42).will(returnValue(Ax(27))),
                                exactly(1).of(mock2).foo(666).will(returnValue(1))
                            )
                        );

        REQUIRE(mock1.foo(42) == 27);
        REQUIRE(mock2.foo(666) == 1);
    }
}

// gmock.h

namespace testing
{
    template <typename T>
    action<T> Return(const T& v)
    {
        return action<T>(v);
    }
}

#define EXPECT_CALL(obj, call) \
    Mock<MockInterface>::Expectations( obj ). call

#define EXPECT_EQ( a, b ) \
    REQUIRE( (a) == (b) )
// #endif

using testing::Return;

TEST_CASE("End to end 'gmock' test")
{
    Mock<MockInterface> mock1;
    Mock<MockInterface> mock2;

    EXPECT_CALL( mock1, foo(42) ).Times(1).WillOnce(Return(Ax(27)));
    EXPECT_CALL( mock2, foo(666) ).Times(1).WillOnce(Return(1));

    EXPECT_EQ(mock1.foo(42), 27);
    EXPECT_EQ(mock2.foo(666), 1);
}

