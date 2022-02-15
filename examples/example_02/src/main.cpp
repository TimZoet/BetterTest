#include "bettertest/run.h"
#include "bettertest/mixins/compare_mixin.h"
#include "bettertest/tests/unit_test.h"
#include "bettertest_alexandria/alexandria_exporter.h"
#include "bettertest_alexandria/alexandria_importer.h"
#include "bettertest_json/json_exporter.h"
#include "bettertest_json/json_importer.h"
#include "bettertest_xml/xml_exporter.h"
#include "bettertest_xml/xml_importer.h"

class UnitTest01 : public bt::UnitTest<UnitTest01, bt::CompareMixin>
{
public:
    void operator()() override
    {
        compareEQ(42, 42);
        compareLT(10, 20);
        compareBetween(0, 200, 100);
    }
};

int main(int argc, char** argv)
{
    bt::registerExporter<bt::AlexandriaExporter>();
    bt::registerImporter<bt::AlexandriaImporter>();
    bt::registerExporter<bt::JsonExporter>();
    bt::registerImporter<bt::JsonImporter>();
    bt::registerExporter<bt::XmlExporter>();
    bt::registerImporter<bt::XmlImporter>();
    bt::run<UnitTest01>(argc, argv, "myFirstTestSuite");
    return 0;
}