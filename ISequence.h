#pragma once
#include <iostream>

// Nowy interfejs bazowy
class ISequence {
public:
    virtual void insertFront(int value) = 0;
    virtual void insertBack(int value) = 0;
    virtual void insertAt(int position, int value) = 0;
    virtual void deleteFront() = 0;
    virtual void deleteBack() = 0;
    virtual void deleteAt(int position) = 0;
    virtual bool contains(int value) = 0;
    virtual int count() = 0;
    virtual void show() = 0;
    virtual void loadFromFile(std::string filePath) = 0;

    virtual ~ISequence() {}
};
