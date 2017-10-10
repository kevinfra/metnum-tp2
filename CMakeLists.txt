cmake_minimum_required(VERSION 2.6)
project(metnum-tp2)

set(SOURCE_FILES
        src/matrix/Matrix.h
        src/matrix/FullMatrix.h
        src/matrix/SparseMatrix.h
        src/matrix/SymmetricMatrix.h
        src/Vectors.h
        src/Methods.cpp
        src/Methods.h
        src/knn.h
        src/pca.h
        src/io/IO.h
        src/io/MatrixIterator.h
        src/io/TrainSetIterator.h
        src/pipeline/Pipeline.h
        src/pipeline/PipelineFactory.cpp
        src/pipeline/PipelineFactory.h
        src/pipeline/KnnPipeline.h
        src/parameters.cpp
        src/parameters.h
        src/SortedKList.h
        src/benchmark/benchmark.h)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++11 -Wall -pedantic")

add_library(metnum-tp2-base ${SOURCE_FILES})

add_executable(tp2 src/main.cpp)
target_link_libraries (tp2 metnum-tp2-base)

add_subdirectory(test)
