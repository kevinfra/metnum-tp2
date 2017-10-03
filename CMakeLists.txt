cmake_minimum_required(VERSION 2.6)
project(metnum-tp2)

set(SOURCE_FILES
        src/matrix/Matrix.h
        src/matrix/FullMatrix.h
        src/matrix/SparseMatrix.h
        src/matrix/SymmetricMatrix.h
        src/Vectors.h
        src/knn.cpp
        src/Methods.cpp
        src/Methods.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

add_library(metnum-tp2-base ${SOURCE_FILES})

add_executable(main src/main.cpp src/Methods.cpp src/Methods.h)
target_link_libraries (main metnum-tp2-base)

add_subdirectory(test)
