find_package(common REQUIRED)
find_package(date REQUIRED)
find_package(ParserTongue REQUIRED)

include(bettertestVersionString)

option(BETTERTEST_BUILD_ALEXANDRIA "Build Alexandria exporter/importer" OFF)
option(BETTERTEST_BUILD_JSON "Build JSON exporter/importer" OFF)
option(BETTERTEST_BUILD_XML "Build XML exporter/importer" OFF)

set(NAME bettertest)
set(TYPE module)
set(INCLUDE_DIR "include/bettertest")
set(SRC_DIR "src")

set(HEADERS
    ${INCLUDE_DIR}/exceptions/better_test_error.h
    ${INCLUDE_DIR}/exceptions/check_fatal_error.h
    ${INCLUDE_DIR}/exceptions/export_error.h
    ${INCLUDE_DIR}/exceptions/import_error.h

    ${INCLUDE_DIR}/mixins/compare_mixin.h
    ${INCLUDE_DIR}/mixins/exception_mixin.h
    # ${INCLUDE_DIR}/mixins/invalid_code_mixin.h
    ${INCLUDE_DIR}/mixins/mixin_interface.h
    ${INCLUDE_DIR}/mixins/mixin_results_getter.h

    ${INCLUDE_DIR}/output/exporter_interface.h
    ${INCLUDE_DIR}/output/importer_interface.h

    ${INCLUDE_DIR}/runners/performance_test_runner.h
    ${INCLUDE_DIR}/runners/test_runner_interface.h
    ${INCLUDE_DIR}/runners/unit_test_runner.h

    ${INCLUDE_DIR}/suite/performance_test_suite.h
    ${INCLUDE_DIR}/suite/suite_data.h
    ${INCLUDE_DIR}/suite/test_data.h
    ${INCLUDE_DIR}/suite/test_suite.h
    ${INCLUDE_DIR}/suite/unit_test_suite.h

    ${INCLUDE_DIR}/tests/performance_test.h
    ${INCLUDE_DIR}/tests/test_interface.h
    ${INCLUDE_DIR}/tests/unit_test.h
    ${INCLUDE_DIR}/tests/unit_test_interface.h

    ${INCLUDE_DIR}/utils/check_result.h
    ${INCLUDE_DIR}/utils/class_name.h
    ${INCLUDE_DIR}/utils/compare.h
    ${INCLUDE_DIR}/utils/date.h
    ${INCLUDE_DIR}/utils/hashing.h
    ${INCLUDE_DIR}/utils/name_filter.h
    ${INCLUDE_DIR}/utils/projections.h
    ${INCLUDE_DIR}/utils/result.h
    ${INCLUDE_DIR}/utils/to_string.h
    ${INCLUDE_DIR}/utils/try.h
    ${INCLUDE_DIR}/utils/type_traits.h
    ${INCLUDE_DIR}/utils/version.h

    ${INCLUDE_DIR}/run.h
)
 
set(SOURCES
    ${SRC_DIR}/exceptions/better_test_error.cpp
    ${SRC_DIR}/exceptions/check_fatal_error.cpp
    ${SRC_DIR}/exceptions/export_error.cpp
    ${SRC_DIR}/exceptions/import_error.cpp

    ${SRC_DIR}/mixins/compare_mixin.cpp
    ${SRC_DIR}/mixins/exception_mixin.cpp
    # ${SRC_DIR}/mixins/invalid_code_mixin.cpp
    ${SRC_DIR}/mixins/mixin_interface.cpp

    ${SRC_DIR}/output/exporter_interface.cpp
    ${SRC_DIR}/output/importer_interface.cpp

    ${SRC_DIR}/runners/test_runner_interface.cpp

    ${SRC_DIR}/suite/performance_test_suite.cpp
    ${SRC_DIR}/suite/suite_data.cpp
    ${SRC_DIR}/suite/test_data.cpp
    ${SRC_DIR}/suite/test_suite.cpp
    ${SRC_DIR}/suite/unit_test_suite.cpp

    ${SRC_DIR}/utils/check_result.cpp
    ${SRC_DIR}/utils/compare.cpp
    ${SRC_DIR}/utils/date.cpp
    ${SRC_DIR}/utils/name_filter.cpp
    ${SRC_DIR}/utils/version.cpp

    ${SRC_DIR}/run.cpp
)

set(DEPS_PUBLIC
    common::common
)

set(DEPS_PRIVATE
    date::date
    parsertongue::parsertongue
)

make_target(
    NAME ${NAME}
    TYPE ${TYPE}
    VERSION ${BETTERTEST_VERSION}
    WARNINGS WERROR
    HEADERS "${HEADERS}"
    SOURCES "${SOURCES}"
    DEPS_PUBLIC "${DEPS_PUBLIC}"
    DEPS_PRIVATE "${DEPS_PRIVATE}"
)

install_target(
    NAME ${NAME}
    TYPE ${TYPE}
    VERSION ${BETTERTEST_VERSION}
    HEADERS "${HEADERS}"
)

target_compile_definitions(
    ${NAME}
    PRIVATE
        BETTERTEST_VERSION_MAJOR=${BETTERTEST_VERSION_MAJOR}
        BETTERTEST_VERSION_MINOR=${BETTERTEST_VERSION_MINOR}
        BETTERTEST_VERSION_PATCH=${BETTERTEST_VERSION_PATCH}
)
