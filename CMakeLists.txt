cmake_minimum_required(VERSION 3.27)
project(SudokuSolverCPP)

find_package(JNI REQUIRED)
include_directories(${JNI_INCLUDE_DIRS} ${CMAKE_CURRENT_SOURCE_DIR}/lib)

set(CMAKE_CXX_STANDARD 17)

add_library(SudokuSolverCPP SHARED
        SudokuSolverJNI.cpp)
target_link_libraries(SudokuSolverCPP ${CMAKE_CURRENT_SOURCE_DIR}/lib/libSudokuSolver.dylib)
