set(NAME testapp)
set(TYPE test)
set(INCLUDE_DIR "include/testapp")
set(SRC_DIR "src")

set(HEADERS
	${INCLUDE_DIR}/tests.h
)
 
set(SOURCES
	${SRC_DIR}/tests.cpp
	${SRC_DIR}/main.cpp
)

set(DEPS_PRIVATE
	bettertest
)

make_target(TYPE ${TYPE} NAME ${NAME} OUTDIR "tests" STARTUP HEADERS "${HEADERS}" SOURCES "${SOURCES}" DEPS_PRIVATE "${DEPS_PRIVATE}")