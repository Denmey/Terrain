cmake_minimum_required(VERSION 3.5)

project(GLAD)
set(CMAKE_CXX_STANDARD 17)

add_library(GLAD
  source/glad.c
  include/glad.h
  include/khrplatform.h
)

target_include_directories(GLAD PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/include)
# target_link_libraries(GLAD PUBLIC)
install(EXPORT GLADTargets FILE GLADTargets.cmake
  EXPORT_LINK_INTERFACE_LIBRARIES
  DESTINATION "${CMAKE_INSTALL_LIBDIR}/cmake/GLAD"
)

install(TARGETS GLAD
  EXPORT GLADTargets
  RUNTIME DESTINATION "bin"
  ARCHIVE DESTINATION "${CMAKE_INSTALL_LIBDIR}"
  LIBRARY DESTINATION "${CMAKE_INSTALL_LIBDIR}"
)