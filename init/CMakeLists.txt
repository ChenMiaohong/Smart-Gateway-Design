cmake_minimum_required(VERSION 2.8)

project(smart_getway_init)

set(CMAKE_C_FLAGS "-Wall -O2 -g")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} SHARED src/smart_getway_init.c)

target_link_libraries(${PROJECT_NAME} smart_getway_init smart_getway_parse smart_getway_log)

target_include_directories(${PROJECT_NAME} PUBLIC include)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIB_PREFIX})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDE_PREFIX}/init
  FILES_MATCHING PATTERN "*.h")
