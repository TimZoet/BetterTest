set(NAME pugixml)
set(TYPE module)
set(INCLUDE_DIR "include/pugixml")
set(SRC_DIR "include/pugixml")

set(HEADERS
	${INCLUDE_DIR}/pugiconfig.hpp
	${INCLUDE_DIR}/pugixml.hpp
)
 
set(SOURCES
	${SRC_DIR}/pugixml.cpp
)

make_target(NAME ${NAME} TYPE ${TYPE} HEADERS "${HEADERS}" SOURCES "${SOURCES}")
