
cmake_minimum_required (VERSION 3.8)
project ("Matrix_Multiplication_HPX")
add_executable (Matrix_Multiplication_HPX "main.cpp"  "Matrix.h" "Matrix_Operations.h")
find_package(HPX REQUIRED)
target_link_libraries(Matrix_Multiplication_HPX HPX::hpx HPX::wrap_main)
