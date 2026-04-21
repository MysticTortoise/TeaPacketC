if(NOT DEFINED TP_DEBUG)
    set(TP_DEBUG 0)
endif()

set(CMAKE_C_STANDARD 90)

file(GLOB_RECURSE incSources "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h*")

add_library(${PROJECT_NAME} INTERFACE ${incSources})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE C)
target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
message("${PROJECT_NAME}")
include("${CMAKE_CURRENT_LIST_DIR}/CommonEnd.CMake")