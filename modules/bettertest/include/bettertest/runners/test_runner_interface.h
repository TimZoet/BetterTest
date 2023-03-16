#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <concepts>
#include <memory>
#include <ostream>
#include <string>
#include <utility>

namespace bt
{
    class IExporter;
    class TestSuite;

    /**
     * \brief The ITestRunner defines the interface that all test runners need to implement. When invoked, it should create and run the test it holds.
     */
    class ITestRunner
    {
    public:
        ITestRunner() = default;

        ITestRunner(const ITestRunner&) = default;

        ITestRunner(ITestRunner&&) = default;

        virtual ~ITestRunner() = default;

        ITestRunner& operator=(const ITestRunner&) = default;

        ITestRunner& operator=(ITestRunner&&) = default;

        /**
         * \brief Create and run the test associated with this runner.
         * \return Passing state of the test and optional error message if a fatal error occurred.
         */
        virtual std::pair<bool, std::string>
          operator()(const TestSuite& suite, IExporter& exporter, std::ostream&) noexcept = 0;

        /**
         * \brief Get the name of the test this runner holds.
         * \return Test name.
         */
        [[nodiscard]] const std::string& getTestName() const noexcept;

        /**
         * \brief Returns whether the test held by this runner can run in parallel. If not, it will always run serialized.
         * \return True or false.
         */
        [[nodiscard]] virtual bool isParallel() const noexcept = 0;

    protected:
        /**
         * \brief Set the name of the test this runner holds.
         * \param name Test name.
         */
        void setTestName(std::string name);

    private:
        /**
         * \brief Name of the test this runner holds.
         */
        std::string testName;
    };

    using ITestRunnerPtr = std::unique_ptr<ITestRunner>;

    // clang-format off
    template<typename T>
    concept hasExplicitName = requires
    {
        { T::name } -> std::convertible_to<std::string>;
    };
    // clang-format on
}  // namespace bt
