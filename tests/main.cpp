#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "member_function_traits.hpp"

TEST_CASE("sanity/1", "sanity check")
{
    REQUIRE(true);
}

template <typename Interface>
struct TypeInfo
{
    static int s_type;

    template <typename T>
    static int typeId(const T&)
    {
        static bool init(false);
        static int result;
        if( !init )
        {
            result = ++s_type;
            init = true;
        }
        return result;
    }
};

template <typename Interface>
//static
int TypeInfo<Interface>::s_type = 0;

template <typename Interface>
struct placeholder : public Interface
{
    virtual ~placeholder() {}
    virtual placeholder<Interface>* clone() const = 0;
    // comparable
    virtual bool typeMatches(const placeholder& other) const = 0;
    virtual int type() const  = 0;
};

template <typename Interface, typename T>
struct Comparable : public placeholder<Interface>
{
    ~Comparable() {}
    virtual T value() const = 0;
    virtual bool match(const T& v) const = 0;
};

template <typename UserOperations, typename Interface, typename ValueType>
class holder : public Comparable<Interface, ValueType>
{
public:
    holder()
        : m_value()
    {}
    holder(const ValueType& value)
        : m_value(value)
    {}
    virtual placeholder<Interface>* clone() const
    {
        const UserOperations* p = static_cast<const UserOperations*>(this);
        return new UserOperations(*p);
    }
    virtual int type() const
    {
        return TypeInfo<Interface>::typeId(m_value);
    }

    virtual ValueType value() const
    {
        return m_value;
    }
    virtual bool typeMatches(const placeholder<Interface>& other) const
    {
        if( type() == other.type() )
        {
            // safe - types match
            const Comparable<Interface, ValueType>* rhs = static_cast<const Comparable<Interface, ValueType>*>(&other);
            return this->match(rhs->value());
        }
        return false;
    }

protected:
    ValueType m_value;
};

template <typename T>
class my_operations;

template <typename Interface>
class any_interface
{
public:
    any_interface()
        : m_held(0)
    {}
    ~any_interface()
    {
        delete m_held;
    }
    template <typename T>
    any_interface(const T& v)
        : m_held(new my_operations<T>(v))
    {
    }
    any_interface(const any_interface& rhs)
        : m_held(rhs.m_held ? static_cast<placeholder<Interface>*>(rhs.m_held)->clone() : NULL)
    {}
    any_interface& operator=(any_interface rhs)
    {
        return rhs.swapContent(*this);
    }

    template <typename Function>
    typename goospimpl::member_function_traits<Function>::result_type operator()(Function func)
    {
        return (m_held->*func)();
    }
    template <typename Function>
    typename goospimpl::member_function_traits<Function>::result_type operator()(Function func, typename goospimpl::member_function_traits<Function>::arg1_type t1)
    {
        return (m_held->*func)(t1);
    }

    bool match(const any_interface& other) const
    {
        if( m_held && other.m_held )
        {
            return m_held->typeMatches(*other.m_held);
        }
        return false;
    }

private:
    any_interface& swapContent(any_interface & rhs)
    {
        std::swap(m_held, rhs.m_held);
        return *this;
    }

    placeholder<Interface>* m_held;
};

struct Printable
{
    ~Printable() {}
    virtual void print(std::ostream& os) const = 0;
};

struct Queryable : public Printable
{
    ~Queryable() {}
    virtual std::string asString() const = 0;
};

template <typename T>
class my_operations : public holder<my_operations<T>, Queryable, T>
{
public:
    my_operations(const T& value)
        : holder<my_operations<T>, Queryable, T>(value)
    {}

    // Comparable
    virtual bool match(const T& v) const
    {
        return (v == this->m_value);
    }
    // Printable
    virtual void print(std::ostream& os) const
    {
        os << this->m_value;
    }
    // Queryable
    virtual std::string asString() const
    {
        std::ostringstream oss;
        oss << "The value is: " << this->m_value;
        return oss.str();
    }
};

struct A
{
    A(int v)
        : m_int(v)
    {}
    void print(std::ostream& os) const
    {
        os << "The int value is: " << m_int;
    }
    int m_int;
};

template <>
class my_operations<A> : public holder<my_operations<A>, Queryable, A>
{
public:
    my_operations(const A& value)
        : holder(value)
    {}
    // Comparable
    virtual bool match(const A& v) const
    {
        return (v.m_int == m_value.m_int);
    }
    // Printable
    virtual void print(std::ostream& os) const
    {
        m_value.print(os);
    }
    // Queryable
    virtual std::string asString() const
    {
        std::ostringstream oss;
        oss << "asString: ";
        m_value.print(oss);
        return oss.str();
    }
};
TEST_CASE("any/1", "any check")
{
    any_interface<Queryable> h(42);
    std::ostringstream oss;
    h(&Printable::print, oss);
    std::string result = oss.str();
    REQUIRE(result == "42");
    std::string r2 = h(&Queryable::asString);
    REQUIRE(r2 == "The value is: 42");

    A a(27);
    any_interface<Queryable> ha(a);
    std::ostringstream ossa;
    ha(&Printable::print, ossa);
    result = ossa.str();
    REQUIRE(result == "The int value is: 27");
    r2 = ha(&Queryable::asString);
    REQUIRE(r2 == "asString: The int value is: 27");

    bool match = h.match(ha);
    REQUIRE(!match);

    any_interface<Queryable> h2(h);
    match = h.match(h2);
    REQUIRE(match);
}

#ifdef GOOS_PIMPL
#include "goospimpl.hpp"

using namespace goospimpl;

namespace {
    // Interface to mock
    struct Turtle
    {
        virtual ~Turtle() {}
        virtual void penDown() = 0;
        virtual void forward(int x) = 0;
        virtual void turn(double angle) = 0;
        virtual void penUp() = 0;
        virtual void flashLEDs() = 0;
        virtual void throwsException() = 0;
    };
    
    // Class under test
    struct TurtleDriver
    {
        void run(Turtle& t)
        {
            t.penDown();
            t.flashLEDs();
            t.forward(10);
            t.flashLEDs();
            t.turn(90);
            t.flashLEDs();
            t.forward(10);
            t.flashLEDs();
            t.penUp();
        }
        void sequence(Turtle& t)
        {
            t.penDown();
            t.forward(20);
            t.flashLEDs();
            t.forward(10);
            t.flashLEDs();
            t.penUp();
            try
            {
                t.throwsException();
                REQUIRE(false);
            }
            catch(const std::runtime_error& e)
            {
                REQUIRE(e.what() == std::string("called throwsException"));
            }
        }
    };
    
}

MOCK_CLASS_6(Turtle, penDown, forward, turn, penUp, flashLEDs, throwsException);

TEST_CASE("mock/1", "Tests an empty mock object fails - this test is expected to fail!")
{
    Mockery context;
    Turtle& turtle = context.mock<Turtle>();
    context.checking( (Expectations()
        ) );

    TurtleDriver t;
    t.run(turtle);
}

TEST_CASE("mock/2", "Tests variants of equals matchers")
{
    Mockery context;
    States pen = context.states("pen").startsAs("up");
    Turtle& turtle = context.mock<Turtle>();


    context.checking( (Expectations(),
        allowing(turtle, &Turtle::flashLEDs),
        oneOf(turtle, &Turtle::penDown), then(pen.is("down")),
        oneOf(turtle, &Turtle::forward, with(equal(10))), when(pen.is("down")),
        oneOf(turtle, &Turtle::turn, with(equal(90, 0.001))), when(pen.is("down")),
        oneOf(turtle, &Turtle::forward, 10), when(pen.is("down")),
        oneOf(turtle, &Turtle::penUp), then(pen.is("up"))
        ) );

    TurtleDriver t;
    t.run(turtle);
}

TEST_CASE("mock/3", "Test 'with' and 'equal' and 'any'")
{
    Mockery context;
    States pen = context.states("pen").startsAs("up");
    Turtle& turtle = context.mock<Turtle>();
    context.checking( (Expectations(),
        allowing(turtle, &Turtle::flashLEDs),
        oneOf(turtle, &Turtle::penDown), then(pen.is("down")),
        oneOf(turtle, &Turtle::forward, with(any<int>())), when(pen.is("down")),
        oneOf(turtle, &Turtle::turn, with(equal(90, 0.001))), when(pen.is("down")),
        oneOf(turtle, &Turtle::forward, 10), when(pen.is("down")),
        oneOf(turtle, &Turtle::penUp), then(pen.is("up"))
        ) );

    TurtleDriver t;
    t.run(turtle);
}

TEST_CASE("mock/4", "Tests sequence and throws")
{
    Mockery context;
    Sequence s = context.sequence("in order");
    Turtle& turtle = context.mock<Turtle>();
    context.checking( (Expectations(),
        allowing(turtle, &Turtle::flashLEDs),
        oneOf(turtle, &Turtle::penDown), inSequence(s),
        oneOf(turtle, &Turtle::forward, between(19,21)), inSequence(s),
        oneOf(turtle, &Turtle::forward, 10), inSequence(s),
        oneOf(turtle, &Turtle::penUp), inSequence(s),
        oneOf(turtle, &Turtle::throwsException), will(throw_exception(std::runtime_error("called throwsException")))
        ) );

    TurtleDriver t;
    t.sequence(turtle);
}

TEST_CASE("mock/5", "Tests exactly/of")
{
    Mockery context;
    States pen = context.states("pen").startsAs("up");
    Turtle& turtle = context.mock<Turtle>();


    context.checking( (Expectations(),
        allowing(turtle, &Turtle::flashLEDs),
        exactly(1).of(turtle, &Turtle::penDown), then(pen.is("down")),
        oneOf(turtle, &Turtle::forward, with(equal(10))), when(pen.is("down")),
        oneOf(turtle, &Turtle::turn, with(equal(90, 0.001))), when(pen.is("down")),
        oneOf(turtle, &Turtle::forward, 10), when(pen.is("down")),
        oneOf(turtle, &Turtle::penUp), then(pen.is("up"))
        ) );

    TurtleDriver t;
    t.run(turtle);
}
#endif
