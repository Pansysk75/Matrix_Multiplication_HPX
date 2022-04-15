# CMakeList.txt : CMake project for Matrix_Multiplication_HPX, include source and define
# project specific logic here.
#
cmake_minimum_required (VERSION 3.8)

project ("Matrix_Multiplication_HPX")

# Add source to this project's executable.
add_executable (Matrix_Multiplication_HPX "main.cpp"  "Matrix.h" "Matrix_Operations.h")

# TODO: Add tests and install targets if needed.

find_package(HPX REQUIRED)
target_link_libraries(Matrix_Multiplication_HPX HPX::hpx HPX::wrap_main)
