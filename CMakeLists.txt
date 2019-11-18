cmake_minimum_required( VERSION 2.8 )
project ( produce-calc )

set( CMAKE_CXX_COMPILER "g++" )
set( CMAKE_BUILD_TYPE "Release" )
set( CMAKE_CXX_FLAGS "-std=c++11 -march=native -O3" )

set( execName objectcalc)

# OpenCV
find_package( OpenCV 3.1 REQUIRED )
include_directories( ${OpenCV_INCLUDE_DIRS} )


 ADD_EXECUTABLE(${execName} demov1.cpp)
add_definitions(-std=c++11 -g -O3 )

link_directories(${OpenCV_LIBRARY_DIRS})
target_link_libraries(${execName} ${OpenCV_LIBS})

