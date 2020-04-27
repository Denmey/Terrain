cmake_minimum_required(VERSION 3.5 FATAL_ERROR)

project(TerrainStandalone
  LANGUAGES CXX
)

# ---- Dependencies ----

include(../../cmake/CPM.cmake)

# CPMAddPackage(
#   NAME cxxopts
#   GITHUB_REPOSITORY jarro2783/cxxopts
#   VERSION 2.2.0
#   OPTIONS
#     "CXXOPTS_BUILD_EXAMPLES Off"
#     "CXXOPTS_BUILD_TESTS Off"
# )

CPMAddPackage(
  NAME Terrain
  SOURCE_DIR ${CMAKE_CURRENT_LIST_DIR}/../..
)

# ---- Create standalone executable ----

file(GLOB sources CONFIGURE_DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp)

add_executable(TerrainStandalone ${sources})

set_target_properties(TerrainStandalone PROPERTIES 
  CXX_STANDARD 17 
  OUTPUT_NAME "Terrain"
)

# target_link_libraries(TerrainStandalone Terrain cxxopts)
target_link_libraries(TerrainStandalone Terrain)
# file(COPY Resources 
#   DESTINATION ${CMAKE_BINARY_DIR}
# )
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E echo "Copying resources"
)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${CMAKE_COMMAND} -E copy_directory
    ${CMAKE_SOURCE_DIR}/Resources
    $<TARGET_FILE_DIR:TerrainStandalone>/Resources
)