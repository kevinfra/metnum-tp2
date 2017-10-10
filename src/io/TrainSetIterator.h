#ifndef METNUM_TP2_TRAINSETITERATOR_H
#define METNUM_TP2_TRAINSETITERATOR_H

#include <fstream>
#include "../matrix/Matrix.h"
#include "IO.h"

template < typename T >
class TrainSetIterator {
public:
    TrainSetIterator(std::ifstream& f) : file(f), end(false) {
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

    TrainCase<T> operator*() {
        return cur;
    }

    bool hasNext() {
        return !end;
    }

private:
    std::ifstream& file;
    TrainCase<T> cur;
    bool end;

    void step() {
        std::string line;
        if(std::getline(file, line)) {
            size_t digitEnd = line.find(',');
            unsigned char digit = std::stoi(line.substr(0, digitEnd));
            line.erase(0, digitEnd + 1);
            cur = {IO::splitAndParse<T>(line, ','), digit};
        } else {
            end = true;
        }
    }
};


#endif //METNUM_TP2_TRAINSETITERATOR_H
