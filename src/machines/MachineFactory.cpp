#include "MachineFactory.h"
#include "KnnMachine.h"
#include "KnnPcaMachine.h"

namespace MachineFactory {

    MachineRef create(const parameters &p) {
        switch(p.method) {
            case kNN:
                return std::make_shared<KnnMachine>(p.k);
            case kNNPCA:
                return std::make_shared<KnnPcaMachine>(p.k, p.alfa);
            default:
                throw std::runtime_error("Unknown implementation!");
        }
    }
}