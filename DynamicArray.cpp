#include "DynamicArray.h"
#include <fstream>

DynamicArray::DynamicArray(int initialSize)
    : maxSize(initialSize), size(0) {
    buffer = new int[maxSize];
}

DynamicArray::~DynamicArray() {
    delete[] buffer;
}

void DynamicArray::expand() {
    maxSize *= 2;
    int* newBuffer = new int[maxSize];
    for (int i = 0; i < size; ++i)
        newBuffer[i] = buffer[i];
    delete[] buffer;
    buffer = newBuffer;
}

void DynamicArray::insertFront(int value) {
    if (size == maxSize) expand();
    for (int i = size; i > 0; --i)
        buffer[i] = buffer[i - 1];
    buffer[0] = value;
    ++size;
}

void DynamicArray::insertBack(int value) {
    if (size == maxSize) expand();
    buffer[size++] = value;
}

void DynamicArray::insertAt(int position, int value) {
    if (position < 0 || position > size) return;
    if (size == maxSize) expand();
    for (int i = size; i > position; --i)
        buffer[i] = buffer[i - 1];
    buffer[position] = value;
    ++size;
}

void DynamicArray::deleteFront() {
    if (size == 0) return;
    for (int i = 0; i < size - 1; ++i)
        buffer[i] = buffer[i + 1];
    --size;
}

void DynamicArray::deleteBack() {
    if (size > 0) --size;
}

void DynamicArray::deleteAt(int position) {
    if (position < 0 || position >= size) return;
    for (int i = position; i < size - 1; ++i)
        buffer[i] = buffer[i + 1];
    --size;
}

bool DynamicArray::contains(int value) {
    for (int i = 0; i < size; ++i)
        if (buffer[i] == value) return true;
    return false;
}

int DynamicArray::count() {
    return size;
}

void DynamicArray::show() {
    std::cout << "[ ";
    for (int i = 0; i < size; ++i)
        std::cout << buffer[i] << " ";
    std::cout << "]\n";
}

void DynamicArray::loadFromFile(std::string filePath) {
    delete[] buffer;
    buffer = new int[maxSize];
    size = 0;

    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "File error: " << filePath << "\n";
        return;
    }

    int num;
    while (file >> num) {
        insertBack(num);
    }

    file.close();
}
