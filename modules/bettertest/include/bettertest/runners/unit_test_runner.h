#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <sstream>
#include <string>
#include <utility>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/exceptions/check_fatal_error.h"
#include "bettertest/output/exporter_interface.h"
#include "bettertest/runners/test_runner_interface.h"
#include "bettertest/tests/unit_test.h"
#include "bettertest/utils/class_name.h"

namespace bt
{
    /**
     * \brief When invoked, the UnitTestRunner creates and runs a unit test of the given type.
     * \tparam T UnitTest.
     */
    template<IsUnitTest T>
    class UnitTestRunner final : public ITestRunner
    {
    public:
        using test_t = T;

        UnitTestRunner()
        {
            if constexpr (hasExplicitName<T>)
                setTestName(std::string(T::template name));
            else
                setTestName(getPrettyClassName<T>());
        }

        UnitTestRunner(const UnitTestRunner&) = default;

        UnitTestRunner(UnitTestRunner&&) = default;

        ~UnitTestRunner() noexcept override = default;

        UnitTestRunner& operator=(const UnitTestRunner&) = default;

        UnitTestRunner& operator=(UnitTestRunner&&) = default;

        std::pair<bool, std::string>
          operator()(const TestSuite& suite, IExporter& exporter, std::ostream& out) noexcept override
        {
            bool              passing = false;
            std::stringstream error;

            // Try to run test.
            T t;
            try
            {
                t.setOutput(out);
                t();
                passing = t.passing();
            }

            // Catch any exceptions.
            catch (const CheckFatalError& e)
            {
                error << "Test terminated because of failed check: "
                      << (e.getMessage().empty() ? "<no message>" : e.getMessage());
            }
            catch (const BetterTestError& e)
            {
                error << "BetterTestError: " << e.what();
            }
            catch (const std::exception& e)
            {
                error << "Exception: " << e.what();
            }
            catch (...)
            {
                error << "An unknown error occurred";
            }

            // Write test results.
            exporter.writeUnitTestResults(suite, t, getTestName());

            return std::make_pair(passing, error.str());
        }

        /**
         * \brief Returns whether the test held by this runner can run in parallel. If not, it will always run serialized.
         * \return True or false.
         */
        [[nodiscard]] bool isParallel() const noexcept override
        {
            // If test has a static member isParallel, use that to determine if test can run in parallel.
            // Otherwise, default to true.
            if constexpr (requires(test_t) { test_t::isParallel; })
                return test_t::isParallel;
            else
                return true;
        }
    };
}  // namespace bt
