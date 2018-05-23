cmake_minimum_required(VERSION 2.8)

project(smart_getway)

set(CMAKE_C_FLAGS "-Wall -O2 -g")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

include_directories(/usr/local/include/smart_getway )
link_directories(/usr/local/lib/smart_getway )

add_executable(smart_getway src/smart_getway.c)
target_link_libraries(smart_getway smart_getway_forward smart_getway_validation struct2json pthread smart_getway_init smart_getway_parse smart_getway_log)
target_include_directories(${PROJECT_NAME} PUBLIC include)
install(TARGETS ${PROJECT_NAME} DESTINATION ${CMAKE_INSTALL_BIN_PREFIX})
