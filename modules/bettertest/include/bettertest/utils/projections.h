#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <memory>
#include <optional>

namespace bt::proj
{
    /**
     * \brief Projection function for converting a const optional<T>& to a const T&.
     * \tparam T Element type.
     */
    template<typename T>
    constexpr auto optional_to_ref = [](const std::optional<T>& opt) -> const T& { return *opt; };

    /**
     * \brief Projection function for converting a const optional<T>& to a const T*.
     * \tparam T Element type.
     */
    template<typename T>
    constexpr auto optional_to_raw_ptr = [](const std::optional<T>& opt) -> const T* { return &*opt; };

    /**
     * \brief Projection function for converting a const unique_ptr<T>& to a const T&.
     * \tparam T Element type.
     */
    template<typename T>
    constexpr auto unique_ptr_to_ref = [](const std::unique_ptr<T>& ptr) -> const T& { return *ptr; };

    /**
     * \brief Projection function for converting a const unique_ptr<T>& to a const T*.
     * \tparam T Element type.
     */
    template<typename T>
    constexpr auto unique_ptr_to_raw_ptr = [](const std::unique_ptr<T>& ptr) -> const T* { return ptr.get(); };

    /**
     * \brief Projection function for converting a const shared_ptr<T>& to a const T&.
     * \tparam T Element type.
     */
    template<typename T>
    constexpr auto shared_ptr_to_ref = [](const std::shared_ptr<T>& ptr) -> const T& { return *ptr; };

    /**
     * \brief Projection function for converting a const shared_ptr<T>& to a const T*.
     * \tparam T Element type.
     */
    template<typename T>
    constexpr auto shared_ptr_to_raw_ptr = [](const std::shared_ptr<T>& ptr) -> const T* { return ptr.get(); };
}  // namespace bt::proj
