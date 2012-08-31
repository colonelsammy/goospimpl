//          Copyright Malcolm Noyes 2012.
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#ifndef GOOS_PIMPL_MOCK_CLASS_HPP
#define GOOS_PIMPL_MOCK_CLASS_HPP

#include "expectations.hpp"
#include "member_function_traits.hpp"
#include <cassert>

namespace goospimpl
{
    namespace detail
    {
        template <int N1, int N2, typename T = int>
        struct equal_to
        {
            static const bool value = (N1 == N2);
            typedef T type;
        };

        template <typename T>
        struct ResolvedReturnValue
        {
            T v;
            explicit ResolvedReturnValue(const ValueHolder& a)
                : v(a.value<T>())
            {}
            T value() const {return v;}
        };

        template <>
        struct ResolvedReturnValue<void>
        {
            explicit ResolvedReturnValue(const ValueHolder&)
            {}
            void value() const {}
        };

        struct EmptyArg
        {
            typedef int type;
        };

        template <typename T, int N>
        struct ArityMatcher;

        template <typename T>
        struct ArityMatcher<T, 0>
        {
            typedef EmptyArg arg1_type;
            typedef EmptyArg arg2_type;
            typedef EmptyArg arg3_type;
            typedef EmptyArg arg4_type;
            typedef EmptyArg arg5_type;
            typedef EmptyArg arg6_type;
            typedef EmptyArg arg7_type;
            typedef EmptyArg arg8_type;
            typedef EmptyArg arg9_type;
            typedef EmptyArg arg10_type;
        };

        template <typename T>
        struct ArityMatcher<T, 1>
        {
            typedef typename member_function_traits<T>::arg1_type arg1_type;
            typedef EmptyArg arg2_type;
            typedef EmptyArg arg3_type;
            typedef EmptyArg arg4_type;
            typedef EmptyArg arg5_type;
            typedef EmptyArg arg6_type;
            typedef EmptyArg arg7_type;
            typedef EmptyArg arg8_type;
            typedef EmptyArg arg9_type;
            typedef EmptyArg arg10_type;
        };

        template <typename T>
        struct ArityMatcher<T, 2>
        {
            typedef typename member_function_traits<T>::arg1_type arg1_type;
            typedef typename member_function_traits<T>::arg2_type arg2_type;
            typedef EmptyArg arg3_type;
            typedef EmptyArg arg4_type;
            typedef EmptyArg arg5_type;
            typedef EmptyArg arg6_type;
            typedef EmptyArg arg7_type;
            typedef EmptyArg arg8_type;
            typedef EmptyArg arg9_type;
            typedef EmptyArg arg10_type;
        };

        template <typename T>
        struct ArityMatcher<T, 3>
        {
            typedef typename member_function_traits<T>::arg1_type arg1_type;
            typedef typename member_function_traits<T>::arg2_type arg2_type;
            typedef typename member_function_traits<T>::arg3_type arg3_type;
            typedef EmptyArg arg4_type;
            typedef EmptyArg arg5_type;
            typedef EmptyArg arg6_type;
            typedef EmptyArg arg7_type;
            typedef EmptyArg arg8_type;
            typedef EmptyArg arg9_type;
            typedef EmptyArg arg10_type;
        };

        template <typename T>
        struct ArityMatcher<T, 4>
        {
            typedef typename member_function_traits<T>::arg1_type arg1_type;
            typedef typename member_function_traits<T>::arg2_type arg2_type;
            typedef typename member_function_traits<T>::arg3_type arg3_type;
            typedef typename member_function_traits<T>::arg4_type arg4_type;
            typedef EmptyArg arg5_type;
            typedef EmptyArg arg6_type;
            typedef EmptyArg arg7_type;
            typedef EmptyArg arg8_type;
            typedef EmptyArg arg9_type;
            typedef EmptyArg arg10_type;
        };

        template <typename T>
        struct ArityMatcher<T, 5>
        {
            typedef typename member_function_traits<T>::arg1_type arg1_type;
            typedef typename member_function_traits<T>::arg2_type arg2_type;
            typedef typename member_function_traits<T>::arg3_type arg3_type;
            typedef typename member_function_traits<T>::arg4_type arg4_type;
            typedef typename member_function_traits<T>::arg5_type arg5_type;
            typedef EmptyArg arg6_type;
            typedef EmptyArg arg7_type;
            typedef EmptyArg arg8_type;
            typedef EmptyArg arg9_type;
            typedef EmptyArg arg10_type;
        };

        template <typename T>
        struct ArityMatcher<T, 6>
        {
            typedef typename member_function_traits<T>::arg1_type arg1_type;
            typedef typename member_function_traits<T>::arg2_type arg2_type;
            typedef typename member_function_traits<T>::arg3_type arg3_type;
            typedef typename member_function_traits<T>::arg4_type arg4_type;
            typedef typename member_function_traits<T>::arg5_type arg5_type;
            typedef typename member_function_traits<T>::arg6_type arg6_type;
            typedef EmptyArg arg7_type;
            typedef EmptyArg arg8_type;
            typedef EmptyArg arg9_type;
            typedef EmptyArg arg10_type;
        };

        template <typename T>
        struct ArityMatcher<T, 7>
        {
            typedef typename member_function_traits<T>::arg1_type arg1_type;
            typedef typename member_function_traits<T>::arg2_type arg2_type;
            typedef typename member_function_traits<T>::arg3_type arg3_type;
            typedef typename member_function_traits<T>::arg4_type arg4_type;
            typedef typename member_function_traits<T>::arg5_type arg5_type;
            typedef typename member_function_traits<T>::arg6_type arg6_type;
            typedef typename member_function_traits<T>::arg7_type arg7_type;
            typedef EmptyArg arg8_type;
            typedef EmptyArg arg9_type;
            typedef EmptyArg arg10_type;
        };

        template <typename T>
        struct ArityMatcher<T, 8>
        {
            typedef typename member_function_traits<T>::arg1_type arg1_type;
            typedef typename member_function_traits<T>::arg2_type arg2_type;
            typedef typename member_function_traits<T>::arg3_type arg3_type;
            typedef typename member_function_traits<T>::arg4_type arg4_type;
            typedef typename member_function_traits<T>::arg5_type arg5_type;
            typedef typename member_function_traits<T>::arg6_type arg6_type;
            typedef typename member_function_traits<T>::arg7_type arg7_type;
            typedef typename member_function_traits<T>::arg8_type arg8_type;
            typedef EmptyArg arg9_type;
            typedef EmptyArg arg10_type;
        };

        template <typename T>
        struct ArityMatcher<T, 9>
        {
            typedef typename member_function_traits<T>::arg1_type arg1_type;
            typedef typename member_function_traits<T>::arg2_type arg2_type;
            typedef typename member_function_traits<T>::arg3_type arg3_type;
            typedef typename member_function_traits<T>::arg4_type arg4_type;
            typedef typename member_function_traits<T>::arg5_type arg5_type;
            typedef typename member_function_traits<T>::arg6_type arg6_type;
            typedef typename member_function_traits<T>::arg7_type arg7_type;
            typedef typename member_function_traits<T>::arg8_type arg8_type;
            typedef typename member_function_traits<T>::arg9_type arg9_type;
            typedef EmptyArg arg10_type;
        };

        template <typename T>
        struct ArityMatcher<T, 10>
        {
            typedef typename member_function_traits<T>::arg1_type arg1_type;
            typedef typename member_function_traits<T>::arg2_type arg2_type;
            typedef typename member_function_traits<T>::arg3_type arg3_type;
            typedef typename member_function_traits<T>::arg4_type arg4_type;
            typedef typename member_function_traits<T>::arg5_type arg5_type;
            typedef typename member_function_traits<T>::arg6_type arg6_type;
            typedef typename member_function_traits<T>::arg7_type arg7_type;
            typedef typename member_function_traits<T>::arg8_type arg8_type;
            typedef typename member_function_traits<T>::arg9_type arg9_type;
            typedef typename member_function_traits<T>::arg10_type arg10_type;
        };
    } // detail

    class FunctionCallResolver
    {
    public:
        explicit FunctionCallResolver(Expectations* p)
            : expectations(p)
        {}
        template <typename RV, typename Mock, typename T>
        RV checkFunctionCall(const std::string& name, const Mock* obj, T fn, const std::vector<ValueHolder>& parameters)
        {
            FunctionHolder t(new detail::FunctionBinder<Mock, T>(obj, fn));
            assert(expectations);
            ValueHolder rv(0);
            expectations->checkFunctionParameters(name, t, parameters, rv);
            return detail::ResolvedReturnValue<RV>(rv).value();
        }
        Expectations* expectations;
    };

    #define MOCK_FN_IMPL(base_name, func_type, func_name) \
        typedef typename member_function_traits<func_type>::result_type result_type_##func_name; \
        typedef typename detail::ArityMatcher<func_type, member_function_traits<func_type>::arity>::arg1_type arg1_type_f1_##func_name; \
        typedef typename detail::ArityMatcher<func_type, member_function_traits<func_type>::arity>::arg2_type arg1_type_f2_##func_name; \
        typedef typename detail::ArityMatcher<func_type, member_function_traits<func_type>::arity>::arg3_type arg1_type_f3_##func_name; \
        typedef typename detail::ArityMatcher<func_type, member_function_traits<func_type>::arity>::arg4_type arg1_type_f4_##func_name; \
        typedef typename detail::ArityMatcher<func_type, member_function_traits<func_type>::arity>::arg5_type arg1_type_f5_##func_name; \
        typedef typename detail::ArityMatcher<func_type, member_function_traits<func_type>::arity>::arg6_type arg1_type_f6_##func_name; \
        typedef typename detail::ArityMatcher<func_type, member_function_traits<func_type>::arity>::arg7_type arg1_type_f7_##func_name; \
        typedef typename detail::ArityMatcher<func_type, member_function_traits<func_type>::arity>::arg8_type arg1_type_f8_##func_name; \
        typedef typename detail::ArityMatcher<func_type, member_function_traits<func_type>::arity>::arg9_type arg1_type_f9_##func_name; \
        typedef typename detail::ArityMatcher<func_type, member_function_traits<func_type>::arity>::arg10_type arg1_type_f10_##func_name; \
        result_type_##func_name func_name() \
        { \
            std::vector<ValueHolder> results; \
            return checkFunctionCall<result_type_##func_name>( std::string(#base_name) + "::" + #func_name, static_cast<const base_type*>(this), &base_type::func_name, results); \
        } \
        result_type_##func_name func_name(arg1_type_f1_##func_name v1) \
        { \
            std::vector<ValueHolder> results; \
            results.push_back(v1); \
            return checkFunctionCall<result_type_##func_name>( std::string(#base_name) + "::" + #func_name, static_cast<const base_type*>(this), &base_type::func_name, results); \
        } \
        result_type_##func_name func_name(arg1_type_f1_##func_name v1, arg1_type_f2_##func_name v2) \
        { \
            std::vector<ValueHolder> results; \
            results.push_back(v1); \
            results.push_back(v2); \
            return checkFunctionCall<result_type_##func_name>( std::string(#base_name) + "::" + #func_name, static_cast<const base_type*>(this), &base_type::func_name, results); \
        } \
        result_type_##func_name func_name(arg1_type_f1_##func_name v1, arg1_type_f2_##func_name v2, arg1_type_f3_##func_name v3) \
        { \
            std::vector<ValueHolder> results; \
            results.push_back(v1); \
            results.push_back(v2); \
            results.push_back(v3); \
            return checkFunctionCall<result_type_##func_name>( std::string(#base_name) + "::" + #func_name, static_cast<const base_type*>(this), &base_type::func_name, results); \
        } \
        result_type_##func_name func_name(arg1_type_f1_##func_name v1, arg1_type_f2_##func_name v2, arg1_type_f3_##func_name v3, arg1_type_f4_##func_name v4) \
        { \
            std::vector<ValueHolder> results; \
            results.push_back(v1); \
            results.push_back(v2); \
            results.push_back(v3); \
            results.push_back(v4); \
            return checkFunctionCall<result_type_##func_name>( std::string(#base_name) + "::" + #func_name, static_cast<const base_type*>(this), &base_type::func_name, results); \
        } \
        result_type_##func_name func_name(arg1_type_f1_##func_name v1, arg1_type_f2_##func_name v2, arg1_type_f3_##func_name v3, arg1_type_f4_##func_name v4, arg1_type_f5_##func_name v5) \
        { \
            std::vector<ValueHolder> results; \
            results.push_back(v1); \
            results.push_back(v2); \
            results.push_back(v3); \
            results.push_back(v4); \
            results.push_back(v5); \
            return checkFunctionCall<result_type_##func_name>( std::string(#base_name) + "::" + #func_name, static_cast<const base_type*>(this), &base_type::func_name, results); \
        } \
        result_type_##func_name func_name(arg1_type_f1_##func_name v1, arg1_type_f2_##func_name v2, arg1_type_f3_##func_name v3, arg1_type_f4_##func_name v4, arg1_type_f5_##func_name v5 \
                                        , arg1_type_f6_##func_name v6) \
        { \
            std::vector<ValueHolder> results; \
            results.push_back(v1); \
            results.push_back(v2); \
            results.push_back(v3); \
            results.push_back(v4); \
            results.push_back(v5); \
            results.push_back(v6); \
            return checkFunctionCall<result_type_##func_name>( std::string(#base_name) + "::" + #func_name, static_cast<const base_type*>(this), &base_type::func_name, results); \
        } \
        result_type_##func_name func_name(arg1_type_f1_##func_name v1, arg1_type_f2_##func_name v2, arg1_type_f3_##func_name v3, arg1_type_f4_##func_name v4, arg1_type_f5_##func_name v5 \
                                        , arg1_type_f6_##func_name v6, arg1_type_f7_##func_name v7) \
        { \
            std::vector<ValueHolder> results; \
            results.push_back(v1); \
            results.push_back(v2); \
            results.push_back(v3); \
            results.push_back(v4); \
            results.push_back(v5); \
            results.push_back(v6); \
            results.push_back(v7); \
            return checkFunctionCall<result_type_##func_name>( std::string(#base_name) + "::" + #func_name, static_cast<const base_type*>(this), &base_type::func_name, results); \
        } \
        result_type_##func_name func_name(arg1_type_f1_##func_name v1, arg1_type_f2_##func_name v2, arg1_type_f3_##func_name v3, arg1_type_f4_##func_name v4, arg1_type_f5_##func_name v5 \
                                        , arg1_type_f6_##func_name v6, arg1_type_f7_##func_name v7, arg1_type_f8_##func_name v8) \
        { \
            std::vector<ValueHolder> results; \
            results.push_back(v1); \
            results.push_back(v2); \
            results.push_back(v3); \
            results.push_back(v4); \
            results.push_back(v5); \
            results.push_back(v6); \
            results.push_back(v7); \
            results.push_back(v8); \
            return checkFunctionCall<result_type_##func_name>( std::string(#base_name) + "::" + #func_name, static_cast<const base_type*>(this), &base_type::func_name, results); \
        } \
        result_type_##func_name func_name(arg1_type_f1_##func_name v1, arg1_type_f2_##func_name v2, arg1_type_f3_##func_name v3, arg1_type_f4_##func_name v4, arg1_type_f5_##func_name v5 \
                                        , arg1_type_f6_##func_name v6, arg1_type_f7_##func_name v7, arg1_type_f8_##func_name v8, arg1_type_f9_##func_name v9) \
        { \
            std::vector<ValueHolder> results; \
            results.push_back(v1); \
            results.push_back(v2); \
            results.push_back(v3); \
            results.push_back(v4); \
            results.push_back(v5); \
            results.push_back(v6); \
            results.push_back(v7); \
            results.push_back(v8); \
            results.push_back(v9); \
            return checkFunctionCall<result_type_##func_name>( std::string(#base_name) + "::" + #func_name, static_cast<const base_type*>(this), &base_type::func_name, results); \
        } \
        result_type_##func_name func_name(arg1_type_f1_##func_name v1, arg1_type_f2_##func_name v2, arg1_type_f3_##func_name v3, arg1_type_f4_##func_name v4, arg1_type_f5_##func_name v5 \
                                        , arg1_type_f6_##func_name v6, arg1_type_f7_##func_name v7, arg1_type_f8_##func_name v8, arg1_type_f9_##func_name v9, arg1_type_f10_##func_name v10) \
        { \
            std::vector<ValueHolder> results; \
            results.push_back(v1); \
            results.push_back(v2); \
            results.push_back(v3); \
            results.push_back(v4); \
            results.push_back(v5); \
            results.push_back(v6); \
            results.push_back(v7); \
            results.push_back(v8); \
            results.push_back(v9); \
            results.push_back(v10); \
            return checkFunctionCall<result_type_##func_name>( std::string(#base_name) + "::" + #func_name, static_cast<const base_type*>(this), &base_type::func_name, results); \
        }

    template <typename T>
    class MockContent : public CountedContent<CountedType>, public T
    {
    public:
        typedef T ValueType;
        ValueType& base() {return *static_cast<ValueType*>(this);}
        virtual const std::type_info & type() const
        {
            return typeid(ValueType);
        }
    };

    class MockHolder : public CountedHolder<MockHolder, CountedType>
    {
    public:
        explicit MockHolder(CountedType* p)
            : CountedHolder(p)
        {
        }
        template <typename T>
        T& mockReference()
        {
            assert(content);
            if( content->type() != typeid(T) )
            {
                throw std::runtime_error("wrong type");
            }
            return static_cast<MockContent<T>*>(content)->base();
        }
        const std::type_info & type() const
        {
            assert(content);
            return content->type();
        }
    };

    template<typename I>
    MockHolder createMockClass(Expectations* p);

    #define MOCK_CLASS_1(base, func1) \
    namespace goospimpl { template <typename base_type, typename F1> \
    MockHolder createMock(Expectations* p, F1) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1); \
    } }

    #define MOCK_CLASS_2(base, func1, func2) \
    namespace goospimpl { template <typename base_type, typename F1, typename F2> \
    MockHolder createMock(Expectations* p, F1, F2) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
            MOCK_FN_IMPL(base, F2, func2) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1, &type::func2); \
    } }

    #define MOCK_CLASS_3(base, func1, func2, func3) \
    namespace goospimpl { template <typename base_type, typename F1, typename F2, typename F3> \
    MockHolder createMock(Expectations* p, F1, F2, F3) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
            MOCK_FN_IMPL(base, F2, func2) \
            MOCK_FN_IMPL(base, F3, func3) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1, &type::func2, &type::func3); \
    } }

    #define MOCK_CLASS_4(base, func1, func2, func3, func4) \
    namespace goospimpl { template <typename base_type, typename F1, typename F2, typename F3, typename F4> \
    MockHolder createMock(Expectations* p, F1, F2, F3, F4) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
            MOCK_FN_IMPL(base, F2, func2) \
            MOCK_FN_IMPL(base, F3, func3) \
            MOCK_FN_IMPL(base, F4, func4) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1, &type::func2, &type::func3, &type::func4); \
    } }

    #define MOCK_CLASS_5(base, func1, func2, func3, func4, func5) \
    namespace goospimpl { template <typename base_type, typename F1, typename F2, typename F3, typename F4, typename F5> \
    MockHolder createMock(Expectations* p, F1, F2, F3, F4, F5) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
            MOCK_FN_IMPL(base, F2, func2) \
            MOCK_FN_IMPL(base, F3, func3) \
            MOCK_FN_IMPL(base, F4, func4) \
            MOCK_FN_IMPL(base, F5, func5) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1, &type::func2, &type::func3, &type::func4, &type::func5); \
    } }

    #define MOCK_CLASS_6(base, func1, func2, func3, func4, func5, func6) \
    namespace goospimpl { template <typename base_type, typename F1, typename F2, typename F3, typename F4, typename F5, typename F6> \
    MockHolder createMock(Expectations* p, F1, F2, F3, F4, F5, F6) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
            MOCK_FN_IMPL(base, F2, func2) \
            MOCK_FN_IMPL(base, F3, func3) \
            MOCK_FN_IMPL(base, F4, func4) \
            MOCK_FN_IMPL(base, F5, func5) \
            MOCK_FN_IMPL(base, F6, func6) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1, &type::func2, &type::func3, &type::func4, &type::func5, &type::func6); \
    } }

    #define MOCK_CLASS_7(base, func1, func2, func3, func4, func5, func6, func7) \
    namespace goospimpl { template <typename base_type, typename F1, typename F2, typename F3, typename F4, typename F5, typename F6, typename F7> \
    MockHolder createMock(Expectations* p, F1, F2, F3, F4, F5, F6, F7) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
            MOCK_FN_IMPL(base, F2, func2) \
            MOCK_FN_IMPL(base, F3, func3) \
            MOCK_FN_IMPL(base, F4, func4) \
            MOCK_FN_IMPL(base, F5, func5) \
            MOCK_FN_IMPL(base, F6, func6) \
            MOCK_FN_IMPL(base, F7, func7) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1, &type::func2, &type::func3, &type::func4, &type::func5, &type::func6, &type::func7); \
    } }

    #define MOCK_CLASS_8(base, func1, func2, func3, func4, func5, func6, func7, func8) \
    namespace goospimpl { template <typename base_type, typename F1, typename F2, typename F3, typename F4, typename F5, typename F6, typename F7, typename F8> \
    MockHolder createMock(Expectations* p, F1, F2, F3, F4, F5, F6, F7, F8) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
            MOCK_FN_IMPL(base, F2, func2) \
            MOCK_FN_IMPL(base, F3, func3) \
            MOCK_FN_IMPL(base, F4, func4) \
            MOCK_FN_IMPL(base, F5, func5) \
            MOCK_FN_IMPL(base, F6, func6) \
            MOCK_FN_IMPL(base, F7, func7) \
            MOCK_FN_IMPL(base, F8, func8) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1, &type::func2, &type::func3, &type::func4, &type::func5, &type::func6, &type::func7, &type::func8); \
    } }

    #define MOCK_CLASS_9(base, func1, func2, func3, func4, func5, func6, func7, func8, func9) \
    namespace goospimpl { template <typename base_type, typename F1, typename F2, typename F3, typename F4, typename F5, typename F6, typename F7, typename F8, typename F9> \
    MockHolder createMock(Expectations* p, F1, F2, F3, F4, F5, F6, F7, F8, F9) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
            MOCK_FN_IMPL(base, F2, func2) \
            MOCK_FN_IMPL(base, F3, func3) \
            MOCK_FN_IMPL(base, F4, func4) \
            MOCK_FN_IMPL(base, F5, func5) \
            MOCK_FN_IMPL(base, F6, func6) \
            MOCK_FN_IMPL(base, F7, func7) \
            MOCK_FN_IMPL(base, F8, func8) \
            MOCK_FN_IMPL(base, F9, func9) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1, &type::func2, &type::func3, &type::func4, &type::func5, &type::func6, &type::func7, &type::func8, &type::func9); \
    } }

    #define MOCK_CLASS_10(base, func1, func2, func3, func4, func5, func6, func7, func8, func9, func10) \
    namespace goospimpl { template <typename base_type, typename F1, typename F2, typename F3, typename F4, typename F5, typename F6, typename F7, typename F8, typename F9, typename F10> \
    MockHolder createMock(Expectations* p, F1, F2, F3, F4, F5, F6, F7, F8, F9, F10) \
    { \
        struct impl : public MockContent<base_type>, public FunctionCallResolver \
        { \
            impl(Expectations* p) : FunctionCallResolver(p) {} \
            virtual const std::type_info & type() const {return typeid(base_type);} \
            MOCK_FN_IMPL(base, F1, func1) \
            MOCK_FN_IMPL(base, F2, func2) \
            MOCK_FN_IMPL(base, F3, func3) \
            MOCK_FN_IMPL(base, F4, func4) \
            MOCK_FN_IMPL(base, F5, func5) \
            MOCK_FN_IMPL(base, F6, func6) \
            MOCK_FN_IMPL(base, F7, func7) \
            MOCK_FN_IMPL(base, F8, func8) \
            MOCK_FN_IMPL(base, F9, func9) \
            MOCK_FN_IMPL(base, F10, func10) \
        }; \
        return MockHolder(new impl(p)); \
    } \
    template<> \
    MockHolder createMockClass<base>(Expectations* p) \
    { \
        typedef base type; \
        return createMock<base>(p, &type::func1, &type::func2, &type::func3, &type::func4, &type::func5, &type::func6, &type::func7, &type::func8, &type::func9, &type::func10); \
    } }
}

#endif
