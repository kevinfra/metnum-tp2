#ifndef METNUM_TP2_BENCHMARK_H
#define METNUM_TP2_BENCHMARK_H

#define NOP (static_cast<void>(0));

// (un)comment to toggle benchmark tests
//#define BENCH

#ifdef BENCH

    #include <chrono>
    #include <fstream>

    #define BENCH_NOW std::chrono::high_resolution_clock::now()
    #define BENCH_UNIT std::chrono::nanoseconds

    #define INIT_BENCH(f) {\
        std::ofstream file(f, std::ofstream::out | std::ofstream::trunc);\
        file << "t" << std::endl;\
    }

    #define START_BENCH auto start = BENCH_NOW;
    #define END_BENCH(f) {\
        auto end = BENCH_NOW; \
        auto diff = std::chrono::duration_cast< BENCH_UNIT >(end - start).count(); \
        std::ofstream file(f, std::ofstream::out | std::ofstream::app);\
        file << diff << std::endl;\
    }

#else

    #define INIT_BENCH(f) NOP
    #define START_BENCH NOP
    #define END_BENCH(f) NOP

#endif

#endif //METNUM_TP2_BENCHMARK_H
