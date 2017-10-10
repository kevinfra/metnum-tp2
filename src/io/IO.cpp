#include "IO.h"

namespace IO {
    void clearFile(const std::string& fn) {
        std::ofstream file(fn, std::ofstream::out | std::ofstream::trunc);
    }
}