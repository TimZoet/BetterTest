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
    };
}  // namespace bt
