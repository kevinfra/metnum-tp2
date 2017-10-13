#include "MachineFactory.h"
#include "KnnMachine.h"
#include "KnnPcaMachine.h"

namespace MachineFactory {

    MachineRef create(Implementation impl) {
        switch(impl) {
            case kNN:
                return std::make_shared<KnnMachine>();
            case kNNPCA:
                return std::make_shared<KnnPcaMachine>();
            default:
                throw std::runtime_error("Unknown implementation!");
        }
    }
}