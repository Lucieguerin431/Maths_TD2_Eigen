cmake_minimum_required(VERSION 3.13)


# give a name to the project
project(poly LANGUAGES C CXX)

# include Eigen
find_package(Eigen3 REQUIRED)
if(${EIGEN3_FOUND})
    message(STATUS "lib EIGEN3 found")
    message(STATUS "  version " ${EIGEN3_VERSION_STRING})
    message(STATUS "  include " ${EIGEN3_INCLUDE_DIR})
else()
    message(FATAL_ERROR "lib EIGEN3 not found")
endif()


# files to compile
add_executable(poly src/main.cpp src/Polynomial.cpp src/Polynomial.hpp)

# compilation flags
target_compile_features(poly PRIVATE cxx_std_11) # use at least c++ 11
target_compile_options(poly PRIVATE -Wall -O2)   # specify some compilation flags

# lib include path
target_include_directories(poly PRIVATE "${EIGEN3_INCLUDE_DIR}")


