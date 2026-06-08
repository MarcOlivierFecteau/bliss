cmake_minimum_required(VERSION 3.8)
project(bliss)

# ccache for faster rebuilds
find_program(CCACHE_PROGRAM ccache)
if (CCACHE_PROGRAM)
  set(CMAKE_CXX_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
  set(CMAKE_C_COMPILER_LAUNCHER "${CCACHE_PROGRAM}")
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

if (NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

if (NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 17)
endif()

find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(sensor_msgs REQUIRED)
find_package(bliss_msgs REQUIRED)

include_directories(include)

add_executable(bliss_node src/main.cpp)
ament_target_dependencies(bliss_node
  rclcpp
  std_msgs
  sensor_msgs
  bliss_msgs
)

install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/launch
)

install(DIRECTORY
  config
  DESTINATION share/${PROJECT_NAME}/config
)

install(TARGETS
  bliss_node
  DESTINATION lib/${PROJECT_NAME}
)

if(BUILD_TESTING)
  find_package(ament_lint_auto REQUIRED)
  set(ament_cmake_cpplint_FOUND TRUE)
  ament_lint_auto_find_test_dependencies()
endif()

ament_package()
