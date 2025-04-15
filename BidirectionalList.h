#pragma once
#include "ISequence.h"
#include <iostream>
#include <fstream>

class BidirectionalList : public ISequence {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val);
    };

    Node* start;
    Node* end;
    int size;

public:
    BidirectionalList();
    ~BidirectionalList();

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
