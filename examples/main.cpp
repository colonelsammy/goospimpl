#define CATCH_CONFIG_MAIN
#include "catch.hpp"
//#include "goospimpl.hpp"

//using namespace goospimpl;

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

#ifdef XXX
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
