//
// Created by Hà Tường Nguyên on 12/28/23.
//

#include "main.h"

void test_0() {
    tns::tensor<int> X(10, 10, -9, 9);
    tns::tensor<int> Y;
    tns::tensor<double> w_0(10, 784, -0.5, 0.5);
    tns::tensor<double> x_0(784, 10, 0, 1);
    tns::tensor<double> b_0(10, 1, -0.5, 0.5);

    tns::tensor<double> w_1(100, 100, -100, 100);
    tns::tensor<double> b_1(100, 500, 0, 100);

    auto ReUL = [](double x) {
        return (x > 0) ? x : 0;
    };

    Y = X.elementWise(ReUL);
    X.display();
    hRule(3);
    Y.display();
    hRule(3);
    std::cout << "Same size: " << Y.sameSize(X) << std::endl;

//    std::cout << "A * B = " << std::endl;
//    auto start = std::chrono::high_resolution_clock::now();
//    X = A * B;
//    auto end = std::chrono::high_resolution_clock::now();
//    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);
//    std::cout << X;

//    std::cout << "\nDuration of a matrix multiplication: " << YELLOW << duration.count() << RESET << " µs" << std::endl;
}

void test_1() {
    std::string fileCSV = "/test.csv";

    tns::tensor<double> X;

    auto start = std::chrono::high_resolution_clock::now();
    X = tns::tensor<double>::read_csv(fileCSV, 50, 10, 15);
    auto end = std::chrono::high_resolution_clock::now();
    auto duration = std::chrono::duration_cast<std::chrono::microseconds>(end - start);

    hRule(5);
    std::cout << std::setprecision(15) << X;
    hRule(5);

    std::cout << X(0, 0) << std::endl;

    std::cout << "\nDuration of a static tns::tensor::read_csv(): " << YELLOW << duration.count() << RESET << " µs"
              << std::endl;

}

int main() {
    std::cout << GREEN << "Starting the program!" << RESET << std::endl;
    std::cout << MAGENTA << "---------------------------" << RESET << std::endl;

    double timeExe = executeTime(test_1);

    std::cout << MAGENTA << "---------------------------" << RESET << std::endl;
    std::cout << GREEN << "Execute success in " << timeExe << " µs" << RESET << std::endl;

    return 0;
}