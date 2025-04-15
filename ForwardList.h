#pragma once
#include "ISequence.h"
#include <iostream>
#include <fstream>

class ForwardList : public ISequence {
private:
    struct Node {
        int value;
        Node* next;
        Node(int v);
    };

    Node* first;
    Node* last;
    int size;

public:
    ForwardList();
    ~ForwardList();

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
