#include "catch.hpp"

#include "with.hpp"
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

TEST_CASE("With/1","")
{
    using goospimpl::EqualsMatcher2;
    using goospimpl::WithMatcher2;
    using goospimpl::MatcherHolder2;

    WithMatcher2<EqualsMatcher2<int> > wm(2);
    MatcherHolder2 matcher = wm.matcher<double>();
}
