// / / / / / integration space : 

#include <iostream>
#include <vector >
#include <thread>
#include <chrono>
#include <algorithm>

// -=-=-=-=-=-=-=-===-=-=-c=-==-=-=-==-=-
using namespace std;
// -=-=-=-=-=-=-=-===-=-=-=-==-=-=-==-=-




//int binarySearch(const vector<int>& arr, int target) {
//    int left = 0;
//    int right = arr.size() - 1;
//
//    while (left <= right) {
//        int mid = left + (right - left) / 2;
//
//        // Проверка среднего элемента
//        if (arr[mid] == target) {
//            return mid;
//        }
//
//        // Если искомое значение меньше среднего элемента,
//        // продолжить поиск в левой половине массива
//        if (arr[mid] > target) {
//            right = mid - 1;
//        }
//        // Если искомое значение больше среднего элемента,
//        // продолжить поиск в правой половине массива
//        else {
//            left = mid + 1;
//        }
//    }
//
//    // Если элемент не найден, вернуть -1
//    return -1;
//}
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//
//    vector<int> sortedArray = { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19 , 20 ,
//                                  21, 23, 43, 54 , 1324, 4234,5476, 3421,
//                                  143, 34,324 , 224, 234, 233, 234, 123,453 ,
//                                  56, 45,87,4,234,62,31, 89767, 1234, 1231, 54212 };
//    int target = 7;
//
//    int result = binarySearch(sortedArray, target);
//
//    if (result != -1) {
//        cout << "Элемент найден на индексе: " << result << std::endl;
//    }
//    else {
//        cout << "Элемент не найден" << std::endl;
//    }
//
//    return 0;
//}



// Одновременное выполнение двух различных поисковых подходов. 


 //Линейный поиск
//void linearSearch(const vector<int>& arr, int target) {
//    for (size_t i = 0; i < arr.size(); ++i) {
//        if (arr[i] == target) {
//            std::cout << "Линейный поиск: Элемент найден на индексе " << i << std::endl;
//            return;
//        }
//    }
//    std::cout << "Линейный поиск: Элемент не найден" << std::endl;
//}
//
//// Бинарный поиск
//void binarySearch(const std::vector<int>& arr, int target) {
//    int left = 0, right = arr.size() - 1;
//    while (left <= right) {
//        int mid = left + (right - left) / 2;
//        if (arr[mid] == target) {
//            cout << "Бинарный поиск: Элемент найден на индексе " << mid << std::endl;
//            return;
//        }
//        else if (arr[mid] < target) {
//            left = mid + 1;
//        }
//        else {
//            right = mid - 1;
//        }
//    }
//    cout << "Бинарный поиск: Элемент не найден" << std::endl;
//}
//
//int main() {
//    setlocale(LC_ALL, "Russian");
//    vector<int> arr =
//    { 1, 3, 5, 7, 9, 11, 13, 15, 17, 19,20,6564,34,35,
//      21, 23, 43, 54 , 1324, 4234,5476, 3421,34,65,45,
//      143, 34,324 , 224, 234, 233, 234, 123,453,23434,
//      56, 45,87,4,234,62,31, 89767, 1234, 1231, 54212, 
//    };
//   
//    
//    int target ;
//    cout << "Enter target : "; cin >> target;
//
//    // Запускаем оба поиска в разных потоках
//    thread t1(linearSearch, std::cref(arr), target);
//    thread t2(binarySearch, std::cref(arr), target);
//
//    // Ожидаем завершения потоков
//    t1.join();
//    t2.join();
//
//    return 0;
//}




// ...............................................................
// ...............................................................




// Binary Search
int binarySearch(const std::vector<int>& arr, int target) {
    int left = 0, right = arr.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;

        if (arr[mid] == target) {
            return mid; // Element found
        }
        else if (arr[mid] < target) {
            left = mid + 1; // Search the right half
        }
        else {
            right = mid - 1; // Search the left half
        }
    }

    return -1; // Element not found
}

// Linear Search
int linearSearch(const std::vector<int>& arr, int target) {
    for (size_t i = 0; i < arr.size(); ++i) {
        if (arr[i] == target) {
            return i;
        }
    }
    return -1;
}

// Function for binary search flow
void binarySearchThread(const std::vector<int>& arr, int target) {
    auto start = std::chrono::high_resolution_clock::now();
    int result = binarySearch(arr, target);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    if (result != -1) {
        std::cout << "[Binary search] Element found on the index : " << result << ", time : " << duration.count() << " seconds" << std::endl;
    }
    else {
        std::cout << "[Binary search] Item not found, time :  " << duration.count() << " seconds" << std::endl;
    }
}

// Function for linear search flow
void linearSearchThread(const std::vector<int>& arr, int target) {
    auto start = std::chrono::high_resolution_clock::now();
    int result = linearSearch(arr, target);
    auto end = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> duration = end - start;
    if (result != -1) {
        std::cout << "[Linear search] Element found on index : " << result << ", time : " << duration.count() << " seconds" << std::endl;
    }
    else {
        std::cout << "[Linear search] Item not found, time : " << duration.count() << " seconds" << std::endl;
    }
}

int main() {
    std::vector<int> arr(1000000); // Array of 1 million elements
    for (int i = 0; i < 1000000; ++i) {
        arr[i] = i * 2; // Even numbers
    }

    int target = 987654; // Seeking value

    // Start two threads
    thread binaryThread(binarySearchThread, ref(arr), target); 
    thread linearThread(linearSearchThread, ref(arr), target); 

    // Wait for the threads to complete
    binaryThread.join();
    linearThread.join();

    return 0;
}






