cmake_minimum_required(VERSION 3.22)
project(options_pricing)

set(CMAKE_CXX_STANDARD 20)

add_executable(options_pricing black_scholes.cpp)
