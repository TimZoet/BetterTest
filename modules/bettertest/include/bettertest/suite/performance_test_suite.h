#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <filesystem>
#include <string>
#include <vector>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/runners/performance_test_runner.h"
#include "bettertest/suite/test_data.h"
#include "bettertest/utils/name_filter.h"

namespace bt
{
    class PerformanceTestSuite
    {
    public:
        using TestData_t    = std::vector<TestDataPtr>;
        using TestRunners_t = std::vector<ITestRunnerPtr>;

        PerformanceTestSuite() = default;

        PerformanceTestSuite(const PerformanceTestSuite&) = delete;

        PerformanceTestSuite(PerformanceTestSuite&&) = delete;

        ~PerformanceTestSuite() = default;

        PerformanceTestSuite& operator=(const PerformanceTestSuite&) = delete;

        PerformanceTestSuite& operator=(PerformanceTestSuite&&) = delete;

        void addTest(ITestRunnerPtr runner);

        void setFilter(const std::vector<std::string>& filters);

        void setRunFailingOnly(bool run) noexcept;

        [[nodiscard]] TestData_t& getData() noexcept;

        [[nodiscard]] const TestData_t& getData() const noexcept;

        void operator()();

    private:
        void resolveTests();

        TestData_t    data;
        TestRunners_t runners;
        NameFilter    filter;
        bool          runFailingOnly = false;
    };
}  // namespace bt
