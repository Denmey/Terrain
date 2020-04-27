cmake_minimum_required(VERSION 3.5)

project(GLAD)
set(CMAKE_CXX_STANDARD 17)

add_library(GLAD
  source/glad.c
  include/glad.h
  include/khrplatform.h
)

target_include_directories(GLAD PUBLIC # ${CMAKE_CURRENT_SOURCE_DIR}/include
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
  $<INSTALL_INTERFACE:include>  # <prefix>/include
)

# target_link_libraries(GLAD PUBLIC)

# TODO: install workflow failing to find GLAD
# TODO: CMAKE_INSTALL_LIBDIR is empty?
# MESSAGE(STATUS "CMAKE_INSTALL_LIBDIR: " $<INSTALL_PREFIX>)


install(EXPORT GLADTargets FILE GLADTargets.cmake
  EXPORT_LINK_INTERFACE_LIBRARIES
  # DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/GLAD"
  DESTINATION "lib/cmake/GLAD"
)

install(TARGETS GLAD
  EXPORT GLADTargets
  RUNTIME DESTINATION "bin"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)

# Copy headers 
install(
  FILES 
    ${PROJECT_SOURCE_DIR}/include/glad.h 
    ${PROJECT_SOURCE_DIR}/include/khrplatform.h 
  DESTINATION include # TODO: Move to include/GLAD directory
)

# Generating config file
include(CMakePackageConfigHelpers)
write_basic_package_version_file(
  "${CMAKE_CURRENT_BINARY_DIR}/GLADConfigVersion.cmake"
  VERSION 0.1.33
  COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
  ${PROJECT_SOURCE_DIR}/Config.cmake.in
  "${CMAKE_CURRENT_BINARY_DIR}/GLADConfig.cmake"
  INSTALL_DESTINATION "lib/cmake/GLAD"
)

# Install config file
install(
  FILES 
    "${CMAKE_CURRENT_BINARY_DIR}/GLADConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/GLADConfigVersion.cmake"
  DESTINATION "lib/cmake/GLAD")

# export(TARGETS GLAD FILE GLADTargets.cmake)
