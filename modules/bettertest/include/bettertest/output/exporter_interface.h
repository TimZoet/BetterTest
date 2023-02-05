#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <filesystem>
#include <memory>
#include <string>

namespace bt
{
    class IExporter;
    class IUnitTest;
    class TestSuite;

    using IExporterPtr = std::unique_ptr<IExporter>;

    /**
     * \brief The IExporter class defines the interface that all exporters need to implement.
     */
    class IExporter
    {
    public:
        IExporter() = delete;

        IExporter(const IExporter&) = delete;

        IExporter(IExporter&&) = delete;

        explicit IExporter(std::filesystem::path path);

        virtual ~IExporter() = default;

        IExporter& operator=(const IExporter&) = delete;

        IExporter& operator=(IExporter&&) = delete;

        /**
         * \brief Write the main test suite file.
         * \param suite The test suite object.
         */
        virtual void writeSuite(const TestSuite& suite) = 0;

        /**
         * \brief Write unit test results.
         * \param suite The test suite object.
         * \param test The unit test object.
         * \param name The name of the unit test.
         */
        virtual void writeUnitTestResults(const TestSuite& suite, const IUnitTest& test, const std::string& name) = 0;

    protected:
        /**
         * \brief Output directory.
         */
        std::filesystem::path path;
    };

    
}  // namespace bt
