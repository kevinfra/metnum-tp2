#ifndef METNUM_TP2_MACHINEFACTORY_H
#define METNUM_TP2_MACHINEFACTORY_H

#include "Machine.h"
#include "../parameters.h"

typedef std::shared_ptr<Machine> MachineRef;

namespace MachineFactory {

    enum Implementations : unsigned char { kNN, kNNPCA };

    MachineRef create(const parameters& params);
}

#endif //METNUM_TP2_MACHINEFACTORY_H
