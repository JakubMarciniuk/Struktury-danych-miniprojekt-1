#include "BidirectionalList.h"

BidirectionalList::Node::Node(int val)
    : data(val), prev(nullptr), next(nullptr) {
}

BidirectionalList::BidirectionalList()
    : start(nullptr), end(nullptr), size(0) {
}

BidirectionalList::~BidirectionalList() {
    Node* node = start;
    while (node) {
        Node* nextNode = node->next;
        delete node;
        node = nextNode;
    }
}

void BidirectionalList::insertFront(int value) {
    Node* node = new Node(value);
    node->next = start;
    if (start) start->prev = node;
    else end = node;
    start = node;
    ++size;
}

void BidirectionalList::insertBack(int value) {
    Node* node = new Node(value);
    node->prev = end;
    if (end) end->next = node;
    else start = node;
    end = node;
    ++size;
}

void BidirectionalList::insertAt(int position, int value) {
    if (position < 0 || position > size) return;
    if (position == 0) return insertFront(value);
    if (position == size) return insertBack(value);

    Node* current = start;
    for (int i = 0; i < position; ++i) current = current->next;

    Node* node = new Node(value);
    node->prev = current->prev;
    node->next = current;
    current->prev->next = node;
    current->prev = node;
    ++size;
}

void BidirectionalList::deleteFront() {
    if (!start) return;
    Node* node = start;
    start = start->next;
    if (start) start->prev = nullptr;
    else end = nullptr;
    delete node;
    --size;
}

void BidirectionalList::deleteBack() {
    if (!end) return;
    Node* node = end;
    end = end->prev;
    if (end) end->next = nullptr;
    else start = nullptr;
    delete node;
    --size;
}

void BidirectionalList::deleteAt(int position) {
    if (position < 0 || position >= size) return;
    if (position == 0) return deleteFront();
    if (position == size - 1) return deleteBack();

    Node* current = start;
    for (int i = 0; i < position; ++i) current = current->next;

    current->prev->next = current->next;
    current->next->prev = current->prev;
    delete current;
    --size;
}

bool BidirectionalList::contains(int value) {
    for (Node* node = start; node; node = node->next)
        if (node->data == value) return true;
    return false;
}

int BidirectionalList::count() {
    return size;
}

void BidirectionalList::show() {
    std::cout << "[ ";
    for (Node* node = start; node; node = node->next)
        std::cout << node->data << " ";
    std::cout << "]\n";
}

void BidirectionalList::loadFromFile(std::string filePath) {
    Node* node = start;
    while (node) {
        Node* next = node->next;
        delete node;
        node = next;
    }
    start = end = nullptr;
    size = 0;

    std::ifstream file(filePath);
    if (!file) {
        std::cerr << "Nie mo¿na otworzyæ pliku: " << filePath << "\n";
        return;
    }

    int value;
    while (file >> value) {
        insertBack(value);
    }

    file.close();
}
