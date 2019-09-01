cmake_minimum_required(VERSION 3.5)
project(socket_can)

find_package(catkin REQUIRED)

catkin_package(
  INCLUDE_DIRS
    include
  LIBRARIES
    socket_can
)

include_directories(
  include
)

add_library(
  socket_can
    src/socket_can.cpp
)

install(
  TARGETS socket_can
    ARCHIVE DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    LIBRARY DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
    RUNTIME DESTINATION ${CATKIN_PACKAGE_LIB_DESTINATION}
)