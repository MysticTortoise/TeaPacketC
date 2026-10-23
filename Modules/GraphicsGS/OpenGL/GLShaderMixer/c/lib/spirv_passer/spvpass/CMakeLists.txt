add_library(spvpass)

target_include_directories(spvpass PUBLIC include)
target_include_directories(spvpass PRIVATE source)

target_link_libraries(spvpass PUBLIC SPIRV-Tools-opt-PassLib)

add_subdirectory(source)