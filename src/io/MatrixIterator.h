#ifndef METNUM_TP2_MATRIXITERATOR_H
#define METNUM_TP2_MATRIXITERATOR_H

#include <fstream>
#include "../matrix/Matrix.h"
#include "IO.h"

template < typename T >
class MatrixIterator {
public:
    MatrixIterator(std::ifstream& f) : file(f), end(false)  {
        // go back to beginning of file
        file.clear();
        file.seekg(0, std::ios::beg);
        // drop csv header
        std::string junk;
        std::getline(file, junk);
        step();
    }

    void operator++() {
        step();
    }

    MatrixRef<T> operator*() {
        return cur;
    }

    bool hasNext() {
        return !end;
    }

private:
    std::ifstream& file;
    MatrixRef<T> cur;
    bool end;

    void step() {
        std::string line;
        if(std::getline(file, line)) {
            cur = IO::splitAndParse<T>(line, ',');
        } else {
            end = true;
        }
    }
};


#endif //METNUM_TP2_MATRIXITERATOR_H
