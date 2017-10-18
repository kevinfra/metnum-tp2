#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <atomic>
#include "../src/machines/MachineFactory.h"

#define DATASET_SIZE 10000

vector<unsigned char> run_machine(const TrainSet<Pixel> &trainSet,
                                  const TestSet<Pixel> &testSet, const parameters &p) {
    MachineRef machine = MachineFactory::create(p);

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

void save_diff(unsigned int i, size_t good, size_t total) {
    std::ofstream results("results.csv", std::ios_base::out | std::ios_base::app);
    results << i << "," << good << "," << total << std::endl;
}

void save_results(unsigned int it, const vector<unsigned char> &expected, const vector<unsigned char> &actual, const parameters &p) {
    std::ofstream results("results10k5ktrainAlpha" + std::to_string(p.alfa) + ".csv", std::ios_base::out | std::ios_base::app);
    int amount[10]={0};
    int good[10]={0};
    int bad[10] ={0};
    for(size_t i = 0; i < expected.size(); ++i) {
        amount[expected[i]]++;
        if(expected[i] == actual[i]) {
            good[expected[i]]++;
        } else {
            bad[actual[i]]++;
        }
    }

    results << it;
    for(int i = 0; i < 10; i++) {
        results << "," << good[i] << "," << bad[i] << "," << amount[i];
    }
    results << std::endl;
}


void run_crossval(unsigned int i, TrainSet<Pixel> trainSet,
                  TestSet<Pixel> testSet,
                  vector<unsigned char> expected, const parameters &p) {

    std::cout << "[" << i << "] Guessing...                 " << std::endl;
    vector<unsigned char> guesses = run_machine(trainSet, testSet, p);

    save_results(i, expected, guesses, p);
    /*
    std::cout << "[" << i << "] Calculating differences...  " << std::endl;
    size_t good = compare(expected, guesses);

    std::cout << "[" << i << "] Saving results...           " << std::endl;
    save_diff(i, good, expected.size());
     */
}

void crossval_thread(const TrainSet<Pixel> &trainSet, const vector<vector<bool>> &cases,
                     std::atomic_uint &fold, const parameters &p) {
    unsigned int i;
    while ((i = fold++) < cases.size()) {
        TrainSet<Pixel> trainSubset;
        TestSet<Pixel> testSet;
        vector<unsigned char> solutions;
        const vector<bool>& line = cases[i];
        for (unsigned int j = 0; j < DATASET_SIZE; ++j) {
            if(line[j]) {
                trainSubset.push_back(trainSet[j]);
            } else {
                testSet.push_back(trainSet[j].img);
                solutions.push_back(trainSet[j].digit);
            }
        }
        run_crossval(i, trainSubset, testSet, solutions, p);
    }
}

int main(int argc, char const *argv[]) {
    std::string folder;
    unsigned int kKNN;
    unsigned int alphaPCA;
    unsigned int kKFold;

    std::cin >> folder >> kKNN >> alphaPCA >> kKFold;

    vector< vector<bool> > cases(kKFold);

    for (unsigned int i = 0; i < kKFold; ++i) {
        vector<bool>& line = cases[i];
        for (unsigned int j = 0; j < DATASET_SIZE; ++j) {
            bool enable;
            std::cin >> enable;
            line.push_back(enable);
        }
    }

    std::ifstream train_file(folder + "train.csv");
    TrainSet<Pixel> trainSet = IO::loadTrainSet<Pixel>(train_file);
    train_file.close();

    vector<unsigned int> alphas = {5, 10, 15, 20, 25, 30, 40, 50, 60, 80, 100, 150, 200, 300, 400, 500};
    for (unsigned int i = 0; i < alphas.size(); i++) {
        alphaPCA = alphas[i];

        std::cout << "Running: Knn:" << kKNN << " AlphaPCA:" << alphaPCA << std::endl;

        vector<std::thread> ts;
        std::atomic_uint fold(0);

        {
            std::ofstream results("results10k5ktrainAlpha" + std::to_string(alphaPCA) + ".csv",
                                  std::ios_base::out | std::ios_base::trunc);
        }

        parameters p{MachineFactory::kNNPCA, NULL, NULL, NULL, kKNN, alphaPCA};

        for (unsigned int i = 0; i < 3; ++i) {
            ts.push_back(std::thread(crossval_thread, std::cref(trainSet),
                                     std::cref(cases), std::ref(fold), std::ref(p)));
        }

        for (auto t = ts.begin(); t != ts.end(); ++t) {
            (*t).join();
        }
    }

    std::cout << "All done!                        " << std::endl;
    return 0;
}