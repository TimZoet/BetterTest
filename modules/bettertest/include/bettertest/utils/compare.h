#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <concepts>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/utils/result.h"
#include "bettertest/utils/try.h"

namespace bt
{
    template<typename A, typename B>
    concept can_compare_eq = requires(A lhs, B rhs)
    {
        {
            lhs == rhs
            } -> std::same_as<bool>;
    };

    template<typename A, typename B>
    concept can_compare_lt = requires(A lhs, B rhs)
    {
        {
            lhs < rhs
            } -> std::same_as<bool>;
    };

    template<typename A, typename B>
    concept can_compare_gt = requires(A lhs, B rhs)
    {
        {
            lhs > rhs
            } -> std::same_as<bool>;
    };

    template<typename A, typename B>
    concept can_compare_le = requires(A lhs, B rhs)
    {
        {
            lhs <= rhs
            } -> std::same_as<bool>;
    };

    template<typename A, typename B>
    concept can_compare_ge = requires(A lhs, B rhs)
    {
        {
            lhs >= rhs
            } -> std::same_as<bool>;
    };

    template<typename A, typename B, typename C, bool L, bool U>
    concept can_compare_between = (can_compare_le<A, B> && L || can_compare_lt<A, B> && !L) &&
                                  (can_compare_le<B, C> && U || can_compare_lt<B, C> && !U);

    template<typename F>
    result_t compare_impl(const F& f)
    {
        const auto r = try_catch(f);
        if (!r.first) return result_t::exception;
        if (!r.second) return result_t::failure;
        return result_t::success;
    }

    template<typename A>
    requires(can_compare_eq<A, bool>) result_t compare_true(const A& lhs)
    {
        return compare_impl([&]() { return lhs == true; });
    }

    template<typename A>
    requires(can_compare_eq<A, bool>) result_t compare_false(const A& lhs)
    {
        return compare_impl([&]() { return lhs == false; });
    }

    template<typename A, typename B>
    requires(can_compare_eq<A, B>) result_t compare_eq(const A& lhs, const B& rhs)
    {
        return compare_impl([&]() { return lhs == rhs; });
    }

    template<typename A, typename B>
    requires(can_compare_eq<A, B>) result_t compare_ne(const A& lhs, const B& rhs)
    {
        return compare_impl([&]() { return !(lhs == rhs); });
    }

    template<typename A, typename B>
    requires(can_compare_lt<A, B>) result_t compare_lt(const A& lhs, const B& rhs)
    {
        return compare_impl([&]() { return lhs < rhs; });
    }

    template<typename A, typename B>
    requires(can_compare_gt<A, B>) result_t compare_gt(const A& lhs, const B& rhs)
    {
        return compare_impl([&]() { return lhs > rhs; });
    }

    template<typename A, typename B>
    requires(can_compare_le<A, B>) result_t compare_le(const A& lhs, const B& rhs)
    {
        return compare_impl([&]() { return lhs <= rhs; });
    }

    template<typename A, typename B>
    requires(can_compare_ge<A, B>) result_t compare_ge(const A& lhs, const B& rhs)
    {
        return compare_impl([&]() { return lhs >= rhs; });
    }

    template<typename A, typename B, typename C, bool LowerInclusive, bool UpperInclusive>
    requires(can_compare_between<A, B, C, LowerInclusive, UpperInclusive>) result_t
      compare_between(const A& lower, const B& middle, const C& upper)
    {
        if constexpr (LowerInclusive)
        {
            if constexpr (UpperInclusive)
                return compare_impl([&]() { return lower <= middle && middle <= upper; });
            else
                return compare_impl([&]() { return lower <= middle && middle < upper; });
        }
        else
        {
            if constexpr (UpperInclusive)
                return compare_impl([&]() { return lower < middle && middle <= upper; });
            else
                return compare_impl([&]() { return lower < middle && middle < upper; });
        }
    }
}  // namespace bt
