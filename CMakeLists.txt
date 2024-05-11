cmake_minimum_required(VERSION 3.15)

project(terminal_3d_projection)

add_library(compiler_flags INTERFACE)
target_compile_features(compiler_flags INTERFACE cxx_std_11)

add_subdirectory(terminal_3d_projection)