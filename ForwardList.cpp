#include "ForwardList.h"

// Konstruktor wêz³a
ForwardList::Node::Node(int v) : value(v), next(nullptr) {}

// Konstruktor listy
ForwardList::ForwardList() : first(nullptr), last(nullptr), size(0) {}

// Destruktor
ForwardList::~ForwardList() {
    Node* current = first;
    while (current) {
        Node* nextNode = current->next;
        delete current;
        current = nextNode;
    }
}

// Dodaje element na pocz¹tek
void ForwardList::insertFront(int value) {
    Node* node = new Node(value);
    node->next = first;
    first = node;
    if (!last) last = node;
    ++size;
}

// Dodaje element na koniec
void ForwardList::insertBack(int value) {
    Node* node = new Node(value);
    if (!last) {
        first = last = node;
    }
    else {
        last->next = node;
        last = node;
    }
    ++size;
}

// Dodaje element na okreœlonej pozycji
void ForwardList::insertAt(int position, int value) {
    if (position < 0 || position > size) return;
    if (position == 0) return insertFront(value);
    if (position == size) return insertBack(value);

    Node* current = first;
    for (int i = 0; i < position - 1; ++i)
        current = current->next;

    Node* node = new Node(value);
    node->next = current->next;
    current->next = node;
    ++size;
}

// Usuwa pierwszy element
void ForwardList::deleteFront() {
    if (!first) return;
    Node* temp = first;
    first = first->next;
    delete temp;
    if (!first) last = nullptr;
    --size;
}

// Usuwa ostatni element
void ForwardList::deleteBack() {
    if (!first) return;
    if (first == last) {
        delete first;
        first = last = nullptr;
        size = 0;
        return;
    }

    Node* current = first;
    while (current->next != last)
        current = current->next;

    delete last;
    last = current;
    last->next = nullptr;
    --size;
}

// Usuwa element na pozycji
void ForwardList::deleteAt(int position) {
    if (position < 0 || position >= size) return;
    if (position == 0) return deleteFront();
    if (position == size - 1) return deleteBack();

    Node* current = first;
    for (int i = 0; i < position - 1; ++i)
        current = current->next;

    Node* nodeToDelete = current->next;
    current->next = nodeToDelete->next;
    delete nodeToDelete;
    --size;
}

// Szuka elementu
bool ForwardList::contains(int value) {
    for (Node* node = first; node; node = node->next)
        if (node->value == value) return true;
    return false;
}

// Zwraca liczbê elementów
int ForwardList::count() {
    return size;
}

// Wyœwietla zawartoœæ
void ForwardList::show() {
    std::cout << "[ ";
    for (Node* node = first; node; node = node->next)
        std::cout << node->value << " ";
    std::cout << "]\n";
}

// Import z pliku
void ForwardList::loadFromFile(std::string filePath) {
    Node* node = first;
    while (node) {
        Node* temp = node->next;
        delete node;
        node = temp;
    }
    first = last = nullptr;
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
