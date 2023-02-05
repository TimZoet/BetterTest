#include "bettertest/suite/performance_test_suite.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <algorithm>
#include <string>

using namespace std::string_literals;

namespace bt
{
    void PerformanceTestSuite::addTest(ITestRunnerPtr runner) { runners.emplace_back(std::move(runner)); }

    void PerformanceTestSuite::setFilter(const std::vector<std::string>& filters) { filter.addFilters(filters); }

    void PerformanceTestSuite::setRunFailingOnly(const bool run) noexcept { runFailingOnly = run; }

    void PerformanceTestSuite::operator()()
    {
        // Access this to shut up static analysis for now.
        static_cast<void>(this);
#if 0
        resolveTests();

        for (auto& test : data)
        {
            // Skip tests without a runner.
            if (test->runnerIndex >= runners.size()) continue;

            auto& runner = runners[test->runnerIndex];

            // Skip tests that don't match the name pattern.
            if (!filter.match(runner->getTestName(), true)) continue;

            // Skip non-failing tests.
            if (runFailingOnly && test->passing) continue;

            // Run test.
            //results[runner->getTestName()] = {};
            //test.passing                   = (*runner)(results[runner->getTestName()]);
        }
#endif
    }

    auto PerformanceTestSuite::getData() noexcept -> TestData_t& { return data; }

    auto PerformanceTestSuite::getData() const noexcept -> const TestData_t& { return data; }

    void PerformanceTestSuite::resolveTests()
    {
        // Access this to shut up static analysis for now.
        static_cast<void>(this);
#if 0
        // Detect added and deleted tests.
        for (size_t i = 0; i < runners.size(); i++)
        {
            const auto& runner = runners[i];

            // Look for test.
            const auto testName = runner->getTestName();
            auto       it =
              std::find_if(tests.begin(), tests.end(), [&testName](const TestState& t) { return t.name == testName; });

            // Found test, set runner index.
            if (it != tests.end())
            {
                it->state       = TestState::State::Unchanged;
                it->runnerIndex = i;
                continue;
            }

            // Did not find test, create new test state.
            auto& t       = tests.emplace_back();
            t.name        = testName;
            t.state       = TestState::State::Added;
            t.runnerIndex = i;
        }
#endif
    }
}  // namespace bt
