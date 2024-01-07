#include "Vector.h"

[[maybe_unused]] void testVector() {
    Vector v1(0.1, 3);
    Vector v2(1, 0.3);
    Vector v3(4, 3);
    Vector v4(21, 5);

    Vector sumVector = v1 + 2*v2 - v3 + v4;
    std::cout << sumVector.toStr() << std::endl;
    std::cout << sumVector.toPolar().toStr() << std::endl;

    std::cout << "---------------" << std::endl;

    Polar sumPolar = v1.toPolar() + v2.toPolar() - v3.toPolar() + v4.toPolar(); //v1.toPolar() + v2.toPolar() - v3.toPolar() +
    std::cout << sumPolar.toCartesian().toStr() << std::endl;
    std::cout << sumPolar.toStr() << std::endl;
}

[[maybe_unused]] void testVectorMethod() {
    Vector v1(1, 1.01);
    Vector v2(-1, 1);
    Vector v3(4, 3);
    Vector v4(21, 5);

    v1 = 1 + v1;

    std::cout << v1;

}

[[maybe_unused]] void testPolar() {
    Polar p1(1, PI_3);
    Polar p2(4, PI2);
    Polar p3(2, PI_2);
    Polar p4(9, PI);

    Vector v1 = p1.toCartesian();
    Vector v2 = p2.toCartesian();
    Vector v3 = p3.toCartesian();
    Vector v4 = p4.toCartesian();

    std::cout << std::setw(20) << std::fixed << std::left << p1 << v1 << std::endl;
    std::cout << std::setw(20) << std::fixed << std::left << p2 << v2 << std::endl;
    std::cout << std::setw(20) << std::fixed << std::left << p3 << v3 << std::endl;
    std::cout << std::setw(20) << std::fixed << std::left << p4 << v4 << std::endl;

    std::cout << "---------------" << std::endl;

    std::cout << v1 << std::endl;
    std::cout << v2 << std::endl;
    std::cout << v3 << std::endl;
    std::cout << v4 << std::endl;

    std::cout << "---------------" << std::endl;

    std::cout << v3.getX() << std::endl;

    std::cout << "---------------" << std::endl;

    Polar sumPolar = p1 + 5*p2 - p3 + p4;
    std::cout << std::setw(20) << std::fixed << std::left << sumPolar.toCartesian() << sumPolar << std::endl;

    Vector sumVector = v1 + 5*v2 - v3 + v4;
    std::cout << std::setw(20) << std::fixed << std::left << sumVector.toPolar() << sumVector << std::endl;

    std::cout << "---------------" << std::endl;
}

std::string printArray(int* arr, int size) {
    std::stringstream ss;
    for (int j = 0; j < size - 1; ++j) {
        ss << arr[j] << ", ";
    }
    ss << arr[size-1];
    return ss.str();
}

int* generateRow(int* previousRow, int size) {
    int* newRow = new int[size - 1];
    for (int i = 0; i < size - 1; ++i) {
        newRow[i] = previousRow[i] + previousRow[i + 1];
    }
    return newRow;
}

int lastThreeDigitsSum(int* arr, int n, int k) {
    int* currentRow = new int[n];
    for (int i = 0; i < n; ++i) {
        currentRow[i] = arr[i];
    }

    for (int i = 1; i <= k; ++i) {
        std::cout <<  printArray(currentRow, n) << std::endl;
        int* nextRow = generateRow(currentRow, n - i + 1);
        std::cout <<  printArray(nextRow, n) << std::endl;
        delete[] currentRow;
        currentRow = nextRow;
    }

    int sum = 0;
    for (int i = 0; i < n - k + 1; ++i) {
        sum += currentRow[i];
    }

    delete[] currentRow;

    return sum % 1000; // Get the last three digits
}

int main() {
    testVectorMethod();

//    int arr[] = {1, 2, 3, 4, 5};
//    int n = sizeof(arr) / sizeof(arr[0]);
//    int k;
//
//    std::cout << "Enter the row number (k): ";
//    std::cin >> k;
//
//    int result = lastThreeDigitsSum(arr, n, k-1);
//
//    std::cout << "The last three digits of the sum of row " << k << " is: " << result << std::endl;

    return 0;
}
