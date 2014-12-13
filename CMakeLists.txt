cmake_minimum_required(VERSION 2.8)
project(Synthetics)
add_subdirectory(src)

enable_testing()

SET(ENV(CTEST_OUTPUT_ON_FAILURE) YES)
