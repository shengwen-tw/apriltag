cmake_minimum_required(VERSION 2.8)
project(apriltag)

IF(NOT CMAKE_BUILD_TYPE)
  SET(CMAKE_BUILD_TYPE Debug)
ENDIF()

MESSAGE("Build type: " ${CMAKE_BUILD_TYPE})

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Ofast -march=native -mmmx -msse -msse -msse2 -msse3 -mssse3 -funroll-loops")

# Check C++11 or C++0x support
include(CheckCXXCompilerFlag)
CHECK_CXX_COMPILER_FLAG("-std=c++11" COMPILER_SUPPORTS_CXX11)
CHECK_CXX_COMPILER_FLAG("-std=c++0x" COMPILER_SUPPORTS_CXX0X)

if(COMPILER_SUPPORTS_CXX11)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11")
  add_definitions(-DCOMPILEDWITHC11)
  message(STATUS "Using flag -std=c++11.")
elseif(COMPILER_SUPPORTS_CXX0X)
  set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++0x")
  add_definitions(-DCOMPILEDWITHC0X)
  message(STATUS "Using flag -std=c++0x.")
else()
  message(FATAL_ERROR "The compiler ${CMAKE_CXX_COMPILER} has no C++11 support. Please use a different C++ compiler.")
endif()

find_package( OpenCV 3.2 REQUIRED )
find_package(Eigen3 REQUIRED)

set(LIB_APRILTAG "${PROJECT_SOURCE_DIR}/libapriltags/src")

include_directories(
  ${OpenCV_INCLUDE_DIRS} 
  ${EIGEN3_INCLUDE_DIR}
  ${PROJECT_SOURCE_DIR}/libapriltags/include
  ${PROJECT_SOURCE_DIR}/libapriltags/include/AprilTags
)

add_library(${PROJECT_NAME} SHARED
  ${LIB_APRILTAG}/Edge.cc
  ${LIB_APRILTAG}/Gaussian.cc
  ${LIB_APRILTAG}/GLineSegment2D.cc
  ${LIB_APRILTAG}/Homography33.cc
  ${LIB_APRILTAG}/Quad.cc
  ${LIB_APRILTAG}/TagDetection.cc
  ${LIB_APRILTAG}/TagFamily.cc
  ${LIB_APRILTAG}/FloatImage.cc
  ${LIB_APRILTAG}/GLine2D.cc
  ${LIB_APRILTAG}/GrayModel.cc
  ${LIB_APRILTAG}/MathUtil.cc
  ${LIB_APRILTAG}/Segment.cc
  ${LIB_APRILTAG}/TagDetector.cc
  ${LIB_APRILTAG}/UnionFindSimple.cc
)

target_link_libraries(${PROJECT_NAME} ${OpenCV_LIBS} ${EIGEN3_LIBS})
add_executable(apriltag_exe ${PROJECT_SOURCE_DIR}/main.cpp)
target_link_libraries(apriltag_exe  ${PROJECT_NAME})
