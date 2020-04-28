cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

# ---- Project ----

# Note: update this to your new project's name and version
project(Terrain 
  VERSION 0.1
  LANGUAGES CXX
)

# ---- Include guards ----

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR "In-source builds not allowed. Please make a new directory (called a build directory) and run CMake from there.")
endif()

# --- Import tools ----

include(cmake/tools.cmake)

# ---- Add dependencies via CPM ----
# see https://github.com/TheLartians/CPM.cmake for more info

include(cmake/CPM.cmake)

# PackageProject.cmake will be used to make our target installable
CPMAddPackage(
  NAME PackageProject.cmake
  GITHUB_REPOSITORY TheLartians/PackageProject.cmake
  VERSION 1.2
)

add_subdirectory(extern/glad)

CPMFindPackage(
  NAME glfw3
  GITHUB_REPOSITORY glfw/glfw
  GIT_TAG 3.3.2
  OPTIONS
    "GLFW_BUILD_EXAMPLES Off"
    "GLFW_BUILD_TESTS Off"
    "GLFW_BUILD_DOCS Off"
)

CPMFindPackage(
  NAME glm
  GITHUB_REPOSITORY g-truc/glm
  GIT_TAG 0.9.9.8
  DOWNLOAD_ONLY YES
)

if (glm_ADDED)
  set(glm_DIR ${glm_SOURCE_DIR}/cmake/glm)
  find_package(glm REQUIRED)
endif()

# ---- Add source files ----

# Note: globbing sources is considered bad practice as CMake's generators may not detect new files automatically.
# Keep that in mind when changing files, or explicitly mention them here.
FILE(GLOB_RECURSE headers CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/include/*.hpp")
FILE(GLOB_RECURSE sources CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/source/*.cpp")

# ---- Create library ----

# Note: for header-only libraries change all PUBLIC flags to INTERFACE and create an interface target:
# add_library(Terrain INTERFACE)  
# set_target_properties(Terrain PROPERTIES INTERFACE_COMPILE_FEATURES cxx_std_17)

add_library(Terrain ${headers} ${sources})

set_target_properties(Terrain PROPERTIES CXX_STANDARD 17)

# beeing a cross-platform target, we enforce enforce standards conformance on MSVC
target_compile_options(Terrain PUBLIC "$<$<BOOL:${MSVC}>:/permissive->")

# Link dependencies (if required)
target_link_libraries(Terrain PUBLIC glfw GLAD ${CMAKE_DL_LIBS})
target_include_directories(Terrain PUBLIC 
  $<BUILD_INTERFACE:${GLM_INCLUDE_DIRS}>
)

target_include_directories(Terrain
  PUBLIC
    $<BUILD_INTERFACE:${PROJECT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include/${PROJECT_NAME}-${PROJECT_VERSION}>
)

# ---- Create an installable target ----
# this allows users to install and find the library via `find_package()`.

packageProject(
  NAME ${PROJECT_NAME}
  VERSION ${PROJECT_VERSION}
  BINARY_DIR ${PROJECT_BINARY_DIR}
  INCLUDE_DIR ${PROJECT_SOURCE_DIR}/include
  INCLUDE_DESTINATION include/${PROJECT_NAME}-${PROJECT_VERSION}
  DEPENDENCIES "glfw3;GLAD"
)
