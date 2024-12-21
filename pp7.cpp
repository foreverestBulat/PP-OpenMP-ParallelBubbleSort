#include <iostream>
#include <omp.h>
#include <cstdlib>
#include <chrono>
#include <omp.h>
#include <cmath>
#include <random>
#include <vector>

using namespace std;
using namespace std::chrono;

void bubbleSortParallel(std::vector<int>& arr) 
{
    int n = arr.size();

    // Четно-нечетная сортировка
    for (int i = 0; i < n; i++) 
    {
        // Определяем фазу (четная или нечетная)
        if (i % 2 == 0) 
        {
            // Четная фаза: обрабатываем пары (0,1), (2,3), ...
#pragma omp parallel for
            for (int j = 0; j < n - 1; j += 2) 
            {
                if (arr[j] > arr[j + 1]) 
                {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
        else 
        {
            // Нечетная фаза: обрабатываем пары (1,2), (3,4), ...
#pragma omp parallel for
            for (int j = 1; j < n - 1; j += 2) 
            {
                if (arr[j] > arr[j + 1]) 
                {
                    std::swap(arr[j], arr[j + 1]);
                }
            }
        }
    }
}

void printArray(const std::vector<int>& arr) 
{
    for (int num : arr) 
    {
        std::cout << num << " ";
    }
    std::cout << std::endl;
}

vector<int> generateRandomArray(int n) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dist(0, 100);

    vector<int> arr(n);
    for (int i = 0; i < n; i++) 
    {
        arr[i] = dist(gen);
    }
    return arr;
}

void bubbleSort(std::vector<int>& arr) {
    int n = arr.size();
    bool swapped;
    for (int i = 0; i < n - 1; i++) {
        swapped = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
                swapped = true;
            }
        }
        if (!swapped)
            break;
    }
}

int main() 
{
    std::vector<int> arr = generateRandomArray(50000);

    std::cout << "Array: ";

    double start = omp_get_wtime();
    bubbleSort(arr);
    double end = omp_get_wtime();


    std::cout << "Time: " << (end - start) << " second" << std::endl;

    arr = generateRandomArray(50000);

    start = omp_get_wtime();
    bubbleSortParallel(arr);
    end = omp_get_wtime();

    std::cout << "Sort Array: ";

    std::cout << "Time: " << (end - start) << " second" << std::endl;

    return 0;
}