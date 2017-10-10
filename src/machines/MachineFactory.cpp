#include "MachineFactory.h"
#include "KnnMachine.h"

namespace MachineFactory {

    MachineRef create(const parameters& params) {
        switch(params.method) {
            case kNN:
                return std::make_shared<KnnMachine>(params);
            case kNNPCA:
//                return ;
            default:
                throw std::runtime_error("Unknown implementation!");
        }
    }
}