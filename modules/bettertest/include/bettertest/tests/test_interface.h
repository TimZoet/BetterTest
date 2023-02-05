#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <concepts>
#include <memory>




namespace bt
{
    class ITest
    {
    public:
        ITest() = default;

        ITest(const ITest&) = delete;

        ITest(ITest&&) = delete;

        virtual ~ITest() = default;

        ITest& operator=(const ITest&) = delete;

        ITest& operator=(ITest&&) = delete;

        [[nodiscard]] virtual bool passing() const noexcept = 0;

        virtual void operator()() = 0;
    };

    template<typename T>
    concept IsITest = std::derived_from<T, ITest>;

    using ITestPtr = std::unique_ptr<ITest>;
}  // namespace bt
