#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Process {
    int pid;         // Process ID
    int arrival;     // Arrival time
    int burst;       // Burst time
    int remaining;   // Remaining burst time
    int completion;  // Completion time
    int turnaround;  // Turnaround time
    int waiting;     // Waiting time
};

void computeTimes(vector<Process> &processes) {
    int n = processes.size();
    int completed = 0, currentTime = 0, minIndex = -1;
    bool found;

    while (completed < n) {
        found = false;
        int minRemaining = INT_MAX;

        // Find the process with the shortest remaining time at the current time
        for (int i = 0; i < n; i++) {
            if (processes[i].arrival <= currentTime && processes[i].remaining > 0) {
                if (processes[i].remaining < minRemaining) {
                    minRemaining = processes[i].remaining;
                    minIndex = i;
                    found = true;
                }
            }
        }

        if (found) {
            // Execute the selected process for one unit of time
            currentTime++;
            processes[minIndex].remaining--;

            // If the process is completed
            if (processes[minIndex].remaining == 0) {
                completed++;
                processes[minIndex].completion = currentTime;
                processes[minIndex].turnaround = processes[minIndex].completion - processes[minIndex].arrival;
                processes[minIndex].waiting = processes[minIndex].turnaround - processes[minIndex].burst;
            }
        } else {
            // No process is ready, increment time
            currentTime++;
        }
    }
}

void display(const vector<Process> &processes) {
    cout << "\nProcess\tArrival\tBurst\tCompletion\tTurnaround\tWaiting\n";
    for (const auto &p : processes) {
        cout << "P" << p.pid << "\t" << p.arrival << "\t" << p.burst
             << "\t" << p.completion << "\t\t" << p.turnaround
             << "\t\t" << p.waiting << "\n";
    }
}

int main() {
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Process " << i + 1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst;
        processes[i].remaining = processes[i].burst;
    }

    computeTimes(processes);
    display(processes);

    return 0;
}
