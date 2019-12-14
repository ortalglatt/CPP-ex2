#ifndef EX2_FRACTAL_H
#define EX2_FRACTAL_H

#include <string>

/**
 * Defines the Cantor dust fractal shape size.
 */
const int CANTOR_SIZE = 3;

/**
 * Fractal class that contains a degree and a shape size.
 */
class Fractal
{
protected:
    int _deg;
    int _shapeSize;

public:
    /**
     * Two parameters constructor.
     * @param degree The degree of the fractal, needs to be between 1 to 6.
     * @param size The size of the fractal pattern.
     */
    Fractal(const int& degree, const int& size) : _deg(degree), _shapeSize(size) {}

    /**
     * Default copy constructor of Fractal.
     * @param other The Fractal object to copy.
     */
    Fractal(const Fractal& other) = default;

    /**
     * Default move constructor of Fractal.
     * @param other The Fractal object to move.
     */
    Fractal(Fractal && other) noexcept = default;

    /**
     * Default destructor of Fractal.
     */
    virtual ~Fractal() = default;

    /**
     * Default copy assignment operator of fractal.
     * @param other The Fractal object to copy.
     * @return The current Fractal object.
     */
    Fractal& operator=(const Fractal& other) = default;

    /**
     * Default move assignment operator of fractal.
     * @param other The Fractal object to move.
     * @return The current Fractal object.
     */
    Fractal& operator=(Fractal && other) noexcept = default;

    /**
     * Draw the pattern of the fractal.
     */
    void draw() const;

    /**
     * @param x The first argument in the point.
     * @param y The second argument on the point.
     * @return True if that point need to be painted in the fractal pattern, false otherwise.
     */
    virtual bool inPattern(int x, int y) const = 0;
};

/**
 * Sierpinski (carpet or sieve) fractal class.
 */
class Sierpinski: public Fractal
{
public:
    /**
     * Two arguments constructor.
     * @param degree The degree of the fractal, needs to be between 1 to 6.
     * @param size The size of the fractal pattern. If the fractal is carpet - it will be 3, if it's
     *             a sieve - it will be 2.
     */
    Sierpinski(const int& degree, const int& size) : Fractal(degree, size) {}

    /**
     * Copy constructor of Sierpinski fractal.
     * @param other The Sierpinski object to copy.
     */
    Sierpinski(const Sierpinski& other) : Fractal(other) {}

    /**
     * Move constructor of Sierpinski fractal.
     * @param other The Sierpinski object to copy.
     */
    Sierpinski(Sierpinski && other) noexcept = default;

    /**
     * @param x The first argument in the point.
     * @param y The second argument on the point.
     * @return True if that point need to be painted in the fractal pattern, false otherwise.
     */
    bool inPattern(int x, int y) const override;
};

/**
 * Cantor dust fractal class.
 */
class CantorDust: public Fractal
{
public:
    /**
     * One arguments constructor (the shape size of the Cantor dust fractal will always be 3).
     * @param degree The degree of the fractal, needs to be between 1 to 6.
     */
    explicit CantorDust(const int& degree) : Fractal(degree, CANTOR_SIZE) {}

    /**
     * Copy constructor of CantorDust fractal.
     * @param other The CantorDust object to copy.
     */
    CantorDust(const CantorDust& other) : Fractal(other) {}

    /**
     * Move constructor of CantorDust fractal.
     * @param other The CantorDust object to copy.
     */
    CantorDust(CantorDust && other) noexcept = default;

    /**
     * @param x The first argument in the point.
     * @param y The second argument on the point.
     * @return True if that point need to be painted in the fractal pattern, false otherwise.
     */
    bool inPattern(int x, int y) const override;
};

#endif //EX2_FRACTAL_H
