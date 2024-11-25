#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Structure to store process details
struct Process {
    int pid;         // Process ID
    int arrival;     // Arrival time
    int burst;       // Burst time
    int completion;  // Completion time
    int turnaround;  // Turnaround time
    int waiting;     // Waiting time
};

// Comparator for sorting by arrival time
bool compareArrival(const Process &a, const Process &b) {
    return a.arrival < b.arrival;
}

void computeTimes(vector<Process> &processes) {
    int n = processes.size();
    int currentTime = 0;

    for (auto &p : processes) {
        if (currentTime < p.arrival)
            currentTime = p.arrival; // Wait for the process to arrive

        currentTime += p.burst;
        p.completion = currentTime;
        p.turnaround = p.completion - p.arrival;
        p.waiting = p.turnaround - p.burst;
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
    int n;
    cout << "Enter the number of processes: ";
    cin >> n;

    vector<Process> processes(n);

    cout << "Enter arrival time and burst time for each process:\n";
    for (int i = 0; i < n; i++) {
        processes[i].pid = i + 1;
        cout << "Process " << i + 1 << ": ";
        cin >> processes[i].arrival >> processes[i].burst;
    }

    // Sort processes by arrival time
    sort(processes.begin(), processes.end(), compareArrival);

    computeTimes(processes);
    display(processes);

    return 0;
}
