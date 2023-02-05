#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <string>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/runners/test_runner_interface.h"
#include "bettertest/tests/performance_test.h"
#include "bettertest/utils/class_name.h"

namespace bt
{
    template<IsPerformanceTest T>
    class PerformanceTestRunner final : public ITestRunner
    {
    public:
        PerformanceTestRunner()
        {
            if constexpr (hasExplicitName<T>)
                setTestName(std::string(T::template name));
            else
                setTestName(getPrettyClassName<T>());
        }

        PerformanceTestRunner(const PerformanceTestRunner&) = default;

        PerformanceTestRunner(PerformanceTestRunner&&) = default;

        ~PerformanceTestRunner() noexcept override = default;

        PerformanceTestRunner& operator=(const PerformanceTestRunner&) = default;

        PerformanceTestRunner& operator=(PerformanceTestRunner&&) = default;

        std::pair<bool, std::string> operator()(const TestSuite&, IExporter&, std::ostream&) noexcept override
        {
            // Access this to shut up static analysis for now.
            static_cast<void>(this);

            return std::make_pair(false, std::string());
#if 0
            try
            {
                T t;
                t();
                exporter.writePerformanceTestFile(t, getTestName());
                return t.passing();
            }
            catch (std::exception& e)
            {
                return false;
            }
#endif
        }
    };
}  // namespace bt
