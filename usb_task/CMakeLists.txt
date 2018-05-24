cmake_minimum_required(VERSION 2.8)

project(smart_getway_usb_task)


SET(CMAKE_CXX_FLAGS "-Wall -O3 -g")
ADD_DEFINITIONS(-std=c++11)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
find_package(OpenCV REQUIRED)

include_directories(${OpenCV_INCLUDE_DIRS})

add_library(${PROJECT_NAME} SHARED src/smart_getway_usb_cam.cpp)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} stdc++ pthread smart_getway_parse smart_getway_init)

target_include_directories(${PROJECT_NAME} PUBLIC include)

install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_LIB_PREFIX})

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDE_PREFIX}/usb_task
  FILES_MATCHING PATTERN "*.h")