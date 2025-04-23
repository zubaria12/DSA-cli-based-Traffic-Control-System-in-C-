#include <iostream>
#include <fstream>
#include <string>
using namespace std;

// Custom queue implementation
class Queue {
private:
    struct Node {
        int id;
        string type;
        int priority;
        Node* next;
        Node(int i, string t, int p) : id(i), type(t), priority(p), next(nullptr) {}
    };
    Node* front;
    Node* rear;

public:
    Queue() : front(nullptr), rear(nullptr) {}

    bool isEmpty() {
        return front == nullptr;
    }
    void enqueue(int id, string type, int priority) {
        Node* newNode = new Node(id, type, priority);
        if (rear) {
            rear->next = newNode;
        } else {
            front = newNode;
        }
        rear = newNode;
    }

    Node* dequeue() {
        if (isEmpty()) {
            cout << "Queue is empty.\n";
            return nullptr;
        }
        Node* temp = front;
        front = front->next;
        if (!front) {
            rear = nullptr;
        }
        return temp;
    }

    void display() {
        Node* temp = front;
        while (temp) {
            cout << "Vehicle ID: " << temp->id << ", Type: " << temp->type
                 << ", Priority: " << temp->priority << "\n";
            temp = temp->next;
        }
    }

    ~Queue() {
        while (!isEmpty()) {
            delete dequeue();
        }
    }
};

// Linked list to manage roads
class RoadList {
private:
    struct Road {
        int source;
        int destination;
        int capacity;
        Queue normalQueue;
        Queue emergencyQueue;
        Road* next;
        Road(int src, int dest, int cap) : source(src), destination(dest), capacity(cap), next(nullptr) {}
    };
    Road* head;

public:
    RoadList() : head(nullptr) {}

    void addRoad(int source, int destination, int capacity) {
        Road* newRoad = new Road(source, destination, capacity);
        newRoad->next = head;
        head = newRoad;
    }

    Road* findRoad(int source, int destination) {
        Road* temp = head;
        while (temp) {
            if (temp->source == source && temp->destination == destination) {
                return temp;
            }
            temp = temp->next;
        }
        return nullptr;
    }

    void displayRoads() {
        Road* temp = head;
        while (temp) {
            cout << "Road: " << temp->source << " -> " << temp->destination
                 << ", Capacity: " << temp->capacity << "\n";
            cout << "Emergency Queue:\n";
            temp->emergencyQueue.display();
            cout << "Normal Queue:\n";
            temp->normalQueue.display();
            temp = temp->next;
        }
    }

    void saveToFile(const string& filename) {
        ofstream file(filename);
        if (!file) {
            cout << "Error saving to file.\n";
            return;
        }
        Road* temp = head;
        while (temp) {
            file << temp->source << " " << temp->destination << " " << temp->capacity << "\n";
            temp = temp->next;
        }
        file.close();
        cout << "Roads saved to " << filename << "\n";
    }

    void loadFromFile(const string& filename) {
        ifstream file(filename);
        if (!file) {
            cout << "Error loading from file.\n";
            return;
        }
        int src, dest, cap;
        while (file >> src >> dest >> cap) {
            addRoad(src, dest, cap);
        }
        file.close();
        cout << "Roads loaded from " << filename << "\n";
    }
};

int main() {
    RoadList roads;
    bool running = true;

    while (running) {
        cout << "\nTraffic Control System\n"
             << "1. Add Road\n"
             << "2. Display Roads\n"
             << "3. Add Vehicle\n"
             << "4. Process Vehicles\n"
             << "5. Save Roads to File\n"
             << "6. Load Roads from File\n"
             << "0. Exit\n"
             << "Enter your choice: ";
        int choice;
        cin >> choice;

        switch (choice) {
        case 1: {
            int src, dest, cap;
            cout << "Enter source, destination, and capacity: ";
            cin >> src >> dest >> cap;
            roads.addRoad(src, dest, cap);
            break;
        }
        case 2:
            roads.displayRoads();
            break;
        case 3: {
            int src, dest, id, priority;
            string type;
            cout << "Enter source and destination of the road: ";
            cin >> src >> dest;
            cout << "Enter vehicle ID, type (Car/Truck), and priority (1=Normal, 2=Emergency): ";
            cin >> id >> type >> priority;

            auto road = roads.findRoad(src, dest);
            if (road) {
                if (priority == 2) {
                    road->emergencyQueue.enqueue(id, type, priority);
                } else {
                    road->normalQueue.enqueue(id, type, priority);
                }
                cout << "Vehicle added.\n";
            } else {
                cout << "Road not found.\n";
            }
            break;
        }
        case 4: {
            int src, dest;
            cout << "Enter source and destination of the road to process vehicles: ";
            cin >> src >> dest;

            auto road = roads.findRoad(src, dest);
            if (road) {
                cout << "Processing Emergency Vehicles:\n";
                while (!road->emergencyQueue.isEmpty()) {
                    auto vehicle = road->emergencyQueue.dequeue();
                    cout << "Processed Vehicle ID: " << vehicle->id << "\n";
                    delete vehicle;
                }

                cout << "Processing Normal Vehicles:\n";
                while (!road->normalQueue.isEmpty()) {
                    auto vehicle = road->normalQueue.dequeue();
                    cout << "Processed Vehicle ID: " << vehicle->id << "\n";
                    delete vehicle;
                }
            } else {
                cout << "Road not found.\n";
            }
            break;
        }
        case 5: {
            string filename;
            cout << "Enter filename to save roads: ";
            cin >> filename;
            roads.saveToFile(filename);
            break;
        }
        case 6: {
            string filename;
            cout << "Enter filename to load roads: ";
            cin >> filename;
            roads.loadFromFile(filename);
            break;
        }
        case 0:
            running = false;
            break;
        default:
            cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}


