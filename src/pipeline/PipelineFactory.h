#ifndef METNUM_TP2_PIPELINEFACTORY_H
#define METNUM_TP2_PIPELINEFACTORY_H

#include "Pipeline.h"
#include "../parameters.h"

typedef std::shared_ptr<Pipeline> PipelineRef;

namespace PipelineFactory {

    enum Implementations : unsigned char { kNN, kNNPCA };

    PipelineRef create(const parameters& params);
}

#endif //METNUM_TP2_PIPELINEFACTORY_H
