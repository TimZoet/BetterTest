set(NAME example_02)
set(TYPE application)
set(INCLUDE_DIR "include/example_02")
set(SRC_DIR "src")

set(HEADERS
)
 
set(SOURCES
	${SRC_DIR}/main.cpp
)

set(DEPS_PRIVATE
	bettertest
)

make_target(NAME ${NAME} TYPE ${TYPE} EXAMPLE HEADERS "${HEADERS}" SOURCES "${SOURCES}" DEPS_PRIVATE "${DEPS_PRIVATE}")