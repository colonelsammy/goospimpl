//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_DESCRIPTION_HPP
#define GOOS_PIMPL_DESCRIPTION_HPP

#include <sstream>
#include <string>

namespace goospimpl
{
    class Description
    {
    public:
        Description& appendText(const std::string& t)
        {
            m_text.append(t);
            return *this;
        }
        template <typename T>
        Description& appendValue(const T& t)
        {
            std::ostringstream oss;
            oss << "\"" << t << "\"";
            m_text.append(oss.str());
            return *this;
        }
        void print(std::ostream& os) const
        {
            os << m_text;
        }
    private:
        std::string m_text;
    };

    inline std::ostream& operator<<(std::ostream& os, const Description& d)
    {
        d.print(os);
        return os;
    }

}

#endif
