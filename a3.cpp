#include <iostream>
#include <vector>
#include <unistd.h>
#include <sys/wait.h>
#include <algorithm>
#include <cstdlib>

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

void insertionSort(std::vector<int>& arr) {
    int n = arr.size();
    for (int i = 1; i < n; ++i) {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
}

int main() {
    std::vector<int> numbers;
    int num;
    
    std::cout << "Enter integers to sort (enter any non-integer to stop): " << std::endl;
    while (std::cin >> num) {
        numbers.push_back(num);
    }
    
    pid_t pid = fork();
    
    if (pid < 0) {
        std::cerr << "Fork failed!" << std::endl;
        return 1;
    }
    else if (pid == 0) {
        // Child process
        std::cout << "Child process started, PID: " << getpid() << std::endl;
        insertionSort(numbers);
        std::cout << "Child process (sorted using Insertion Sort): ";
        for (int n : numbers) {
            std::cout << n << " ";
        }
        std::cout << std::endl;

        // Simulate a delay to keep the child running longer
        sleep(10);
        std::cout << "Child process finished." << std::endl;
        exit(0);
    }
    else {
        // Parent process
        std::cout << "Parent process started, PID: " << getpid() << std::endl;
        bubbleSort(numbers);
        std::cout << "Parent process (sorted using Bubble Sort): ";
        for (int n : numbers) {
            std::cout << n << " ";
        }
        std::cout << std::endl;

        // Demonstrate the zombie state
        std::cout << "Parent process sleeping to create a zombie state." << std::endl;
        sleep(5);

        // Call wait to clean up the child process
        wait(NULL);

        std::cout << "Parent process finished, child process should be reaped now." << std::endl;

        // Simulate parent process exiting early (orphan state)
        std::cout << "Parent process exiting, leaving child as orphan if it's still running." << std::endl;
        exit(0);
    }

    return 0;
}
