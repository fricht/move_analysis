cmake_minimum_required(VERSION 3.22)
project(moveHighlight)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})
add_executable(main src/main.cpp)
target_link_libraries(main ${OpenCV_LIBS})
