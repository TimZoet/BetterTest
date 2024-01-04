#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <format>
#include <functional>
#include <ranges>
#include <string>
#include <source_location>

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "common/type_traits.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/mixin_interface.h"
#include "bettertest/utils/compare.h"
#include "bettertest/utils/to_string.h"

namespace bt
{
    class CompareMixin : public IMixin
    {
    public:
        ////////////////////////////////////////////////////////////////
        // Types.
        ////////////////////////////////////////////////////////////////

        static constexpr char type[] = "compare";

        enum class RequireEqualLength
        {
            False = 0,
            True  = 1
        };

        ////////////////////////////////////////////////////////////////
        // Constructors.
        ////////////////////////////////////////////////////////////////

        CompareMixin() = default;

        CompareMixin(const CompareMixin&) = delete;

        CompareMixin(CompareMixin&&) = delete;

        ~CompareMixin() noexcept override = default;

        CompareMixin& operator=(const CompareMixin&) = delete;

        CompareMixin& operator=(CompareMixin&&) = delete;

        ////////////////////////////////////////////////////////////////
        // Getters.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] std::string getType() const override;

    protected:
        ////////////////////////////////////////////////////////////////
        // Comparisons.
        ////////////////////////////////////////////////////////////////

        /**
         * \brief lhs == true. Compare a value to true. Does not do implicit conversions to bool.
         * \tparam A Type of left-hand side.
         * \param lhs Left-hand side of comparison.
         * \param loc Automatic source_location.
         * \return Result.
         */
        template<type_traits::comparable_eq<bool> A>
        CheckResult compareTrue(const A& lhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_true(lhs);
            std::string error = res == result_t::success ? "" : std::format("{0} == true", toString(lhs));
            return recordResult(res, loc, std::move(error));
        }

        /**
         * \brief lhs == false. Compare a value to false. Does not do implicit conversions to bool.
         * \tparam A Type of left-hand side.
         * \param lhs Left-hand side of comparison.
         * \param loc Automatic source_location.
         * \return Result.
         */
        template<type_traits::comparable_ne<bool> A>
        CheckResult compareFalse(const A& lhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_false(lhs);
            std::string error = res == result_t::success ? "" : std::format("{0} == false", toString(lhs));
            return recordResult(res, loc, std::move(error));
        }

        /**
         * \brief lhs == rhs. Compare two values for equality.
         * \tparam A Type of left-hand side.
         * \tparam B Type of right-hand side.
         * \param lhs Left-hand side of comparison.
         * \param rhs Right-hand side of comparison.
         * \param loc Automatic source_location.
         * \return Result.
         */
        template<typename A, typename B, typename ProjA = std::identity, typename ProjB = std::identity>
            requires(!std::ranges::range<A> &&
                     type_traits::comparable_eq<std::invoke_result_t<ProjA, A>, std::invoke_result_t<ProjB, B>>)
        CheckResult compareEQ(const A&                    lhs,
                              const B&                    rhs,
                              ProjA                       projectA = std::identity{},
                              ProjB                       projectB = std::identity{},
                              const std::source_location& loc      = std::source_location::current())
        {
            const auto  res   = compare_eq(projectA(lhs), projectB(rhs));
            std::string error = res == result_t::success ? "" : std::format("{0} == {1}", toString(lhs), toString(rhs));
            return recordResult(res, loc, std::move(error));
        }

        /**
         * \brief lhs[0] == rhs[0], ..., lhs[n] == rhs[n]. Compare the elements of two ranges for equality.
         * \tparam Length If true, mismatching lengths result in a failure. If false, the extra elements of the longest range are ignored.
         * \tparam A Type of left-hand side.
         * \tparam B Type of right-hand side.
         * \tparam ProjA Projection function type for lhs.
         * \tparam ProjB Projection function type for rhs.
         * \param lhs Left-hand side of comparison.
         * \param rhs Right-hand side of comparison.
         * \param projectLhs Projection function type to be applied to elements of lhs.
         * \param projectRhs Projection function type to be applied to elements of rhs.
         * \param loc Automatic source_location.
         * \return Result.
         */
        template<RequireEqualLength         Length = RequireEqualLength::True,
                 std::ranges::forward_range A,
                 std::ranges::forward_range B,
                 typename ProjA = std::identity,
                 typename ProjB = std::identity>
            requires(
              type_traits::comparable_eq<std::invoke_result_t<ProjA, typename std::ranges::iterator_t<A>::value_type>,
                                         std::invoke_result_t<ProjB, typename std::ranges::iterator_t<B>::value_type>>)
        CheckResult compareEQ(const A&                    lhs,
                              const B&                    rhs,
                              ProjA                       projectLhs = std::identity{},
                              ProjB                       projectRhs = std::identity{},
                              const std::source_location& loc        = std::source_location::current())
        {
            // Limit iterations to 4 billion in the case of infinite ranges.
            constexpr size_t limit = 1ull << 32;

            auto       it0  = std::ranges::begin(lhs);
            auto       it1  = std::ranges::begin(rhs);
            const auto end0 = std::ranges::end(lhs);
            const auto end1 = std::ranges::end(rhs);

            // If supported, get size of ranges.
            std::string size0 = "?";
            std::string size1 = "?";
            if constexpr (std::ranges::sized_range<A>) size0 = std::to_string(std::distance(it0, end0));
            if constexpr (std::ranges::sized_range<B>) size1 = std::to_string(std::distance(it1, end1));

            size_t i = 0;
            while (i < limit)
            {
                // Reached end of one of the ranges.
                if (it0 == end0 || it1 == end1)
                {
                    // Matching sizes.
                    if (it0 == end0 && it1 == end1) return recordResult(result_t::success, loc, "");

                    // Mismatching sizes.
                    if constexpr (Length == RequireEqualLength::True)
                        return recordResult(
                          result_t::failure, loc, std::format("length lhs[{0}] != length rhs[{1}]", size0, size1));
                    // Don't care.
                    else
                        return recordResult(result_t::success, loc, "");
                }

                const auto res = compare_eq(projectLhs(*it0), projectRhs(*it1));
                if (res != result_t::success)
                {
                    std::string error =
                      std::format("{1} == {2} at index {0}", i, toString(projectLhs(*it0)), toString(projectRhs(*it1)));
                    return recordResult(res, loc, std::move(error));
                }

                ++it0;
                ++it1;
                ++i;
            }

            return recordResult(result_t::failure, loc, std::format("range comparison exceeded limit {}", limit));
        }

        /**
         * \brief lhs == rhs[0], ..., lhs == rhs[n]. Compare a single value to the elements of a range for equality.
         * \tparam A Type of left-hand side.
         * \tparam B Type of right-hand side.
         * \tparam ProjA Projection function type for lhs.
         * \tparam ProjB Projection function type for rhs.
         * \param lhs Left-hand side of comparison.
         * \param rhs Right-hand side of comparison.
         * \param projectLhs Projection function type to be applied to elements of lhs.
         * \param projectRhs Projection function type to be applied to elements of rhs.
         * \param loc Automatic source_location.
         * \return Result.
         */
        template<typename A,
                 std::ranges::forward_range B,
                 typename ProjA = std::identity,
                 typename ProjB = std::identity>
            requires(
              type_traits::comparable_eq<A,
                                         std::invoke_result_t<ProjB, typename std::ranges::iterator_t<B>::value_type>>)
        CheckResult compareEQ(const A&                    lhs,
                              const B&                    rhs,
                              ProjA&&                     projectLhs = std::identity{},
                              ProjB&&                     projectRhs = std::identity{},
                              const std::source_location& loc        = std::source_location::current())
        {
            return compareEQ<RequireEqualLength::False>(
              std::views::repeat(lhs), rhs, std::forward<ProjA>(projectLhs), std::forward<ProjB>(projectRhs), loc);
        }

        /**
         * \brief lhs[0] == rhs, ..., lhs[0] == rhs. Compare a single value to the elements of a range for equality.
         * \tparam A Type of left-hand side.
         * \tparam B Type of right-hand side.
         * \tparam ProjA Projection function type for lhs.
         * \tparam ProjB Projection function type for rhs.
         * \param lhs Left-hand side of comparison.
         * \param rhs Right-hand side of comparison.
         * \param projectLhs Projection function type to be applied to elements of lhs.
         * \param projectRhs Projection function type to be applied to elements of rhs.
         * \param loc Automatic source_location.
         * \return Result.
         */
        template<std::ranges::forward_range A,
                 typename B,
                 typename ProjA = std::identity,
                 typename ProjB = std::identity>
            requires(
              type_traits::comparable_eq<std::invoke_result_t<ProjA, typename std::ranges::iterator_t<A>::value_type>,
                                         B>)
        CheckResult compareEQ(const A&                    lhs,
                              const B&                    rhs,
                              ProjA&&                     projectLhs = std::identity{},
                              ProjB&&                     projectRhs = std::identity{},
                              const std::source_location& loc        = std::source_location::current())
        {
            return compareEQ<RequireEqualLength::False>(
              lhs, std::views::repeat(rhs), std::forward<ProjA>(projectLhs), std::forward<ProjB>(projectRhs), loc);
        }

        /**
         * \brief lhs != rhs. Compare two values for inequality.
         * \tparam A Type of left-hand side.
         * \tparam B Type of right-hand side.
         * \param lhs Left-hand side of comparison.
         * \param rhs Right-hand side of comparison.
         * \param loc Automatic source_location.
         * \return Result.
         */
        template<typename A, typename B>
            requires(type_traits::comparable_ne<A, B>)
        CheckResult
          compareNE(const A& lhs, const B& rhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_ne(lhs, rhs);
            std::string error = res == result_t::success ? "" : std::format("{0} != {1}", toString(lhs), toString(rhs));
            return recordResult(res, loc, std::move(error));
        }

        /**
         * \brief lhs < rhs. Compare two values.
         * \tparam A Type of left-hand side.
         * \tparam B Type of right-hand side.
         * \param lhs Left-hand side of comparison.
         * \param rhs Right-hand side of comparison.
         * \param loc Automatic source_location.
         * \return Result.
         */
        template<typename A, typename B>
            requires(type_traits::comparable_lt<A, B>)
        CheckResult
          compareLT(const A& lhs, const B& rhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_lt(lhs, rhs);
            std::string error = res == result_t::success ? "" : std::format("{0} < {1}", toString(lhs), toString(rhs));
            return recordResult(res, loc, std::move(error));
        }

        /**
         * \brief lhs > rhs. Compare two values.
         * \tparam A Type of left-hand side.
         * \tparam B Type of right-hand side.
         * \param lhs Left-hand side of comparison.
         * \param rhs Right-hand side of comparison.
         * \param loc Automatic source_location.
         * \return Result.
         */
        template<typename A, typename B>
            requires(type_traits::comparable_gt<A, B>)
        CheckResult
          compareGT(const A& lhs, const B& rhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_gt(lhs, rhs);
            std::string error = res == result_t::success ? "" : std::format("{0} > {1}", toString(lhs), toString(rhs));
            return recordResult(res, loc, std::move(error));
        }

        /**
         * \brief lhs <= rhs. Compare two values.
         * \tparam A Type of left-hand side.
         * \tparam B Type of right-hand side.
         * \param lhs Left-hand side of comparison.
         * \param rhs Right-hand side of comparison.
         * \param loc Automatic source_location.
         * \return Result.
         */
        template<typename A, typename B>
            requires(type_traits::comparable_le<A, B>)
        CheckResult
          compareLE(const A& lhs, const B& rhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_le(lhs, rhs);
            std::string error = res == result_t::success ? "" : std::format("{0} <= {1}", toString(lhs), toString(rhs));
            return recordResult(res, loc, std::move(error));
        }

        /**
         * \brief lhs >= rhs. Compare two values.
         * \tparam A Type of left-hand side.
         * \tparam B Type of right-hand side.
         * \param lhs Left-hand side of comparison.
         * \param rhs Right-hand side of comparison.
         * \param loc Automatic source_location.
         * \return Result.
         */
        template<typename A, typename B>
            requires(type_traits::comparable_ge<A, B>)
        CheckResult
          compareGE(const A& lhs, const B& rhs, const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_ge(lhs, rhs);
            std::string error = res == result_t::success ? "" : std::format("{0} >= {1}", toString(lhs), toString(rhs));
            return recordResult(res, loc, std::move(error));
        }

        /**
         * \brief lower <[=] middle <[=] upper. Compare middle value with lower and upper.
         * \tparam LowerInclusive If true, do lower <= middle. If false, do power < middle.
         * \tparam UpperInclusive If true, do middle <= upper. If false, do middle < upper.
         * \tparam A Type of lower.
         * \tparam B Type of middle.
         * \tparam C Type of upper.
         * \param lower Lower value of comparison.
         * \param middle Middle value of comparison.
         * \param upper Upper value of comparison.
         * \param loc Automatic source_location.
         * \return Result.
         */
        template<bool LowerInclusive = true,
                 bool UpperInclusive = true,
                 typename A          = nullptr_t,
                 typename B          = nullptr_t,
                 typename C          = nullptr_t>
            requires(type_traits::comparable_between<A, B, C, LowerInclusive, UpperInclusive>)
        CheckResult compareBetween(const A&                    lower,
                                   const B&                    middle,
                                   const C&                    upper,
                                   const std::source_location& loc = std::source_location::current())
        {
            const auto  res   = compare_between<A, B, C, LowerInclusive, UpperInclusive>(lower, middle, upper);
            std::string error = res == result_t::success ? "" :
                                                           std::format("{0} {1} {2} {3} {4}",
                                                                       toString(lower),
                                                                       LowerInclusive ? "<=" : "<",
                                                                       toString(middle),
                                                                       UpperInclusive ? "<=" : "<",
                                                                       toString(upper));
            return recordResult(res, loc, std::move(error));
        }
    };

    constexpr CompareMixin::RequireEqualLength RequireEqualLength   = CompareMixin::RequireEqualLength::True;
    constexpr CompareMixin::RequireEqualLength NoRequireEqualLength = CompareMixin::RequireEqualLength::False;
}  // namespace bt
