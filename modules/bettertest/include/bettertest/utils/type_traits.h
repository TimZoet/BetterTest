#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <concepts>
#include <memory>

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "common/type_traits.h"

namespace bt::type_traits
{
    template<typename A, typename B>
    concept comparable_eq = requires(A lhs, B rhs) {
        {
            lhs == rhs
        } -> std::same_as<bool>;
    };

    template<typename A, typename B>
    concept comparable_ne = requires(A lhs, B rhs) {
        {
            !(lhs == rhs)
        } -> std::same_as<bool>;
    };

    template<typename A, typename B>
    concept comparable_lt = requires(A lhs, B rhs) {
        {
            lhs < rhs
        } -> std::same_as<bool>;
    };

    template<typename A, typename B>
    concept comparable_gt = requires(A lhs, B rhs) {
        {
            lhs > rhs
        } -> std::same_as<bool>;
    };

    template<typename A, typename B>
    concept comparable_le = requires(A lhs, B rhs) {
        {
            lhs <= rhs
        } -> std::same_as<bool>;
    };

    template<typename A, typename B>
    concept comparable_ge = requires(A lhs, B rhs) {
        {
            lhs >= rhs
        } -> std::same_as<bool>;
    };

    template<typename A, typename B, typename C, bool L, bool U>
    concept comparable_between = (comparable_le<A, B> && L || comparable_lt<A, B> && !L) &&
                                 (comparable_le<B, C> && U || comparable_lt<B, C> && !U);
}  // namespace bt::type_traits
