cmake_minimum_required(VERSION 2.8)

project(smart_getway_forward)


SET(CMAKE_CXX_FLAGS "-Wall -O3 -g")  

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} SHARED src/smart_getway_forward.cpp)

target_link_libraries(${PROJECT_NAME} stdc++ pthread smart_getway_init)

target_include_directories(${PROJECT_NAME} PUBLIC include)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIB_PREFIX})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDE_PREFIX}/forward
  FILES_MATCHING PATTERN "*.h")