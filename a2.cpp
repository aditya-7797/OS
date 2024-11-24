#include <iostream>
#include <pthread.h>
#include <vector>

#define SIZE 3 // Matrix size (3x3)

std::vector<std::vector<int>> matrix1(SIZE, std::vector<int>(SIZE));
std::vector<std::vector<int>> matrix2(SIZE, std::vector<int>(SIZE));
std::vector<std::vector<int>> result(SIZE, std::vector<int>(SIZE));

// Structure to hold data for each thread
struct ThreadData {
    int row;
    int col;
};

// Function for matrix addition
void* add(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    result[data->row][data->col] = matrix1[data->row][data->col] + matrix2[data->row][data->col];
    delete data; // Free memory for the thread data
    return NULL;
}

// Function for matrix subtraction
void* subtract(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    result[data->row][data->col] = matrix1[data->row][data->col] - matrix2[data->row][data->col];
    delete data;
    return NULL;
}

// Function for matrix multiplication
void* multiply(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    result[data->row][data->col] = 0;
    for (int k = 0; k < SIZE; ++k) {
        result[data->row][data->col] += matrix1[data->row][k] * matrix2[k][data->col];
    }
    delete data;
    return NULL;
}

// Function for matrix division
void* divide(void* arg) {
    ThreadData* data = (ThreadData*)arg;
    if (matrix2[data->row][data->col] != 0) {
        result[data->row][data->col] = matrix1[data->row][data->col] / matrix2[data->row][data->col];
    } else {
        result[data->row][data->col] = 0; // Handle division by zero
    }
    delete data;
    return NULL;
}

// Function to print a matrix
void print_matrix(const std::vector<std::vector<int>>& mat) {
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

int main() {
    pthread_t threads[SIZE][SIZE];

    // Take manual input for matrix1
    std::cout << "Enter elements for Matrix 1 (" << SIZE << "x" << SIZE << "):\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cin >> matrix1[i][j];
        }
    }

    // Take manual input for matrix2
    std::cout << "Enter elements for Matrix 2 (" << SIZE << "x" << SIZE << "):\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            std::cin >> matrix2[i][j];
        }
    }

    // Perform addition
    std::cout << "Performing Addition:\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            ThreadData* data = new ThreadData{i, j};
            pthread_create(&threads[i][j], NULL, add, (void*)data);
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            pthread_join(threads[i][j], NULL);
        }
    }
    print_matrix(result);

    // Perform subtraction
    std::cout << "Performing Subtraction:\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            ThreadData* data = new ThreadData{i, j};
            pthread_create(&threads[i][j], NULL, subtract, (void*)data);
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            pthread_join(threads[i][j], NULL);
        }
    }
    print_matrix(result);

    // Perform multiplication
    std::cout << "Performing Multiplication:\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            ThreadData* data = new ThreadData{i, j};
            pthread_create(&threads[i][j], NULL, multiply, (void*)data);
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            pthread_join(threads[i][j], NULL);
        }
    }
    print_matrix(result);

    // Perform division
    std::cout << "Performing Division:\n";
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            ThreadData* data = new ThreadData{i, j};
            pthread_create(&threads[i][j], NULL, divide, (void*)data);
        }
    }
    for (int i = 0; i < SIZE; ++i) {
        for (int j = 0; j < SIZE; ++j) {
            pthread_join(threads[i][j], NULL);
        }
    }
    print_matrix(result);

    return 0;
}
