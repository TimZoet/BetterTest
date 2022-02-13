set(NAME example_01)
set(TYPE application)
set(INCLUDE_DIR "include/example_01")
set(SRC_DIR "src")

set(HEADERS
)
 
set(SOURCES
	${SRC_DIR}/main.cpp
)

set(DEPS_PRIVATE
	bettertest
    bettertest_json
    bettertest_xml
)

make_target(NAME ${NAME} TYPE ${TYPE} EXAMPLE HEADERS "${HEADERS}" SOURCES "${SOURCES}" DEPS_PRIVATE "${DEPS_PRIVATE}")