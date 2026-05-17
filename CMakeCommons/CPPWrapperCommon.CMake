if(NOT DEFINED TP_DEBUG)
    set(TP_DEBUG 0)
endif()

file(GLOB_RECURSE incSources "${CMAKE_CURRENT_SOURCE_DIR}/include/*.h*")

TP_add_interface_subdirectory(${TEAPACKET_WRAPPER_CPP_MODULE})

add_library(${PROJECT_NAME} INTERFACE ${incSources})
set_target_properties(${PROJECT_NAME} PROPERTIES LINKER_LANGUAGE CXX)
target_include_directories(${PROJECT_NAME} INTERFACE "${CMAKE_CURRENT_SOURCE_DIR}/include")
target_compile_definitions(${PROJECT_NAME} INTERFACE ${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} INTERFACE TeaPacket_${TEAPACKET_WRAPPER_CPP_MODULE}_Base)
include("${TEAPACKET_ROOT}/CMakeCommons/CommonEnd.CMake")

if ((MSVC) AND (MSVC_VERSION GREATER_EQUAL 1914))
    target_compile_options(${PROJECT_NAME} INTERFACE "/Zc:__cplusplus")
endif()