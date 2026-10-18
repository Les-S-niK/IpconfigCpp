cmake_minimum_required(VERSION 3.15)
set(PROJECT_NAME "ipconfig")

project(${PROJECT_NAME} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 26)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

option(TESTS "Enable tests" OFF)

if(TESTS)
  find_package(GTest)
  enable_testing()
  include(GoogleTest)
  add_executable(IpconfigTests ./tests/)
  target_include_directories(IpconfigTests PUBLIC ./include/)
  target_link_libraries(IpconfigTests PRIVATE GTest::gtest GTest::gtest_main)
  add_test(NAME IpconfigTests COMMAND IpconfigTests)
else()
  add_executable(${PROJECT_NAME} main.cpp)

  target_include_directories(
    ${PROJECT_NAME}
    PUBLIC $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
           $<INSTALL_INTERFACE:include>)
endif()
