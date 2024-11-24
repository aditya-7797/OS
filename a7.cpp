#include <iostream>
#include <vector>
using namespace std;

bool isSafeState(vector<vector<int>>& allocation, vector<vector<int>>& max, vector<int>& available, int n, int m) {
    vector<int> work = available;
    vector<bool> finish(n, false);
    vector<int> safeSequence;
    bool found;

    for (int k = 0; k < n; k++) {
        found = false;
        for (int i = 0; i < n; i++) {
            if (!finish[i]) {
                bool possible = true;
                for (int j = 0; j < m; j++) {
                    if (max[i][j] - allocation[i][j] > work[j]) {
                        possible = false;
                        break;
                    }
                }

                if (possible) {
                    for (int j = 0; j < m; j++) {
                        work[j] += allocation[i][j];
                    }
                    finish[i] = true;
                    found = true;
                    safeSequence.push_back(i);
                }
            }
        }

        if (!found) {
            return false; // System is not in a safe state
        }
    }

    // If we reach here, system is in a safe state
    cout << "System is in a safe state.\nSafe sequence: ";
    for (int i = 0; i < safeSequence.size(); i++) {
        cout << safeSequence[i] << " ";
    }
    cout << endl;

    return true;
}

int main() {
    int n, m; // Number of processes and resource types

    cout << "Enter the number of processes: ";
    cin >> n;
    cout << "Enter the number of resource types: ";
    cin >> m;

    vector<vector<int>> allocation(n, vector<int>(m));
    vector<vector<int>> max(n, vector<int>(m));
    vector<int> available(m);

    cout << "Enter the allocation matrix (row-wise):\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": ";
        for (int j = 0; j < m; j++) {
            cin >> allocation[i][j];
        }
    }

    cout << "Enter the maximum demand matrix (row-wise):\n";
    for (int i = 0; i < n; i++) {
        cout << "Process " << i + 1 << ": ";
        for (int j = 0; j < m; j++) {
            cin >> max[i][j];
        }
    }

    cout << "Enter the available resources:\n";
    for (int i = 0; i < m; i++) {
        cin >> available[i];
    }

    if (!isSafeState(allocation, max, available, n, m)) {
        cout << "System is not in a safe state.\n";
    }

    return 0;
}
