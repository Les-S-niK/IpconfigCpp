cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "ipconfig")

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TESTS "Enable tests" OFF)

if(TESTS)
  find_package(GTest)
  enable_testing()
  include(GoogleTest)

  add_executable(IpconfigTests ./tests/test_network_ifaces.cpp)
  add_library(source_files ./src/network_ifaces.cpp)

  target_include_directories(source_files PUBLIC ./include/)
  target_include_directories(IpconfigTests PUBLIC ./include/)

  target_link_libraries(IpconfigTests PRIVATE GTest::gtest GTest::gtest_main)
  target_link_libraries(IpconfigTests PRIVATE source_files)

  add_test(NAME IpconfigTests COMMAND IpconfigTests)
else()
  add_executable(${PROJECT_NAME} main.cpp)

  add_library(network_ifaces ./src/network_ifaces.cpp)

  target_include_directories(${PROJECT_NAME} PUBLIC ./include/)
  target_include_directories(network_ifaces PUBLIC ./include/)

  target_link_libraries(${PROJECT_NAME} PRIVATE network_ifaces)
endif()
