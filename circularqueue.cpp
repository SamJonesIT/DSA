#include <bits/stdc++.h>
using namespace std;

class CircularQueue {
private:
    int front, rear, size;
    int* queue;

public:
    CircularQueue(int capacity) {
        size = capacity;
        queue = new int[size];
        front = -1;
        rear = -1;
    }

    ~CircularQueue() {
        delete[] queue;
    }

    // Insertion (Enqueue)
    void enqueue(int value) {
        if ((rear + 1) % size == front) {
            cout << "Queue is full! Cannot enqueue " << value << endl;
            return;
        }
        if (front == -1) { // First element being inserted
            front = 0;
        }
        rear = (rear + 1) % size;
        queue[rear] = value;
        cout << value << " enqueued to the queue." << endl;
    }

    // Deletion (Dequeue)
    void dequeue() {
        if (front == -1) {
            cout << "Queue is empty! Cannot dequeue." << endl;
            return;
        }
        cout << queue[front] << " dequeued from the queue." << endl;
        if (front == rear) { // Queue becomes empty
            front = rear = -1;
        } else {
            front = (front + 1) % size;
        }
    }

    // Display the elements in the queue
    void display() {
        if (front == -1) {
            cout << "Queue is empty!" << endl;
            return;
        }
        cout << "Queue elements are: ";
        int i = front;
        while (true) {
            cout << queue[i] << " ";
            if (i == rear) break;
            i = (i + 1) % size;
        }
        cout << endl;
    }
};

int main() {
    int capacity;
    cout << "Enter the capacity of the circular queue: ";
    cin >> capacity;

    CircularQueue cq(capacity);

    int choice, value;
    do {
        cout << "\n--- Circular Queue Operations ---\n";
        cout << "1. Enqueue\n2. Dequeue\n3. Display\n4. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                cout << "Enter the value to enqueue: ";
                cin >> value;
                cq.enqueue(value);
                break;
            case 2:
                cq.dequeue();
                break;
            case 3:
                cq.display();
                break;
            case 4:
                cout << "Exiting program." << endl;
                break;
            default:
                cout << "Invalid choice! Please try again." << endl;
        }
    } while (choice != 4);

    return 0;
}
