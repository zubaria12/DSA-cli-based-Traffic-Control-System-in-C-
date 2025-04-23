# 🚦 Traffic Control System in C++

A C++ console application that simulates a traffic control system with the ability to manage roads and prioritize vehicles using separate emergency and normal queues. It supports dynamic road creation, vehicle addition, processing by priority, and file I/O for saving/loading road data.

---

## 🔧 Features

- Add roads with source, destination, and capacity
- Add vehicles with type, ID, and priority (Normal or Emergency)
- Separate queueing for emergency and normal vehicles
- Process vehicles in priority order
- Save and load roads from a file
- Display roads and their respective queues

---

## 📁 Project Structure

📁 TrafficControlSystem/ ├── main.cpp # Main source code └── roads.txt # Optional saved road data

---

## ▶️ How to Run

### 🛠 Requirements

- C++11 or later
- GCC or any C++ compiler

### 🚀 Steps to Run

1. **Compile the program:**
   ```bash
   g++ -o traffic_system main.cpp
Run the program:
./traffic_system
🛣️ Menu Options
Add Road - Define a road by source, destination, and capacity.

Display Roads - Show all roads and their queued vehicles.

Add Vehicle - Assign a vehicle to a road with priority.

Process Vehicles - Dequeue and process emergency vehicles first, then normal ones.

Save Roads - Write road information to a file.

Load Roads - Load road data from a file.

Exit - Terminate the program.

📦 File Format Example
roads.txt
1 2 10
3 4 15
Each line: source destination capacity

💡 Key Concepts Used
Custom Queue class with linked list

Separate emergency & normal queues

Linked list to manage roads dynamically

File I/O using fstream

Object-oriented design

✨ Sample Output
Traffic Control System
1. Add Road
2. Display Roads
3. Add Vehicle
...
Vehicle ID: 102, Type: Car, Priority: 2
Processed Vehicle ID: 102
🤝 Contribution
Pull requests are welcome. You can help improve features like:

Queue visualization

GUI version

Real-time traffic simulation


