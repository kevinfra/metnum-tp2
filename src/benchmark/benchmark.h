#ifndef METNUM_TP2_BENCHMARK_H
#define METNUM_TP2_BENCHMARK_H

#define NOP (static_cast<void>(0))
#define NOSTREAM if(false) std::cerr

// (un)comment to toggle benchmark tests
#define BENCH

#ifdef BENCH

    #include <chrono>
    #include <fstream>
    #include "../io/IO.h"

    struct BenchHelper {
        BenchHelper(const std::string& fn) : file(fn, std::ofstream::out | std::ofstream::app) {}
        ~BenchHelper() { file << std::endl; }

        std::ofstream file;
    };

    #define BENCH_NOW std::chrono::high_resolution_clock::now()
    #define BENCH_UNIT std::chrono::nanoseconds

    #define INIT_BENCH(f) \
        IO::clearFile(f);\
        BenchHelper(f).file << "t"

    #define START_BENCH auto start = BENCH_NOW

    #define END_BENCH(f) \
        auto end = BENCH_NOW;\
        auto diff = std::chrono::duration_cast< BENCH_UNIT >(end - start).count();\
        BenchHelper(f).file << diff

#else

    #define INIT_BENCH(f) NOSTREAM
    #define START_BENCH NOP
    #define END_BENCH(f) NOSTREAM

#endif

#endif //METNUM_TP2_BENCHMARK_H
