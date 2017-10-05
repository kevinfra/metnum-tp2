#include "PipelineFactory.h"
#include "KnnPipeline.h"

namespace PipelineFactory {

    PipelineRef create(const parameters& params) {
        switch(params.method) {
            case kNN:
                return std::make_shared<KnnPipeline>(params);
            case kNNPCA:
//                return ;
            default:
                throw std::runtime_error("Unknown implementation!");
        }
    }
}