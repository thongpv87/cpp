cmake_minimum_required(VERSION 3.5)
project(cpp
  VERSION "0.1.0"
  DESCRIPTION "cpp template project"
  LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)

find_package(Boost REQUIRED)

add_executable(main main.cpp)
target_link_libraries(main Boost::headers)
install(TARGETS main
  RUNTIME DESTINATION bin)
