#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <limits>
// Function to get valid input for double values (used for a, b)
bool getDoubleInput(const std::string& prompt, double& value) {
    while (true) {
        std::cout << prompt;
        std::cin >> value;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter a valid number." << std::endl;
        }
        else if (std::cin.get() != '\n') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter only one value." << std::endl;
        }
        else {
            return true;
        }
    }
}

// Function to get valid input for integer values (used for n)
bool getNInput(int& n) {
    while (true) {
        std::cout << "Enter value for n (n > 2): ";
        std::cin >> n;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter a valid integer for n." << std::endl;
        }
        else if (n <= 2) {
            std::cerr << "Invalid input. n must be greater than 2." << std::endl;
        }
        else if (std::cin.get() != '\n') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter only one value for n." << std::endl;
        }
        else {
            return true;
        }
    }
}

// Function to get valid step input ensuring step is in range and positive
bool getStepInput(double a, double b, double& step) {
    while (true) {
        std::cout << "Enter the step value (step > 0 and step <= (b - a)): ";
        std::cin >> step;
        if (std::cin.fail()) {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter a valid number." << std::endl;
        }
        else if (step <= 0) {
            std::cerr << "Invalid input. Step must be greater than 0." << std::endl;
        }
        else if (step > (b - a)) {
            std::cerr << "Invalid input. Step is too large for the given range." << std::endl;
        }
        else if (std::cin.get() != '\n') {
            std::cin.clear();
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
            std::cerr << "Invalid input. Please enter only one value." << std::endl;
        }
        else {
            return true;
        }
    }
}

// Function to calculate y based on the value of x and n
double calculateY(double x, int n) {
    double y = 0.0;
    if (x < 0) {
        for (int i = 2; i <= n; i++) {
            y += pow(i - 3 + x, 2);
        }
    }
    else {
        for (int i = 0; i <= n; i++) {
            double product = 1.0;
            for (int j = 1; j <= n - 1; j++) {
                product *= (i + j) / (2 * pow(1 + x, 2));
            }
            y += product;
        }
    }
    return y;
}

// Function to get user confirmation for saving the result
bool getSaveInput(std::string& saveToFile) {
    while (true) {
        std::cout << "Do you want to save the result to output.txt? (yes/no): ";
        std::cin >> saveToFile;
        if (saveToFile == "yes" || saveToFile == "no") {
            return true;
        }
        else {
            std::cerr << "Invalid input. Please enter 'yes' or 'no'." << std::endl;
        }
    }
}

int main() {
    double a, b, step;
    int n;

    // Input value of a
    if (!getDoubleInput("Enter the start of the range (a): ", a)) return 1;

    // Input value of b with a check to ensure b > a
    do {
        if (!getDoubleInput("Enter the end of the range (b): ", b)) return 1;
        if (b <= a) {
            std::cerr << "Invalid input. 'b' must be greater than 'a'." << std::endl;
        }
    } while (b <= a);

    // Input value of step
    if (!getStepInput(a, b, step)) return 1;

    // Input value of n
    if (!getNInput(n)) return 1;

    std::cout << "Calculating values of y for x in range (" << a << ", " << b << ") with step " << step << "...\n";

    // Iterate over the range (a, b) and calculate y for each x
    for (double x = a; x <= b; x += step) {
        double y = calculateY(x, n);
        std::cout << "For x = " << x << ", y = " << y << std::endl;
    }

    // Option to save the results
    std::string saveToFile;
    if (getSaveInput(saveToFile) && saveToFile == "yes") {
        std::ofstream outputFile("output.txt");
        if (outputFile.is_open()) {
            for (double x = a; x <= b; x += step) {
                double y = calculateY(x, n);
                outputFile << "For x = " << x << ", y = " << y << std::endl;
            }
            outputFile.close();
            std::cout << "Results saved to output.txt." << std::endl;
        }
        else {
            std::cerr << "Unable to open file for writing." << std::endl;
        }
    }
    else {
        std::cout << "Results not saved." << std::endl;
    }

    return 0;
}
