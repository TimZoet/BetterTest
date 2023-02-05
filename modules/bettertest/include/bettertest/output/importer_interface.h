#pragma once

////////////////////////////////////////////////////////////////
// Standard includes.
////////////////////////////////////////////////////////////////

#include <filesystem>
#include <memory>

namespace bt
{
    class IImporter;
    class ITest;
    class TestSuite;

    using IImporterPtr = std::unique_ptr<IImporter>;

    /**
     * \brief The IImporter class defines the interface that all importers need to implement.
     */
    class IImporter
    {
    public:
        IImporter() = delete;

        IImporter(const IImporter&) = delete;

        IImporter(IImporter&&) = delete;

        explicit IImporter(std::filesystem::path path);

        virtual ~IImporter() = default;

        IImporter& operator=(const IImporter&) = delete;

        IImporter& operator=(IImporter&&) = delete;

        /**
         * \brief Read the main test suite file, if it exists.
         * \param suite The test suite object.
         * \return True if the file existed, false if not.
         */
        virtual bool readSuite(TestSuite& suite) = 0;

    protected:
        /**
         * \brief Output directory.
         */
        std::filesystem::path path;
    };
}  // namespace bt
