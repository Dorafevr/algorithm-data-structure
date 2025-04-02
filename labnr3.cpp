#include <iostream>
#include <cassert>
#include <functional>

template<typename T>
struct Node {
    T value;
    Node* next;
    Node* prev;  

    Node(T val) : value(val), next(nullptr), prev(nullptr) {}
};

template<typename T>
struct FindNodeResult {
    Node<T>* prevNode;
    Node<T>* foundNode;
};

template<typename T>
struct SinglyLinkedList {
    Node<T>* head;
    Node<T>* tail;
    size_t size;

    SinglyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    Node<T>* insertAfter(Node<T>* node, T value) {
        Node<T>* newNode = new Node<T>(value);
        if (!node) {
            newNode->next = head;
            head = newNode;
            if (!tail) tail = newNode;
        } else {
            newNode->next = node->next;
            node->next = newNode;
            if (node == tail) tail = newNode;
        }
        ++size;
        assertNoCycles();
        return newNode;
    }

    FindNodeResult<T> find(T value) {
        Node<T>* prev = nullptr;
        Node<T>* current = head;
        while (current) {
            if (current->value == value) return {prev, current};
            prev = current;
            current = current->next;
        }
        return {nullptr, nullptr};
    }

    void removeAfter(Node<T>* node) {
        if (!node) {
            if (head) {
                Node<T>* temp = head;
                head = head->next;
                delete temp;
                if (!head) tail = nullptr;
                --size;
            }
        } else if (node->next) {
            Node<T>* temp = node->next;
            node->next = temp->next;
            if (temp == tail) tail = node;
            delete temp;
            --size;
        }
        assertNoCycles();
    }

    void assertNoCycles() {
        size_t count = 0;
        Node<T>* current = head;
        while (current) {
            current = current->next;
            if (++count > size) {
                assert(false && "Cycle detected in list!");
            }
        }
    }
};


void testSinglyLinkedList() {
    SinglyLinkedList<int> list;
    Node<int>* first = list.insertAfter(nullptr, 1);
    Node<int>* second = list.insertAfter(first, 2);
    Node<int>* third = list.insertAfter(second, 3);
    assert(list.head == first);
    assert(list.tail == third);
    assert(list.find(2).foundNode == second);
    list.removeAfter(first);
    assert(list.find(2).foundNode == nullptr);
    list.assertNoCycles();
    std::cout << "Singly linked list tests passed!\n";
}

int main() {
    testSinglyLinkedList();
    return 0;
}