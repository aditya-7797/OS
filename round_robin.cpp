#include <iostream>
#include <queue>
#include <vector>
using namespace std;

// Structure to store process details
struct Process {
    int pid;         // Process ID
    int arrival;     // Arrival time
    int burst;       // Burst time
    int remaining;   // Remaining burst time
    int completion;  // Completion time
    int turnaround;  // Turnaround time
    int waiting;     // Waiting time
};

void computeTimes(vector<Process> &processes, int timeQuantum) {
    int n = processes.size();
    int currentTime = 0;
    queue<int> readyQueue;

    // Initially push all processes that have arrived at time 0
    for (int i = 0; i < n; i++) {
        if (processes[i].arrival <= currentTime)
            readyQueue.push(i);
    }

    while (!readyQueue.empty()) {
        int idx = readyQueue.front();
        readyQueue.pop();

        if (processes[idx].remaining > timeQuantum) {
            currentTime += timeQuantum;
            processes[idx].remaining -= timeQuantum;
        } else {
            currentTime += processes[idx].remaining;
            processes[idx].remaining = 0;
            processes[idx].completion = currentTime;
            processes[idx].turnaround = processes[idx].completion - processes[idx].arrival;
            processes[idx].waiting = processes[idx].turnaround - processes[idx].burst;
        }

        // Check if new processes arrive at currentTime and add to the ready queue
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && processes[i].remaining > 0) {
                bool found = false;
                queue<int> tempQueue = readyQueue;
                while (!tempQueue.empty()) {
                    if (tempQueue.front() == i) {
                        found = true;
                        break;
                    }
                    tempQueue.pop();
                }
                if (!found) {
                    readyQueue.push(i);
                }
            }
        }

        if (processes[idx].remaining > 0) {
            readyQueue.push(idx);
        }
    }
}

void display(const vector<Process> &processes) {
    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto &p : processes) {
        cout << "P" << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.completion
             << "\t\t" << p.turnaround << "\t\t" << p.waiting << "\n";
    }
}

int main() {
    int n, timeQuantum;
    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the time quantum: ";
    cin >> timeQuantum;

    vector<Process> processes(n);

    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Process " << i + 1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst;
        processes[i].remaining = processes[i].burst;
    }

    computeTimes(processes, timeQuantum);
    display(processes);

    return 0;
}
