cmake_minimum_required (VERSION 3.4.1)
option(test "build all test" OFF)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(PROJECT_NAME dynamic_db)
project (${PROJECT_NAME})
find_package(Threads REQUIRED)

#--------------
#module
#--------------
include_directories(include)
file(GLOB SOURCES "src/*.cpp")
add_library(dynamic_db_lib ${SOURCES})
add_executable(dynamic_db main/Dynamic_db.cpp)

target_link_libraries(dynamic_db dynamic_db_lib)

if(test)
add_subdirectory( ${PROJECT_SOURCE_DIR}/lib)
enable_testing()
#include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
include_directories(${GTEST_INCLUDE_DIRS} include)

file(GLOB TEST_SOURCES "test/*.cpp")
add_executable(runUnitTests ${TEST_SOURCES} )
add_dependencies(runUnitTests googletest)

target_link_libraries(runUnitTests dynamic_db_lib)
target_link_libraries(runUnitTests ${GTEST_LIBS_DIR}/libgtest.a ${GTEST_LIBS_DIR}/libgtest_main.a )
target_link_libraries(runUnitTests ${CMAKE_THREAD_LIBS_INIT})



add_test(NAME test1 COMMAND runUnitTests)


endif()
