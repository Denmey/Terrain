cmake_minimum_required(VERSION 3.5)

# https://stackoverflow.com/a/49863065

project(GLAD
  LANGUAGES C
)

add_library(GLAD
  source/glad.c
)

target_include_directories(GLAD PUBLIC # ${CMAKE_CURRENT_SOURCE_DIR}/include
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>  
  $<INSTALL_INTERFACE:include>  # <prefix>/include
)

set_target_properties(GLAD PROPERTIES
  VERSION 0.1.33
)

# TODO: install workflow failing to find GLAD

include(GNUInstallDirs)

install(TARGETS GLAD EXPORT GLADConfig
    ARCHIVE  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    LIBRARY  DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME  DESTINATION ${CMAKE_INSTALL_BINDIR})
# install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/GLAD) # TODO: Use this
install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT GLADConfig DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/GLAD)
# install(EXPORT GLADConfig DESTINATION share/MyLib/cmake)

export(TARGETS GLAD FILE GLADConfig.cmake)

# Copy headers 
# install(
#   FILES 
#     ${PROJECT_SOURCE_DIR}/include/glad.h 
#     ${PROJECT_SOURCE_DIR}/include/khrplatform.h 
#   DESTINATION include # TODO: Move to include/GLAD directory
# )

# install(TARGETS GLAD
#   EXPORT GLADTargets
#   RUNTIME DESTINATION "bin"
#   ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
#   LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
# )

# # TODO: CMAKE_INSTALL_LIBDIR is empty?
# # MESSAGE(STATUS "CMAKE_INSTALL_LIBDIR: " $<INSTALL_PREFIX>)
# install(EXPORT GLADTargets FILE GLADTargets.cmake
#   EXPORT_LINK_INTERFACE_LIBRARIES
#   # DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/GLAD"
#   DESTINATION "lib/cmake/GLAD"
# )

# # Generating config file
# include(CMakePackageConfigHelpers)
# write_basic_package_version_file(
#   "${CMAKE_CURRENT_BINARY_DIR}/GLADConfigVersion.cmake"
#   VERSION 0.1.33
#   COMPATIBILITY SameMajorVersion
# )

# configure_package_config_file(
#   ${PROJECT_SOURCE_DIR}/GLADConfig.cmake.in
#   "${CMAKE_CURRENT_BINARY_DIR}/GLADConfig.cmake"
#   INSTALL_DESTINATION "lib/cmake/GLAD"
# )

# # Install config file
# install(
#   FILES 
#     "${CMAKE_CURRENT_BINARY_DIR}/GLADConfig.cmake"
#     "${CMAKE_CURRENT_BINARY_DIR}/GLADConfigVersion.cmake"
#   DESTINATION "lib/cmake/GLAD")

# # export(TARGETS GLAD FILE GLADTargets.cmake)
