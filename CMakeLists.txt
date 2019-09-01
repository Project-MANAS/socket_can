cmake_minimum_required(VERSION 3.5)
project(socket_can)

find_package(catkin REQUIRED)

include_directories(
  include
)

add_library(
  socket_can
    src/socket_can.cpp
)

install(
  TARGETS socket_can
    ARCHIVE DESTINATION lib/${PROJECT_NAME}
    LIBRARY DESTINATION lib/${PROJECT_NAME}
    RUNTIME DESTINATION lib/${PROJECT_NAME}
)

catkin_package()