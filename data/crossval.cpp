#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include "../src/machines/MachineFactory.h"

#define DATASET_SIZE 42000

vector<unsigned char> run_machine(const TrainSet<Pixel> &trainSet, const TestSet<Pixel> &testSet) {
    MachineRef machine = MachineFactory::create(MachineFactory::kNNPCA);

    machine->train(trainSet);

    return machine->guess(testSet);
}

size_t compare(const vector<unsigned char> &expected, const vector<unsigned char> &actual) {
    assert(expected.size() == actual.size());
    size_t good = 0;
    for(size_t i = 0; i < expected.size(); ++i) {
        if(expected[i] == actual[i]) {
            ++good;
        }
    }
    return good;
}

void save_diff(size_t good, size_t total) {
    std::ofstream results("results.csv");
    results << good << "," << total << std::endl;
}

int main(int argc, char const *argv[]) {
    std::string folder;
    unsigned int kKNN;
    unsigned int alphaPCA;
    unsigned int kKFold;

    std::cin >> folder >> kKNN >> alphaPCA >> kKFold;

    std::vector< std::vector<bool> > cases(kKFold);

    for (unsigned int i = 0; i < kKFold; ++i) {
        std::vector<bool>& line = cases[i];
        for (unsigned int j = 0; j < DATASET_SIZE; ++j) {
            bool enable;
            std::cin >> enable;
            line.push_back(enable);
        }
    }

    std::ifstream train_file(folder + "train.csv");
    TrainSet<Pixel> trainSet = IO::loadTrainSet<Pixel>(train_file);
    train_file.close();

    for (unsigned int i = 0; i < kKFold; ++i) {
        TrainSet<Pixel> trainSubset;
        TestSet<Pixel> testSet;
        vector<unsigned char> solutions;
        std::vector<bool>& line = cases[i];
        for (unsigned int j = 0; j < DATASET_SIZE; ++j) {
            if(line[j]) {
                trainSubset.push_back(trainSet[j]);
            } else {
                testSet.push_back(trainSet[j].img);
                solutions.push_back(trainSet[j].digit);
            }
        }
        std::cout << "[" << i << "] Guessing...                 \r" << std::flush;
        vector<unsigned char> guesses = run_machine(trainSubset, testSet);

        std::cout << "[" << i << "] Calculating differences...  \r" << std::flush;
        size_t good = compare(solutions, guesses);

        std::cout << "[" << i << "] Saving results...           \r" << std::flush;
        save_diff(good, solutions.size());
    }

    std::cout << "All done!                        " << std::endl;
    return 0;
}