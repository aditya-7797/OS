#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>

using namespace std;

// Function to calculate total seek operations for SSTF (Shortest Seek Time First)
int sstf(vector<int> requests, int head) {
    int totalSeekOperations = 0;
    while (!requests.empty()) {
        auto closest = min_element(requests.begin(), requests.end(),
            [head](int a, int b) { return abs(a - head) < abs(b - head); });
        
        totalSeekOperations += abs(*closest - head);
        head = *closest;
        requests.erase(closest);
    }
    return totalSeekOperations;
}

// Function to calculate total seek operations for SCAN
int scan(vector<int> requests, int head, int diskSize) {
    int totalSeekOperations = 0;
    requests.push_back(head);
    sort(requests.begin(), requests.end());
    
    // Find the starting point of the head
    auto it = find(requests.begin(), requests.end(), head);
    
    // Moving towards the end of the disk
    for (auto i = it; i != requests.end(); ++i) {
        totalSeekOperations += abs(head - *i);
        head = *i;
    }
    
    // Check if the head reached the end of the disk, then reverse
    if (head != diskSize - 1) {
        totalSeekOperations += abs((diskSize - 1) - head); 
        head = diskSize - 1;
    }

    // Moving back to the beginning
    for (auto i = it - 1; i >= requests.begin(); --i) {
        totalSeekOperations += abs(head - *i);
        head = *i;
    }
    return totalSeekOperations;
}

// Function to calculate total seek operations for C-LOOK
int c_look(vector<int> requests, int head) {
    int totalSeekOperations = 0;
    requests.push_back(head);
    sort(requests.begin(), requests.end());

    // Find the starting point of the head
    auto it = find(requests.begin(), requests.end(), head);

    // Moving towards the end of the disk
    for (auto i = it; i != requests.end(); ++i) {
        totalSeekOperations += abs(head - *i);
        head = *i;
    }

    // Move back to the first request if needed
    if (head != requests.front()) {
        totalSeekOperations += abs(head - requests.front());
        head = requests.front();

        // Complete the remaining requests
        for (auto i = requests.begin(); i != it; ++i) {
            totalSeekOperations += abs(head - *i);
            head = *i;
        }
    }

    return totalSeekOperations;
}

int main() {
    int diskSize, numRequests, head;
    
    cout << "Enter the disk size: ";
    cin >> diskSize;
    
    cout << "Enter the number of disk requests: ";
    cin >> numRequests;

    vector<int> requests(numRequests);
    cout << "Enter the disk requests: ";
    for (int i = 0; i < numRequests; ++i) {
        cin >> requests[i];
    }

    cout << "Enter the initial head position: ";
    cin >> head;

    cout << "\nTotal seek operations using SSTF: " << sstf(requests, head) << endl;
    cout << "Total seek operations using SCAN: " << scan(requests, head, diskSize) << endl;
    cout << "Total seek operations using C-LOOK: " << c_look(requests, head) << endl;

    return 0;
}
