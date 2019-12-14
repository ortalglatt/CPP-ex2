#include "Fractal.h"
#include <cmath>
#include <iostream>

/**
 * Define the painted cells pattern to print.
 */
const char IN_PATTERN = '#';

/**
 * Define the not painted cells pattern to print.
 */
const char NOT_IN_PATTERN = ' ';

/**
 * Draw the pattern of the fractal.
 */
void Fractal::draw() const
{
    int fractalSize = std::pow(_shapeSize, _deg);
    for (int i = 0; i < fractalSize; i++)
    {
        for (int j = 0; j < fractalSize; j++)
        {
            if (inPattern(i, j))
            {
                std::cout << IN_PATTERN;
            }
            else
            {
                std::cout << NOT_IN_PATTERN;
            }
        }
        std::cout << std::endl;
    }
}

/**
 * @param x The first argument in the point.
 * @param y The second argument on the point.
 * @return True if that point need to be painted in the fractal pattern, false otherwise.
 */
bool Sierpinski::inPattern(int x, int y) const
{
    while (true)
    {
        if (x == 0 || y == 0)
        {
            return true;
        }
        if (x % _shapeSize == 1 && y % _shapeSize == 1)
        {
            return false;
        }
        x /= _shapeSize;
        y /= _shapeSize;
    }
}

/**
 * @param x The first argument in the point.
 * @param y The second argument on the point.
 * @return True if that point need to be painted in the fractal pattern, false otherwise.
 */
bool CantorDust::inPattern(int x, int y) const
{
    while (true)
    {
        if (x == 0 && y == 0)
        {
            return true;
        }
        if (x % _shapeSize == 1 || y % _shapeSize == 1)
        {
            return false;
        }
        x /= _shapeSize;
        y /= _shapeSize;
    }
}
