#pragma once

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/mixins/mixin_interface.h"

namespace bt
{
    class InvalidCodeMixin : public IMixin
    {
    public:
        InvalidCodeMixin() = default;

        InvalidCodeMixin(const InvalidCodeMixin&) = delete;

        InvalidCodeMixin(InvalidCodeMixin&&) = delete;

        virtual ~InvalidCodeMixin() = default;

        InvalidCodeMixin& operator=(const InvalidCodeMixin&) = delete;

        InvalidCodeMixin& operator=(InvalidCodeMixin&&) = delete;

        ////////////////////////////////////////////////////////////////
        // Getters.
        ////////////////////////////////////////////////////////////////

        [[nodiscard]] bool isPassing() const noexcept override;

        [[nodiscard]] std::string getName() const override { return "invalidCode"; }
    
    protected:
        ////////////////////////////////////////////////////////////////
        // Export.
        ////////////////////////////////////////////////////////////////
        
        void exportResults(nlohmann::json& data) const override;

        void exportResults(pugi::xml_node& node) const override;

        ////////////////////////////////////////////////////////////////
        // Checks.
        ////////////////////////////////////////////////////////////////

        template<typename T, template<typename> typename C>
        requires(C<T>::value) void invalidCode()
        {
            tests++;
        }

        template<typename T, template<typename> typename C>
        requires(!C<T>::value) void invalidCode()
        {
            tests++;
            rejections++;
        }

    private:
        size_t tests      = 0;
        size_t rejections = 0;
    };
}  // namespace bt
