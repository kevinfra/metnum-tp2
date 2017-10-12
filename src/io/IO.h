#ifndef METNUM_TP2_IO_H
#define METNUM_TP2_IO_H

#include <fstream>
#include "../matrix/Matrix.h"
#include "../matrix/FullMatrix.h"

#define IMG_W 28
#define IMG_H 28
#define IMG_SIZE IMG_W * IMG_H

template < typename T>
struct TrainCase {
    vector<T> img;
    unsigned char digit;
};

typedef unsigned char Pixel;

template < typename T>
using TestSet = vector<vector<T>>;

template < typename T>
using TrainSet = vector<TrainCase<T>>;

namespace IO {

    template < typename T >
    vector<T> split(const std::string& s, char delimiter) {
        size_t prev = 0;
        size_t next = 0;
        std::string token;
        vector<T> v(IMG_SIZE, static_cast<T>(0));
        for (size_t i = 0; i < IMG_SIZE; ++i) {
            next = s.find(delimiter, prev);
            token = s.substr(prev, next - prev);
            v[i] = T(std::stoi(token));
            prev = next + 1;
        }
        return v;
    }

    template < typename T >
    MatrixRef<T> splitAndParse(const std::string& s, char delimiter) {
        size_t prev = 0;
        size_t next = 0;
        std::string token;
        MatrixRef<T> m = std::make_shared<FullMatrix<T>>(IMG_H, IMG_W);
        for (size_t i = 0; i < IMG_H; ++i) {
            for (size_t j = 0; j < IMG_W; ++j) {
                next = s.find(delimiter, prev);
                token = s.substr(prev, next - prev);
                (*m)[i][j] = T(std::stoi(token));
                prev = next + 1;
            }
        }
        return m;
    }

    template < typename T >
    TrainSet<T> loadTrainSet(std::ifstream& file) {
        TrainSet<T> set;
        std::string line;
        std::getline(file, line);
        while(std::getline(file, line)) {
            size_t digitEnd = line.find(',');
            unsigned char digit = std::stoi(line.substr(0, digitEnd));
            line.erase(0, digitEnd + 1);
            set.push_back({IO::split<T>(line, ','), digit});
        }
        return set;
    }

    template < typename T >
    TestSet<T> loadTestSet(std::ifstream& file) {
        TestSet<T> set;
        std::string line;
        std::getline(file, line);
        while(std::getline(file, line)) {
            set.push_back(IO::split<T>(line, ','));
        }
        return set;
    }

    void clearFile(const std::string& fn);
}


#endif //METNUM_TP2_IO_H
