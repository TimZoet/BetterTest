#include "bettertest/output/importer_interface.h"

////////////////////////////////////////////////////////////////
// Current target includes.
////////////////////////////////////////////////////////////////

#include "bettertest/suite/test_suite.h"

namespace bt
{
    IImporter::IImporter(std::filesystem::path path) : path(std::move(path)) {}
}  // namespace bt