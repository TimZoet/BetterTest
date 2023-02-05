#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <string>

namespace bt
{
    template<size_t N>
    size_t getStaticStringLength(const char (&)[N])
    {
        return N;
    }

    template<typename T>
    [[nodiscard]] auto getPrettyClassName()
    {
        /*
         * namespace foo {
         * template<typename T, size_t N, typename U = nullptr_t>
         * class bar{};
         * }
         *
         * getPrettyClassName<foo::bar<float, 4>>()
         *
         * In MSVC:
         * __FUNCSIG__          = auto __cdecl bt::getPrettyClassName<class foo::bar<float,4,std::nullptr_t>>(void)
         * prettyName           = foo::bar<float,4,std::nullptr_t>
         * In GCC:
         * __PRETTY_FUNCTION__  = auto getPrettyClassName() [with T = foo::bar<float, 4>]
         * prettyName           = foo::bar<float, 4>
         * In Clang:
         * __PRETTY_FUNCTION__  = auto getPrettyClassName() [T = app::UnitTest0<float, 4, nullptr_t>]
         * prettyName           = foo::bar<float, 4, nullptr_t>
         */
#if defined _MSC_VER
        const auto name = __FUNCSIG__;

        // Find first and last occurrences of < and >.
        auto start = static_cast<size_t>(-1);
        auto end   = static_cast<size_t>(-1);
        for (size_t i = 0; i < getStaticStringLength(__FUNCSIG__); i++)
        {
            if (start == static_cast<size_t>(-1) && name[i] == '<') start = i;
            if (name[i] == '>') end = i;
        }
        start += 7;
#else
        const auto name = __PRETTY_FUNCTION__;
        // Find =.
        size_t end   = getStaticStringLength(__PRETTY_FUNCTION__) - 2;
        size_t start = end;
        while (name[start] != '=') start--;
        start += 2;
#endif

        std::string prettyName;
        prettyName.reserve(end - start);
        for (auto i = start; i < end; i++) prettyName += name[i];
        return prettyName;
    }
}  // namespace bt