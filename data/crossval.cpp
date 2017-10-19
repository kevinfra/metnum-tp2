#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <thread>
#include <atomic>
#include "../src/machines/MachineFactory.h"

#define DATASET_SIZE 10000

void save_results(unsigned int it, const vector<unsigned char> &expected, const vector<unsigned char> &actual, const parameters &p, unsigned int k) {
    std::ofstream results("results10k"+std::to_string(k)+"ktrainAlpha" + std::to_string(p.alfa) + ".csv", std::ios_base::out | std::ios_base::app);
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

void run_machine(TrainSet<unsigned char> trainSet, TestSet<unsigned char> testSet, const parameters &p, vector<unsigned char> &expected, unsigned int foldindex) {
    MachineRef machine = MachineFactory::create(p);

    machine->train(trainSet);

    vector<unsigned int> ks = {1, 2, 3, 4, 5, 7, 8, 9, 10, 15, 20, 30};
    for (unsigned int i = 0; i < ks.size(); i++) {
        vector<unsigned char> guess = machine->guessK(testSet, ks[i]);

        save_results(foldindex, expected, guess, p, ks[i]);
    }
}

void run_crossval(unsigned int i, TrainSet<Pixel> trainSet,
                  TestSet<Pixel> testSet,
                  vector<unsigned char> expected, const parameters &p) {

    std::cout << "[" << i << "] Guessing...                 " << std::endl;
    run_machine(trainSet, testSet, p, expected, i);

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

    vector<unsigned int> alphas = {15, 30, 50};
    for (unsigned int i = 0; i < alphas.size(); i++) {
        alphaPCA = alphas[i];

        std::cout << "Running: Knn:" << kKNN << " AlphaPCA:" << alphaPCA << std::endl;

        vector<std::thread> ts;
        std::atomic_uint fold(0);

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