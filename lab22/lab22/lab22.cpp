//Melissa Ochoa Flores
//COMSC 210
//Upgrade the DLL Class

#include <iostream>
using namespace std;

const int MIN_NR = 10, MAX_NR = 99, MIN_LS = 5, MAX_LS = 20;

class DoublyLinkedList {
private:
    struct Node {
        int data;
        Node* prev;
        Node* next;
        Node(int val, Node* p = nullptr, Node* n = nullptr) {
            data = val;
            prev = p;
            next = n;
        }
    };
    Node* head;
    Node* tail;

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr) {}

    void push_back(int value) {
        Node* newNode = new Node(value);
        if (!tail) {
            head = tail = newNode;
        }
        else {
            tail->next = newNode;
            newNode->prev = tail;
            tail = newNode;
        }
    }

    void push_front(int value) {
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
        }
        else {
            newNode->next = head;
            head->prev = newNode;
            head = newNode;
        }
    }

    void insert_after(int value, int position) {
        if (position < 0) {
            cout << "Position must be >= 0." << endl;
            return;
        }
        Node* newNode = new Node(value);
        if (!head) {
            head = tail = newNode;
            return;
        }
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        if (!temp) {
            cout << "Position exceeds list size. Node not inserted.\n";
            delete newNode;
            return;
        }
        newNode->next = temp->next;
        newNode->prev = temp;
        if (temp->next)
            temp->next->prev = newNode;
        else
            tail = newNode;
        temp->next = newNode;
    }

    void delete_val(int value) {
        if (!head) return;
        Node* temp = head;
        while (temp && temp->data != value)
            temp = temp->next;
        if (!temp) return;
        if (temp->prev) {
            temp->prev->next = temp->next;
        }
        else {
            head = temp->next;
        }
        if (temp->next) {
            temp->next->prev = temp->prev;
        }
        else {
            tail = temp->prev;
        }
        delete temp;
    }

    void delete_pos(int position) {
        if (position < 0 || !head) return;
        Node* temp = head;
        for (int i = 0; i < position && temp; ++i)
            temp = temp->next;
        if (!temp) return;
        if (temp->prev)
            temp->prev->next = temp->next;
        else
            head = temp->next;
        if (temp->next)
            temp->next->prev = temp->prev;
        else
            tail = temp->prev;
        delete temp;
    }

    void pop_front() {
        if (!head) return;
        Node* temp = head;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            head = head->next;
            head->prev = nullptr;
        }
        delete temp;
    }

    void pop_back() {
        if (!tail) return;
        Node* temp = tail;
        if (head == tail) {
            head = tail = nullptr;
        }
        else {
            tail = tail->prev;
            tail->next = nullptr;
        }
        delete temp;
    }

    void print() {
        Node* current = head;
        if (!current) {
            cout << "List is empty" << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->next;
        }
        cout << endl;
    }

    void print_reverse() {
        Node* current = tail;
        if (!current) {
            cout << "List is empty" << endl;
            return;
        }
        while (current) {
            cout << current->data << " ";
            current = current->prev;
        }
        cout << endl;
    }

    ~DoublyLinkedList() {
        while (head) {
            Node* temp = head;
            head = head->next;
            delete temp;
        }
    }
};

int main() {
    srand(time(0));
    DoublyLinkedList list;

    int size = rand() % (MAX_LS - MIN_LS + 1) + MIN_LS;
    for (int i = 0; i < size; ++i)
        list.push_back(rand() % (MAX_NR - MIN_NR + 1) + MIN_NR);

    cout << "List forward: ";
    list.print();
    cout << "List backward: ";
    list.print_reverse();

    cout << "Deleting node at position 2.\n";
    list.delete_pos(2);
    cout << "List forward after deletion at position 2: ";
    list.print();

    cout << "Popping front (deleting head node).\n";
    list.pop_front();
    cout << "List forward after popping front: ";
    list.print();

    cout << "Popping back (deleting tail node).\n";
    list.pop_back();
    cout << "List forward after popping back: ";
    list.print();

    cout << "Deleting node with value 30.\n";
    list.delete_val(30);
    cout << "List forward after deleting value 30: ";
    list.print();

    return 0;
}
