# William Wu, 2013-05-20 10:04
include_directories (${reverse_byte_ordering_SOURCE_DIR}/src)
link_directories (${reverse_byte_ordering_BINARY_DIR}/src)
set (CORELIBS  )
add_executable (reverse_byte_ordering reverse_byte_ordering.c)
target_link_libraries (reverse_byte_ordering ${CORELIBS} )
# for debugging --- print out all variable names:
# get_cmake_property(_variableNames VARIABLES)
# foreach (_variableName ${_variableNames})
#    message(STATUS "${_variableName}=${${_variableName}}")
# endforeach()
