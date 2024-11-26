#include "ipz.cpp"
int main()
{
    double a, b, step;
    int n;

    // Input value of a
    if (!getDoubleInput("Enter the start of the range (a): ", a))
        return 1;

    // Input value of b with a check to ensure b > a
    do
    {
        if (!getDoubleInput("Enter the end of the range (b): ", b))
            return 1;
        if (b <= a)
        {
            std::cerr << "Invalid input. 'b' must be greater than 'a'." << std::endl;
        }
    } while (b <= a);

    // Input value of step
    if (!getStepInput(a, b, step))
        return 1;

    // Input value of n
    if (!getNInput(n))
        return 1;

    std::cout << "Calculating values of y for x in range (" << a << ", " << b << ") with step " << step << "...\n";

    // Iterate over the range (a, b) and calculate y for each x
    for (double x = a; x <= b; x += step)
    {
        double y = calculateY(x, n);
        std::cout << "For x = " << x << ", y = " << y << std::endl;
    }
    // Option to save the results
    std::string saveToFile;
    if (getSaveInput(saveToFile) && saveToFile == "yes")
    {
        std::ofstream outputFile("output.txt");
        if (outputFile.is_open())
        {
            for (double x = a; x <= b; x += step)
            {
                double y = calculateY(x, n);
                outputFile << "For x = " << x << ", y = " << y << std::endl;
            }
            outputFile.close();
            std::cout << "Results saved to output.txt." << std::endl;
        }
        else
        {
            std::cerr << "Unable to open file for writing." << std::endl;
        }
    }
    else
    {
        std::cout << "Results not saved." << std::endl;
    }

    return 0;
}
