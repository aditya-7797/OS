#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <queue>
#include<climits>

using namespace std;

// Function to check if a page is present in a frame
bool isPagePresent(const vector<int>& frames, int page) {
    return find(frames.begin(), frames.end(), page) != frames.end();
}

// Function to find the page to replace in the Optimal algorithm
int findOptimalPageToReplace(const vector<int>& frames, const vector<int>& referenceString, int currentIndex) {
    int farthest = currentIndex;
    int pageToReplace = -1;
    
    for (int frame : frames) {
        int nextUse = INT_MAX;
        for (int j = currentIndex + 1; j < referenceString.size(); ++j) {
            if (frame == referenceString[j]) {
                nextUse = j;
                break;
            }
        }
        if (nextUse > farthest) {
            farthest = nextUse;
            pageToReplace = frame;
        }
    }
    return pageToReplace;
}

// Function for FIFO Page Replacement Algorithm
int fifoPageFaults(const vector<int>& referenceString, int framesCount) {
    queue<int> frames;
    unordered_map<int, bool> inFrame;
    int pageFaults = 0;
    
    for (int page : referenceString) {
        if (inFrame[page] == false) {
            if (frames.size() == framesCount) {
                int removedPage = frames.front();
                frames.pop();
                inFrame[removedPage] = false;
            }
            frames.push(page);
            inFrame[page] = true;
            pageFaults++;
        }
    }
    return pageFaults;
}

// Function for LRU Page Replacement Algorithm
int lruPageFaults(const vector<int>& referenceString, int framesCount) {
    vector<int> frames;
    unordered_map<int, int> lastUsed;
    int pageFaults = 0;
    
    for (int i = 0; i < referenceString.size(); ++i) {
        int page = referenceString[i];
        
        if (!isPagePresent(frames, page)) {
            if (frames.size() == framesCount) {
                int lruPage = frames[0];
                for (int frame : frames) {
                    if (lastUsed[frame] < lastUsed[lruPage]) {
                        lruPage = frame;
                    }
                }
                // Replace LRU page with current page
                replace(frames.begin(), frames.end(), lruPage, page);
            } else {
                frames.push_back(page);
            }
            pageFaults++;
        }
        lastUsed[page] = i;
    }
    return pageFaults;
}

// Function for Optimal Page Replacement Algorithm
int optimalPageFaults(const vector<int>& referenceString, int framesCount) {
    vector<int> frames;
    int pageFaults = 0;
    
    for (int i = 0; i < referenceString.size(); ++i) {
        int page = referenceString[i];
        
        if (!isPagePresent(frames, page)) {
            if (frames.size() == framesCount) {
                int pageToReplace = findOptimalPageToReplace(frames, referenceString, i);
                replace(frames.begin(), frames.end(), pageToReplace, page);
            } else {
                frames.push_back(page);
            }
            pageFaults++;
        }
    }
    return pageFaults;
}

int main() {
    int framesCount, referenceLength;
    cout << "Enter the number of frames: ";
    cin >> framesCount;
    
    cout << "Enter the length of the reference string: ";
    cin >> referenceLength;
    
    vector<int> referenceString(referenceLength);
    cout << "Enter the reference string: ";
    for (int i = 0; i < referenceLength; ++i) {
        cin >> referenceString[i];
    }

    cout << "\nPage Faults using FIFO: " << fifoPageFaults(referenceString, framesCount) << endl;
    cout << "Page Faults using LRU: " << lruPageFaults(referenceString, framesCount) << endl;
    cout << "Page Faults using Optimal: " << optimalPageFaults(referenceString, framesCount) << endl;

    return 0;
}
