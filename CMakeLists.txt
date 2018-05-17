# CMake 最低版本号要求
cmake_minimum_required (VERSION 2.8)
# 项目信息
project (dcos_test)
set(CMAKE_C_FLAGS "-Wall -O2 -g")

set(CMAKE_INSTALL_PREFIX "${PROJECT_BINARY_DIR}/install")
set(CMAKE_INSTALL_CONF_PREFIX "${CMAKE_INSTALL_PREFIX}/etc")
set(CMAKE_INSTALL_BIN_PREFIX "${CMAKE_INSTALL_PREFIX}/bin")
set(CMAKE_INSTALL_LIB_PREFIX "${CMAKE_INSTALL_PREFIX}/lib")
set(CMAKE_INSTALL_INCLUDE_PREFIX "${CMAKE_INSTALL_PREFIX}/include")
set(CMAKE_INSTALL_SRC_PREFIX "${CMAKE_INSTALL_PREFIX}/sample")


add_subdirectory(log)
add_subdirectory(struct2json)
add_subdirectory(validation)
add_subdirectory(parse)
add_subdirectory(init)
add_subdirectory(forward)
add_subdirectory(core)


install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDE_PREFIX}
  FILES_MATCHING PATTERN "*.h")
  install(FILES config/smart_getway_config.json config/smart_getway_log.conf DESTINATION ${CMAKE_INSTALL_CONF_PREFIX}
  PERMISSIONS
  OWNER_WRITE OWNER_READ
  GROUP_READ GROUP_WRITE
  WORLD_READ WORLD_WRITE)
  #install(FILES release_how_to/update_dcos_test.sh DESTINATION ${CMAKE_INSTALL_PREFIX}
  #PERMISSIONS
  #OWNER_WRITE OWNER_READ
  #GROUP_READ GROUP_WRITE
  #WORLD_READ WORLD_WRITE)

