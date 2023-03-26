#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <filesystem>
#include <functional>
#include <string>

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/output/exporter_interface.h"
#include "bettertest/output/importer_interface.h"
#include "bettertest/suite/suite_data.h"
#include "bettertest/suite/test_suite.h"
#ifdef BETTERTEST_BUILD_ALEXANDRIA
#include "bettertest_alexandria/alexandria_exporter.h"
#include "bettertest_alexandria/alexandria_importer.h"
#endif
#ifdef BETTERTEST_BUILD_JSON
#include "bettertest_json/json_exporter.h"
#include "bettertest_json/json_importer.h"
#endif
#ifdef BETTERTEST_BUILD_XML
#include "bettertest_xml/xml_exporter.h"
#include "bettertest_xml/xml_importer.h"
#endif

namespace bt::internal
{
    using suite_data_callback_t = std::function<SuiteDataPtr()>;

    void initialize();

    void registerSuiteData(const std::string& type, suite_data_callback_t constructor);

    void registerExporter(const std::string& type, TestSuite::exporter_callback_t constructor);

    void registerImporter(const std::string& type, TestSuite::importer_callback_t constructor);

    inline void registerBuiltinOutputFormats()
    {
#ifdef BETTERTEST_BUILD_ALEXANDRIA
        registerExporter(AlexandriaExporter::type,
                         [](const std::filesystem::path& p) { return std::make_unique<AlexandriaExporter>(p); });
        registerImporter(AlexandriaExporter::type,
                         [](const std::filesystem::path& p) { return std::make_unique<AlexandriaImporter>(p); });
#endif
#ifdef BETTERTEST_BUILD_JSON
        registerExporter(JsonExporter::type,
                         [](const std::filesystem::path& p) { return std::make_unique<JsonExporter>(p); });
        registerImporter(JsonImporter::type,
                         [](const std::filesystem::path& p) { return std::make_unique<JsonImporter>(p); });
#endif
#ifdef BETTERTEST_BUILD_XML
        registerExporter(XmlExporter::type,
                         [](const std::filesystem::path& p) { return std::make_unique<XmlExporter>(p); });
        registerImporter(XmlImporter::type,
                         [](const std::filesystem::path& p) { return std::make_unique<XmlImporter>(p); });
#endif
    }

    /**
     * \brief Adds a UnitTestRunner to the TestSuite.
     * \tparam T UnitTest type.
     * \param suite TestSuite.
     */
    template<IsUnitTest T>
    void addRunner(TestSuite& suite)
    {
        auto runner = std::make_unique<UnitTestRunner<T>>();
        suite.addUnitTest(std::move(runner));
    }

    /**
     * \brief Adds a PerformanceTestRunner to the TestSuite.
     * \tparam T PerformanceTest type.
     * \param suite TestSuite.
     */
    template<IsPerformanceTest T>
    void addRunner(TestSuite& suite)
    {
        auto runner = std::make_unique<PerformanceTestRunner<T>>();
        suite.addPerformanceTest(std::move(runner));
    }

    /**
     * \brief Adds TestRunners to the TestSuite.
     * \tparam T Test type.
     * \tparam Ts Test types.
     * \param suite TestSuite.
     */
    template<IsITest T, IsITest... Ts>
    void addRunners(TestSuite& suite)
    {
        addRunner<T>(suite);
        if constexpr (sizeof...(Ts) > 0) addRunners<Ts...>(suite);
    }

    bool parse(int argc, char** argv, TestSuite& suite);
}  // namespace bt::internal

namespace bt
{
    /**
     * \brief Register a new suite data type.
     * \tparam T Class deriving from SuiteData.
     */
    template<std::derived_from<SuiteData> T>
    void registerSuiteData()
    {
        internal::registerSuiteData(T::type, []() { return std::make_unique<T>(); });
    }

    /**
     * \brief Register a new output format.
     * \tparam I Class deriving from IImporter.
     * \tparam E Class deriving from IExporter.
     * \param name Name of the output format.
     */
    template<std::derived_from<IImporter> I, std::derived_from<IExporter> E>
    void registerOutputFormat(const std::string& name)
    {
        internal::registerImporter(name, [](const std::filesystem::path& p) { return std::make_unique<I>(p); });
        internal::registerExporter(name, [](const std::filesystem::path& p) { return std::make_unique<E>(p); });
    }

    /**
     * \brief Run all tests that are passed to this function.
     * \tparam T Test type.
     * \tparam Ts Test types.
     * \param argc 
     * \param argv 
     * \param suiteName Test suite name.
     */
    template<IsITest T, IsITest... Ts>
    int32_t run(const int argc, char** argv, const std::string suiteName)
    {
        try
        {
            internal::registerBuiltinOutputFormats();
            internal::initialize();

            // Create suite.
            TestSuite suite(suiteName);

            // Add all tests.
            internal::addRunners<T, Ts...>(suite);

            // Parse command line arguments.
            if (!internal::parse(argc, argv, suite)) return 1;

            // Run suite.
            suite();

            return suite.getData().passing ? 1 : 0;
        }
        catch (...)
        {
            return 1;
        }
    }
}  // namespace bt
