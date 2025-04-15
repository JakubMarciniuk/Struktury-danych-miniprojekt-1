#include <iostream>
#include <fstream>
#include <string>
#include <random>
#include <chrono>

#include "DynamicArray.h"
#include "ForwardList.h"
#include "BidirectionalList.h"

using namespace std;

// Tworzy plik z losowymi liczbami całkowitymi
void generateDataFile(const string& filename, int count) {
    ofstream outFile(filename);
    if (!outFile) {
        cerr << "Błąd zapisu pliku: " << filename << '\n';
        return;
    }

    random_device rd;
    mt19937 rng(rd());
    uniform_int_distribution<int> dist(INT32_MIN, INT32_MAX);

    for (int i = 0; i < count; ++i)
        outFile << dist(rng) << '\n';

    outFile.close();
}

// Tworzy 10 zestawów testowych dla danego rozmiaru
void prepareTestSets(const string& prefix, int count) {
    for (int i = 0; i < 10; ++i) {
        string file = prefix + "_" + to_string(count) + "_" + to_string(i) + ".txt";
        generateDataFile(file, count);
    }
}

// Wykonuje pomiary dla wszystkich operacji na listach
void runPerformanceTests(ISequence& seqA, ISequence& seqB, ISequence& seqC) {
    const string baseName = "Dataset";
    int datasetSize = 10000;

    random_device rd;
    mt19937 rng(rd());

    while (datasetSize <= 100000) {
        long long addStart[3]{}, addEnd[3]{}, addMid[3]{};
        long long delStart[3]{}, delEnd[3]{}, delMid[3]{};
        long long searchTimes[3]{};

        for (int fileNum = 0; fileNum < 10; ++fileNum) {
            string file = baseName + "_" + to_string(datasetSize) + "_" + to_string(fileNum) + ".txt";

            seqA.loadFromFile(file);
            seqB.loadFromFile(file);
            seqC.loadFromFile(file);

            uniform_int_distribution<int> indexGen(0, datasetSize - 1);
            int searchTarget = indexGen(rng);

            for (int i = 0; i < 100; ++i) {
                int idx = indexGen(rng);

                // Test DynamicArray
                auto start = chrono::high_resolution_clock::now();
                seqA.insertFront(7);
                auto stop = chrono::high_resolution_clock::now();
                addStart[0] += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

                start = chrono::high_resolution_clock::now();
                seqA.deleteFront();
                stop = chrono::high_resolution_clock::now();
                delStart[0] += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

                start = chrono::high_resolution_clock::now();
                seqA.insertBack(7);
                stop = chrono::high_resolution_clock::now();
                addEnd[0] += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

                start = chrono::high_resolution_clock::now();
                seqA.deleteBack();
                stop = chrono::high_resolution_clock::now();
                delEnd[0] += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

                start = chrono::high_resolution_clock::now();
                seqA.insertAt(idx, 7);
                stop = chrono::high_resolution_clock::now();
                addMid[0] += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

                start = chrono::high_resolution_clock::now();
                seqA.deleteAt(idx);
                stop = chrono::high_resolution_clock::now();
                delMid[0] += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

                start = chrono::high_resolution_clock::now();
                seqA.contains(searchTarget);
                stop = chrono::high_resolution_clock::now();
                searchTimes[0] += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

                // ForwardList & BidirectionalList
                ISequence* lists[] = { &seqB, &seqC };
                for (int j = 0; j < 2; ++j) {
                    start = chrono::high_resolution_clock::now();
                    lists[j]->insertFront(7);
                    stop = chrono::high_resolution_clock::now();
                    addStart[j + 1] += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

                    start = chrono::high_resolution_clock::now();
                    lists[j]->deleteFront();
                    stop = chrono::high_resolution_clock::now();
                    delStart[j + 1] += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

                    start = chrono::high_resolution_clock::now();
                    lists[j]->insertBack(7);
                    stop = chrono::high_resolution_clock::now();
                    addEnd[j + 1] += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

                    start = chrono::high_resolution_clock::now();
                    lists[j]->deleteBack();
                    stop = chrono::high_resolution_clock::now();
                    delEnd[j + 1] += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

                    start = chrono::high_resolution_clock::now();
                    lists[j]->insertAt(idx, 7);
                    stop = chrono::high_resolution_clock::now();
                    addMid[j + 1] += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

                    start = chrono::high_resolution_clock::now();
                    lists[j]->deleteAt(idx);
                    stop = chrono::high_resolution_clock::now();
                    delMid[j + 1] += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();

                    start = chrono::high_resolution_clock::now();
                    lists[j]->contains(searchTarget);
                    stop = chrono::high_resolution_clock::now();
                    searchTimes[j + 1] += chrono::duration_cast<chrono::nanoseconds>(stop - start).count();
                }
            }
        }

        cout << "\nWielkosc: " << datasetSize << "\n";
        const char* names[3] = { "DynamicArray", "ForwardList", "BidirectionalList" };

        for (int i = 0; i < 3; ++i) {
            cout << names[i]
                << " | DodajStart: " << addStart[i] / 1000.0
                    << ", UsunStart: " << delStart[i] / 1000.0
                    << ", DodajKoniec: " << addEnd[i] / 1000.0
                    << ", UsunKoniec: " << delEnd[i] / 1000.0
                    << ", DodajSrodek: " << addMid[i] / 1000.0
                    << ", UsunŚrodek: " << delMid[i] / 1000.0
                    << ", Szukaj: " << searchTimes[i] / 1000.0
                    << '\n';
        }

        datasetSize += 10000;
    }
}

int main() {
    DynamicArray arrStructure;
    ForwardList singleStructure;
    BidirectionalList doubleStructure;

    for (int size = 10000; size <= 100000; size += 10000) {
        prepareTestSets("Dataset", size);
    }

    runPerformanceTests(arrStructure, singleStructure, doubleStructure);

    return 0;
}

