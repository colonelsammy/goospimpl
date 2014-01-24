#include "catch.hpp"
//#include "any_facade.hpp"

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
        : ty(0), v(t)
    {}
    action(int x, const T& t)
        : ty(x), v(t)
    {}
    T invoke() const
    {
        if( ty ) throw std::runtime_error("action throw");
        return v;
    }
    template <typename U>
    action(const action<U>& rhs)
        : ty(rhs.ty), v(ty ? T() : rhs.v)
    {
    }
    int ty;
    T v;
};

template <typename T>
action<T> returnValue(const T& v)
{
    return action<T>(v);
}

template <typename T>
action<T> throwException(const T& t)
{
    return action<T>(1,t);
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
    {}

    template <typename T>
    class MethodExpectation
    {
        friend class Mock;
    public:
        MethodExpectation()
            : m_expected(0)
        {}
        template <typename U>
        MethodExpectation& operator,(U& rhs)
        {
            return rhs;
        }
        template <typename U>
        MethodExpectation& operator,(const std::vector<action<U> >& rhs)
        {
            for( typename std::vector<action<U> >::const_iterator it = rhs.begin(); it != rhs.end(); ++it )
            {
                m_actions.push_back(*it);
            }
            return *this;
        }
        template <typename U>
        MethodExpectation& will(const action<U>& a)
        {
            m_actions.push_back(a);
            return *this;
        }
        template <typename U>
        MethodExpectation& WillOnce(const action<U>& a)
        {
            m_actions.push_back(a);
            return *this;
        }
        MethodExpectation& Times(int count)
        {
            m_expected = count;
            return *this;
        }
    private:
        int m_expected;
        std::vector<int> m_v;
        std::vector<action<int> > m_actions;
    };
    class Cardinality
    {
    public:
        Cardinality(Mock& obj, int c)
            : m_obj(obj), m_count(c)
        {}
        MethodExpectation<int>& foo(int v)
        {
            MethodExpectation<int>& result = m_obj.m_expect1_foo.appendMethod();
            result.m_expected = m_count;
            result.m_v.push_back(v);
            return result;
        }
    private:
        Mock& m_obj;
        int m_count;
    };
    class Expectation
    {
    public:
        Expectation(Mock& obj)
            : m_obj(obj)
        {}
        MethodExpectation<int>& foo(int v)
        {
            MethodExpectation<int>& result = m_obj.m_expect1_foo.appendMethod();
            result.m_v.push_back(v);
            return result;
        }
    private:
        Mock& m_obj;
    };

    template <typename R>
    class MethodExpectations
    {
        friend class Mock;
    public:
        MethodExpectation<R>& appendMethod()
        {
            MethodExpectation<R> tmp;
            m_expectations.push_back(tmp);
            return m_expectations.back();
        }
    private:
        std::vector<MethodExpectation<R> > m_expectations;
    };
    
    // MOCK_METHOD1(foo, int(int));
public:
    virtual int foo(int v)
    {
        assert(v == m_expect1_foo.m_expectations[0].m_v[0]);
        return m_expect1_foo.m_expectations[0].m_actions[0].invoke();
    }
private:
    MethodExpectations<int> m_expect1_foo;
    //
};

template <typename T>
typename Mock<T>::Cardinality oneOf(T& mock)
{
    Mock<T>& t = dynamic_cast<Mock<T>&>(mock);
    return typename Mock<T>::Cardinality(t, 1);
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
    typename Mock<T>::Cardinality of(T& mock)
    {
        Mock<T>& t = dynamic_cast<Mock<T>&>(mock);
        return typename Mock<T>::Cardinality(t, m_count);
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

    SECTION("Exception")
    {
        context.checking(
                            (
                                oneOf(mock1).foo(42).will(throwException(std::runtime_error("bar")))
                            )
                        );

        REQUIRE_THROWS(mock1.foo(42));
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
    Mock<MockInterface>::Expectation( obj ). call

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
