#include "bettertest/run.h"

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <algorithm>
#include <iostream>
#include <unordered_map>

////////////////////////////////////////////////////////////////
// Module includes.
////////////////////////////////////////////////////////////////

#include "parsertongue/parser.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/exceptions/better_test_error.h"

namespace bt::internal
{
    void initialize() { bt::registerSuiteData<SuiteData>(); }

    using SuiteData_t = std::unordered_map<std::string, suite_data_callback_t>;
    using Exporters_t = std::unordered_map<std::string, TestSuite::exporter_callback_t>;
    using Importers_t = std::unordered_map<std::string, TestSuite::importer_callback_t>;

    SuiteData_t& suiteDatas()
    {
        static SuiteData_t sd;
        return sd;
    }

    Exporters_t& exporters()
    {
        static Exporters_t exp;
        return exp;
    }

    Importers_t& importers()
    {
        static Importers_t imp;
        return imp;
    }

    void registerSuiteData(const std::string& type, suite_data_callback_t constructor)
    {
        if (suiteDatas().contains(type))
            throw BetterTestError("A suite data type with this name was already registered");

        suiteDatas()[type] = std::move(constructor);
    }

    void registerExporter(const std::string& type, TestSuite::exporter_callback_t constructor)
    {
        if (exporters().contains(type)) throw BetterTestError("An exporter with this name was already registered");

        exporters()[type] = std::move(constructor);
    }

    void registerImporter(const std::string& type, TestSuite::importer_callback_t constructor)
    {
        if (importers().contains(type)) throw BetterTestError("An importer with this name was already registered");

        importers()[type] = std::move(constructor);
    }

    bool parse(const int argc, char** argv, TestSuite& suite)
    {
        ////////////////////////////////////////////////////////////////
        // Create parser.
        ////////////////////////////////////////////////////////////////

        pt::parser parser(argc, argv);

        const auto data = parser.add_value<std::string>('\0', "data");
        data->set_default("default");

        const auto failing = parser.add_flag('f', "failing");
        failing->set_help("Run failing tests.", "If this flag is enabled, only failing tests are run.");

        const auto format = parser.add_value<std::string>('\0', "format");
        format->set_default("json");

        const auto multithreaded = parser.add_flag('m', "multithreaded");
        multithreaded->set_help("Run tests in parallel.");

        const auto outdir = parser.add_value<std::filesystem::path>('o', "outdir");
        outdir->set_default(std::filesystem::current_path() / (suite.getName() + std::string(".dir")));
        outdir->set_help("Path to directory in which test data is stored.");

        /*auto performance = parser.add_list<std::string>('p', "performance");
        performance->set_help(
          "List of name patterns. Only performance tests whose name matches one of the patterns is run.");*/

        const auto unit = parser.add_list<std::string>('u', "unit");
        unit->set_help("List of name patterns. Only unit tests whose name matches one of the patterns is run.");

        const auto verbose = parser.add_flag('\0', "verbose");
        verbose->set_help("");

        ////////////////////////////////////////////////////////////////
        // Run.
        ////////////////////////////////////////////////////////////////

        // Run parser.
        if (std::string e; !parser(e))
        {
            std::cout << "Internal parsing error: " << e << std::endl;
            return false;
        }

        // Display help and errors.
        if (parser.display_help(std::cout)) return false;
        if (!parser.get_errors().empty() && verbose->is_set())
        {
            parser.display_errors(std::cout);
            return false;
        }

        ////////////////////////////////////////////////////////////////
        // Process.
        ////////////////////////////////////////////////////////////////

        if (const auto& operators = parser.get_operands(); !operators.empty())
        {
            if (operators.front() == "info")
            {
                std::cout << suite.getName() << std::endl;
                std::cout << outdir->get_value().string() << std::endl;
                return false;
            }
        }

        // Create suite data object.
        const auto dataFormat = suiteDatas().find(data->get_value());
        if (dataFormat == suiteDatas().end())
        {
            std::cout << "Could not find suite data format " << data->get_value() << std::endl;
            return false;
        }
        suite.setData(dataFormat->second());

        // Pass failing flag.
        suite.setRunFailingOnly(failing->is_set());

        // Create exporters and importers.
        const auto exporter = exporters().find(format->get_value());
        const auto importer = importers().find(format->get_value());
        if (exporter == exporters().end())
        {
            std::cout << "Could not find exporter " << format->get_value() << std::endl;
            return false;
        }
        if (importer == importers().end())
        {
            std::cout << "Could not find importer " << format->get_value() << std::endl;
            return false;
        }
        suite.setOutputDirectory(outdir->get_value());
        suite.setExporterFunction(exporter->second);
        suite.setImporterFunction(importer->second);

        // Enable multithreading.
        if (multithreaded->is_set()) suite.setMultithreaded(true);

        // performance

        // Pass unit test filter to test suite.
        if (unit->is_set()) suite.setUnitTestFilter(unit->get_values());

        // verbose

        return true;
    }
}  // namespace bt::internal
