#include <iostream>
#include <vector>
#include <algorithm>
#include <climits>
using namespace std;

// Structure to store process details
struct Process {
    int pid;         // Process ID
    int arrival;     // Arrival time
    int burst;       // Burst time
    int remaining;   // Remaining burst time
    int priority;    // Priority
    int completion;  // Completion time
    int turnaround;  // Turnaround time
    int waiting;     // Waiting time
};

void computeTimes(vector<Process> &processes) {
    int n = processes.size();
    int currentTime = 0;
    int completedCount = 0;

    while (completedCount < n) {
        int highestPriorityIndex = -1;
        int highestPriority = INT_MAX;

        // Find the process with the highest priority (smallest priority number)
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && processes[i].remaining > 0 &&
                processes[i].priority < highestPriority) {
                highestPriority = processes[i].priority;
                highestPriorityIndex = i;
            }
        }

        if (highestPriorityIndex == -1) {
            // No process is ready to execute, increment time
            currentTime++;
        } else {
            // Execute the process for 1 unit of time
            processes[highestPriorityIndex].remaining--;
            currentTime++;

            // If the process is finished
            if (processes[highestPriorityIndex].remaining == 0) {
                completedCount++;
                processes[highestPriorityIndex].completion = currentTime;
                processes[highestPriorityIndex].turnaround =
                    processes[highestPriorityIndex].completion - processes[highestPriorityIndex].arrival;
                processes[highestPriorityIndex].waiting =
                    processes[highestPriorityIndex].turnaround - processes[highestPriorityIndex].burst;
            }
        }
    }
}

void display(const vector<Process> &processes) {
    cout << "\nProcess\tArrival\tBurst\tPriority\tCompletion\tTurnaround\tWaiting\n";
    for (const auto &p : processes) {
        cout << "P" << p.pid << "\t" << p.arrival << "\t" << p.burst << "\t" << p.priority
             << "\t\t" << p.completion << "\t\t" << p.turnaround << "\t\t" << p.waiting << "\n";
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    cout << "Enter arrival time, burst time, and priority for each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Process " << i + 1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst >> processes[i].priority;
        processes[i].remaining = processes[i].burst;
    }

    computeTimes(processes);
    display(processes);

    return 0;
}
