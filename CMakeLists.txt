## Set up the CMake project.
cmake_minimum_required(VERSION 3.10.2)
project(elevation_map VERSION 0.0.1 LANGUAGES CXX)

## Set the C++ standard.
set(CMAKE_CXX_STANDARD 17)

## Enable all compiler warnings and treat them as errors.
add_compile_options(-Wall -Wextra -Wpedantic)

# Include headers.
include_directories(
  ${CMAKE_CURRENT_SOURCE_DIR}/include
)

if (CATKIN_ENABLE_TESTING)
  find_package(GTest REQUIRED)
endif()

# Declare library.
add_library(${PROJECT_NAME} SHARED
  src/${PROJECT_NAME}/ElevationMap.cpp
)


## Declare executable / tests / etc
if (CATKIN_ENABLE_TESTING)
  add_executable(test_elevation_map test/test_elevation_map.cpp)
  target_link_libraries(test_elevation_map
    ${catkin_LIBRARIES}
    ${GTEST_LIBRARIES}
    ${PROJECT_NAME}
    pthread
  )
endif()