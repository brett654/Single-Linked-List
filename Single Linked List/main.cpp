#include <iostream>

struct Node {
    int data;
    Node* next; //The next member in a node holds the address of the next node in the linked list or nullptr if there are no further nodes.

    Node(int value) : data(value), next(nullptr) {}
};

class SingleLinkedList {
    private:
        Node* head; // Pointer to the head node

    public:
        SingleLinkedList() : head(nullptr) {}

        int getLength() {
            int length = 0;
            Node* current = head;

            while (current != nullptr) {
                length++;
                current = current->next;
            }
            return length;
        }

        void insert(int value) {
            Node* newNode = new Node(value); //create a new node

            if (head == nullptr) { //if the list is empty
                head = newNode; //set the head to the new node
            }
            else {
                Node* current = head;

                while (current->next != nullptr) {
                    current = current->next; //move to the next node
                }
                current->next = newNode; // Link the last node to the new node
            }
        }

        void insertAt(int index, int value) {
            Node* newNode = new Node(value);

            if (index == 0) {
                newNode->next = head;
                head = newNode;
                return;
            }

            Node* current = head;

            for (int i = 0; i < index - 1 && current != nullptr; i++) { //searches for the node just before the target position where the new node will be inserted.
                current = current->next;
            }

            if (current == nullptr) {
                std::cout << "Index out of bounds." << std::endl;
                delete newNode;
                return;
            }

            newNode->next = current->next;
            current->next = newNode;
        }

        void remove(int value) {
            if (head == nullptr) return;

            Node* current = head;
            Node* previous = nullptr;

            while (current != nullptr && current->data != value) {
                previous = current;
                current = current->next;
            }

            if (current == nullptr) {
                std::cout << "Value " << value << " not found in the list." << std::endl;
                return;
            }

            if (current == head) { // if the value to be removed is the head node
                head = head->next; //move head to next node
            }
            else {
                previous->next = current->next; // Bypass the current node
            }

            delete current;
            std::cout << "Value " << value << " removed from the list." << std::endl;
        }
        
        Node* merge(Node* left, Node* right) {
            if (!left) return right;
            if (!right) return left;

            if (left->data <= right ->data) {
                left->next = merge(left->next, right);
                return left;
            }
            else {
                right->next = merge(left, right->next);
                return right;
            }
        }

        Node* getMiddle() {
            return getMiddle(head);
        }

        Node* getMiddle(Node* node) {
            if (!node || !node->next) {
                return node;
            }
            Node* slow = node;
            Node* fast = node->next;

            while (fast != nullptr && fast->next != nullptr) {
                slow = slow->next;
                fast = fast->next->next;
            }

            return slow;
        }

        void mergeSort() {
            head = mergeSort(head); // Start sorting from the head
        }

        Node* mergeSort(Node* node) {
            if (!node || !node->next) {
                return node; // Base case: If list is empty or has one node
            }

            Node* middle = getMiddle(node); // Get the middle node
            Node* secondHalf = middle->next; // Split the list into two halves
            middle->next = nullptr; // Break the list into two halves

            // Recursively sort both halves
            Node* leftSorted = mergeSort(node);
            Node* rightSorted = mergeSort(secondHalf);

            return merge(leftSorted, rightSorted); // Merge sorted halves
        }


        void display() const {
            Node* current = head;

            while (current != nullptr) {
                std::cout << current->data << " ";
                current = current->next; 
            }
            std::cout << std::endl;
        }

        ~SingleLinkedList() {
            Node* current = head;

            while (current != nullptr) {
                Node* temp = current;
                current = current->next; // move to the next node leaving behind the last current that's why we store it in temp
                delete temp;
            }
        }
};

int main() {
    SingleLinkedList list;

    for (int i = 1; i <= 10; ++i) {
        list.insert(i);
    }

    list.display();

    list.remove(5);
    list.display();

    int length = list.getLength();
    std::cout << "Length of the list: " << length << std::endl;

    list.insertAt(4, 5);
    list.display();

    Node* middle = list.getMiddle();
    if (middle != nullptr) {
        std::cout << "Middle value: " << middle->data << std::endl;
    } else {
        std::cout << "List is empty." << std::endl;
    }

    SingleLinkedList unsortedList;

    for (int i = 10; i > 0; --i) {
        unsortedList.insert(i);
    }

    std::cout << "Original List: ";
    unsortedList.display();

    unsortedList.mergeSort();

    std::cout << "Sorted List: ";
    unsortedList.display();

    return 0;
}

