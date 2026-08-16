#include <iostream>
#include <queue> 
using namespace std;

int main() {
    queue<int> q;

    q.push(10); // [10]
    q.push(20); // [10, 20]
    q.push(30); // [10, 20, 30]

    // Display queue properties
    cout << "Queue size: " << q.size() << "\n";      // Output: 3
    cout << "Last added element: " << q.back() << "\n"; // Output: 30

    // Safely process and empty the queue
    while (!q.empty()) {
        cout << "Front element: " << q.front() << "\n"; 
        q.pop(); 
    }

    return 0;
}