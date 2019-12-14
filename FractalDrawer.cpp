#include <iostream>
#include <fstream>
#include <vector>
#include "Fractal.h"

/**
 * Defines the expected number of arguments.
 */
const int ARGS_AMOUNT = 2;
/**
 * Defines the index of the path argument.
 */
const int PATH_ARG = 1;
/**
 * Defines the usage massage (printed when the arguments amount is wrong).
 */
const char* USAGE_MSG = "Usage: FractalDrawer <file path>";
/**
 * Defines the invalid input massage.
 */
const char* INVALID_MSG = "Invalid input";
/**
 * Defines the allocation failure massage.
 */
const char* MEMORY_MSG = "Memory allocation failed";
/**
 * Define the index of the fractal number in the line.
 */
const int FRACTAL = 0;
/**
 * Defines the index of the separator in the line.
 */
const int SEPARATOR = 1;
/**
 * Defines the index of the fractal degree in the line.
 */
const int DEGREE = 2;
/**
 * Defines the expected seperator in the line.
 */
const char LINE_SEP = ',';
/**
 * Defines the expected line length.
 */
const int LINE_LENGTH = 3;
/**
 * Defines a zero char.
 */
const char ZERO_CHAR = '0';
/**
 * Defines the number of Sierpinski carpet fractal.
 */
const int SIERPINSKI_CARPET = 1;
/**
 * Defines the number of Sierpinski sieve fractal.
 */
const int SIERPINSKI_SIEVE = 2;
/**
 * Defines the number of Cantor dust fractal.
 */
const int CANTOR_DUST = 3;
/**
 * Define the shape size of Sierpinski carpet fractal.
 */
const int CARPET_SIZE = 3;
/**
 * Define the shape size of Sierpinski sieve fractal.
 */
const int SIEVE_SIZE = 2;
/**
 * Defines the minimum degree of a fractal.
 */
const int MIN_DEG = 1;
/**
 * Defines the maximum degree of a fractal.
 */
const int MAX_DEG = 6;

/**
 * An invalid input exception class
 */
class InvalidInputException : public std::exception{};

/**
 * This function allocate memory. If the allocation failed, it will throw an exception.
 * The function assume that the arguments are legal.
 * @param fractal number of fractal to create.
 * @param degree degree of the fractal to create.
 * @return The fractal that fits the given fractal number, with the given degree.
 */
Fractal *createFractal(int fractal, int degree)
{
    switch (fractal)
    {
        case SIERPINSKI_CARPET:
            return new Sierpinski(degree, CARPET_SIZE);
        case SIERPINSKI_SIEVE:
            return new Sierpinski(degree, SIEVE_SIZE);
        case CANTOR_DUST:
            return new CantorDust(degree);
        default:
            return nullptr;
    }
}

/**
 * Deletes all the fractal that in the given vectoe.
 * @param fractals A reference to fractal pointers vector.
 */
void deleteFractals(std::vector<Fractal*> &fractals)
{
    for (Fractal* f : fractals)
    {
        delete f;
    }
}

/**
 * Parse the given file and put all the fractals in the given vector.
 * If the file is invalid or the memory allocation failed, it will throw the relevant exception.
 * @param inFile The file to parse.
 * @param fractals An empty fractal pointers vector.
 */
void fileParsing(std::ifstream& inFile, std::vector<Fractal*> &fractals)
{
    if (!inFile)
    {
        throw InvalidInputException();
    }
    std::string line;
    while (getline(inFile, line))
    {
        int fractal = line[FRACTAL] - ZERO_CHAR, degree = line[DEGREE] - ZERO_CHAR;
//        if (line.length() != LINE_LENGTH || line[SEPARATOR] != LINE_SEP || fractal > CANTOR_DUST ||
//            fractal < SIERPINSKI_CARPET || degree < MIN_DEG || degree > MAX_DEG)
        if ((line.length() != LINE_LENGTH && line[3] != '\r') || line[SEPARATOR] != LINE_SEP || fractal > CANTOR_DUST ||
            fractal < SIERPINSKI_CARPET || degree < MIN_DEG || degree > MAX_DEG)
        {
            deleteFractals(fractals);
            throw InvalidInputException();
        }
        try
        {
            fractals.push_back(createFractal(fractal, degree));
        }
        catch (std::bad_alloc&)
        {
            deleteFractals(fractals);
            throw;
        }
    }
}

/**
 * Draw all the fractals from the last to the first one.
 * @param fractals A reference to fractal pointers vector.
 */
void drawFractals(std::vector<Fractal*> &fractals)
{
    for (int i = (int) fractals.size() - 1; i >= 0; i--)
    {
        fractals[i]->draw();
        std::cout << std::endl;
    }
}

/**
 * Runs the whole program, and print the fractals if the input is valid.
 * @param argc The number of arguments.
 * @param argv An array of the given arguments.
 * @return 0.
 */
int main(int argc, char *argv[])
{
    if (argc != ARGS_AMOUNT)
    {
        std::cerr << USAGE_MSG << std::endl;
        return EXIT_FAILURE;
    }
    std::ifstream inFile(argv[PATH_ARG]);
    std::vector<Fractal*> fractals;
    try
    {
        fileParsing(inFile, fractals);
    }
    catch (InvalidInputException&)
    {
        std::cerr << INVALID_MSG << std::endl;
        return EXIT_FAILURE;
    }
    catch (std::bad_alloc&)
    {
        std::cerr << MEMORY_MSG << std::endl;
        return EXIT_FAILURE;
    }
    drawFractals(fractals);
    deleteFractals(fractals);
    return 0;
}