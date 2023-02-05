#include "bettertest/output/exporter_interface.h"

namespace bt
{
    IExporter::IExporter(std::filesystem::path path) : path(std::move(path)) {}
}