// functions.h
#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <string>

// Function declarations
bool getDoubleInput(const std::string &prompt, double &value);
bool getNInput(int &n);
bool getStepInput(double a, double b, double &step);
double calculateY(double x, int n);
bool getSaveInput(std::string &saveToFile);
int maint();

#endif // FUNCTIONS_H
