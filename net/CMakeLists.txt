cmake_minimum_required(VERSION 2.8)

project(smart_getway_net)


SET(CMAKE_CXX_FLAGS "-Wall -O3 -g")
ADD_DEFINITIONS(-std=c++11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

add_library(${PROJECT_NAME} SHARED src/smart_getway_net.cpp)

target_link_libraries(${PROJECT_NAME} stdc++ pthread smart_getway_init smart_getway_merge)

target_include_directories(${PROJECT_NAME} PUBLIC include)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIB_PREFIX})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDE_PREFIX}/net
  FILES_MATCHING PATTERN "*.h")