cmake_minimum_required(VERSION 3.5)
project(esp32_serial)

# Default to C99
if(NOT CMAKE_C_STANDARD)
  set(CMAKE_C_STANDARD 99)
endif()

# Default to C++14
if(NOT CMAKE_CXX_STANDARD)
  set(CMAKE_CXX_STANDARD 14)
endif()

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_COMPILER_ID MATCHES "Clang")
  add_compile_options(-Wall -Wextra -Wpedantic)
endif()

include_directories(include)

# find dependencies
find_package(ament_cmake REQUIRED)
find_package(rclcpp REQUIRED)
find_package(std_msgs REQUIRED)
find_package(Boost 1.71.0 REQUIRED system)

find_package(sensor_msgs REQUIRED)

add_executable(esp32_serial_exe src/esp32_serial_node.cpp)


ament_target_dependencies(esp32_serial_exe rclcpp std_msgs sensor_msgs)

install(TARGETS esp32_serial_exe
  DESTINATION lib/${PROJECT_NAME})


install(DIRECTORY
  launch
  DESTINATION share/${PROJECT_NAME}/
)

ament_package()
