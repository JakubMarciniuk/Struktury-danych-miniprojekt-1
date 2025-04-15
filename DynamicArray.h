#pragma once
#include "ISequence.h"
#include <iostream>

class DynamicArray : public ISequence {
private:
    int* buffer;
    int maxSize;
    int size;

    void expand();

public:
    DynamicArray(int initialSize = 10);
    ~DynamicArray();

    void insertFront(int value) override;
    void insertBack(int value) override;
    void insertAt(int position, int value) override;
    void deleteFront() override;
    void deleteBack() override;
    void deleteAt(int position) override;
    bool contains(int value) override;
    int count() override;
    void show() override;
    void loadFromFile(std::string filePath) override;
};
