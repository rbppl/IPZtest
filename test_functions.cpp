#include <iostream>
#include <sstream>
#include <cassert>
#include <cmath>
#include <fstream>
#include <string>
#include <limits>
#include "functions.h"

void testGetDoubleInput()
{
    double value;
    std::istringstream input("5.5\n");
    std::cin.rdbuf(input.rdbuf()); // Подставляем ввод в std::cin
    bool result = getDoubleInput("Enter a number: /n ", value);
    if (result && value == 5.5)
    {
        std::cout << "testGetDoubleInput() passed\n"
                  << std::endl;
    }
    else
    {
        std::cout << "testGetDoubleInput() failed\n"
                  << std::endl;
    }
}

void testGetNInput()
{
    int n;
    std::istringstream input("3\n");
    std::cin.rdbuf(input.rdbuf());
    bool result = getNInput(n);
    if (result && n == 3)
    {
        std::cout << "testGetNInput() passed\n"
                  << std::endl;
    }
    else
    {
        std::cout << "testGetNInput() failed\n"
                  << std::endl;
    }
}

void testGetStepInput()
{
    double step;
    std::istringstream input("0.5\n");
    std::cin.rdbuf(input.rdbuf());
    bool result = getStepInput(0, 5, step);
    if (result && step == 0.5)
    {
        std::cout << "testGetStepInput() passed \n"
                  << std::endl;
    }
    else
    {
        std::cout << "testGetStepInput() failed \n"
                  << std::endl;
    }
}

void testCalculateY()
{
    double y = calculateY(-1, 3);
    if (fabs(y - 5.0) < 1e-6)
    {
        std::cout << "testCalculateY() passed \n"
                  << std::endl;
    }
    else
    {
        std::cout << "testCalculateY() failed \n"
                  << std::endl;
    }
}

void testGetSaveInput()
{
    std::string saveToFile;
    std::istringstream input("yes\n");
    std::cin.rdbuf(input.rdbuf());
    bool result = getSaveInput(saveToFile);
    if (result && saveToFile == "yes")
    {
        std::cout << "testGetSaveInput() passed\n"
                  << std::endl;
    }
    else
    {
        std::cout << "testGetSaveInput() failed\n"
                  << std::endl;
    }
}

void testMaint()
{
    // Симуляция ввода с помощью istringstream
    std::istringstream input(
        "1.0\n" // Ввод для 'a'
        "5.0\n" // Ввод для 'b'
        "0.5\n" // Ввод для 'step'
        "3\n"   // Ввод для 'n'
        "yes\n" // Ввод для сохранения в файл
    );

    std::ostringstream output;                      // Перехват вывода в строку
    std::streambuf *cinBackup = std::cin.rdbuf();   // Сохраняем оригинальный std::cin
    std::streambuf *coutBackup = std::cout.rdbuf(); // Сохраняем оригинальный std::cout

    std::cin.rdbuf(input.rdbuf());   // Подменяем std::cin
    std::cout.rdbuf(output.rdbuf()); // Подменяем std::cout

    // Вызываем функцию main (maint), которая будет использовать подмененные потоки
    maint();

    // Восстанавливаем оригинальные потоки
    std::cin.rdbuf(cinBackup);
    std::cout.rdbuf(coutBackup);

    // Ожидаемый вывод, с учетом точности
    std::string expectedOutput =
        "For x = 1, y = 0.625\n"
        "For x = 1.5, y = 0.256\n"
        "For x = 2, y = 0.123457\n"
        "For x = 2.5, y = 0.0666389\n"
        "For x = 3, y = 0.0390625\n"
        "For x = 3.5, y = 0.0243865\n"
        "For x = 4, y = 0.016\n"
        "For x = 4.5, y = 0.0109282\n"
        "For x = 5, y = 0.00771605\n"
        "Do you want to save the result to output.txt? (yes/no): Results saved to output.txt.\n";

    // Убираем из фактического вывода лишние строки, связанные с запросом на сохранение
    size_t startPos = output.str().find("For x = 1");
    std::string actualOutput = output.str().substr(startPos);
    size_t endPos = actualOutput.find("Results saved to output.txt.");

    // Проверка вывода с учетом точности
    if (actualOutput == expectedOutput)
    {
        std::cout << "testMaint() passed \n"
                  << std::endl;
    }
    else
    {
        std::cout << "testMaint() failed \n"
                  << std::endl;
        std::cout << "Expected:\n"
                  << expectedOutput << std::endl;
        std::cout << "Actual:\n"
                  << actualOutput << std::endl;
    }

    // Проверка, что файл output.txt был создан
    std::ifstream outputFile("output.txt");
    if (outputFile.is_open())
    {
        std::cout << "testMaint() - file creation passed \n"
                  << std::endl;
        outputFile.close();
    }
    else
    {
        std::cout << "testMaint() - file creation failed\n"
                  << std::endl;
    }
}

int main()
{
    // Запуск тестов
    testGetDoubleInput();
    testGetStepInput();
    testGetNInput();
    testCalculateY();
    testGetSaveInput();
    testMaint();

    std::cout << "All tests finished!\n"
              << std::endl;
    return 0;
}
