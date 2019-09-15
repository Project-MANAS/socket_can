if($ENV{ROS_VERSION} EQUAL 1)
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
else()
  cmake_minimum_required(VERSION 3.5)
  project(socket_can)

  add_compile_options(-std=c++14)

  find_package(ament_cmake REQUIRED)
  
  include_directories(include)

  add_library(${PROJECT_NAME} STATIC
    src/${PROJECT_NAME}.cpp
  )


  install(
    DIRECTORY include/
    DESTINATION include
  )

  install(
    TARGETS ${PROJECT_NAME}
    ARCHIVE DESTINATION lib
    LIBRARY DESTINATION lib
    RUNTIME DESTINATION bin
  )

  ament_export_include_directories(include)
  ament_export_libraries(${PROJECT_NAME})
  ament_package()

endif()
