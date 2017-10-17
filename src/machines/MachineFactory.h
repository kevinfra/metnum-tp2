#ifndef METNUM_TP2_MACHINEFACTORY_H
#define METNUM_TP2_MACHINEFACTORY_H

#include "Machine.h"
#include "../parameters.h"

typedef std::shared_ptr<Machine> MachineRef;

namespace MachineFactory {

    enum Implementation : unsigned char { kNN, kNNPCA, IMPL_COUNT };

    MachineRef create(const parameters &p);
}

#endif //METNUM_TP2_MACHINEFACTORY_H
