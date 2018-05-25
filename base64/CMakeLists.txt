cmake_minimum_required(VERSION 2.8)

project(base64)

set(CMAKE_C_FLAGS "-Wall -O2 -g")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


add_library(${PROJECT_NAME} SHARED src/base64.c)

target_link_libraries(${PROJECT_NAME} )

target_include_directories(${PROJECT_NAME} PUBLIC include)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIB_PREFIX})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDE_PREFIX}/base64
  FILES_MATCHING PATTERN "*.h")
