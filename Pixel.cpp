/**
 * @file Pixel.cpp
 * @author Itai Tagar
 *
 * @brief A file for the Pixel Class implementation.
 */


/*-----=  Includes  =-----*/


#include "Pixel.h"


/*-----=  Definitions  =-----*/


/**
 * @def CORD_COUNT 2
 * @brief A Macro that sets the number of coordinates for a pixel.
 */
#define CORD_COUNT 2

/**
 * @def DEFAULT_CONNECTIVITY_MASK {1, -1}
 * @brief A Macro that sets the connectivity mask for the default pixel connectivity.
 */
#define DEFAULT_CONNECTIVITY_MASK {1, -1}


/*-----=  Class Implementation  =-----*/

/**
 * @brief A Default Constructor for the Pixel which sets a pixel at (0,0).
 */
Pixel::Pixel()  : _x(0), _y(0)
{

}

/**
 * @brief A Constructor for the Pixel, which receive 2 coordinates
 *        and create a new Pixel object with the given coordinates.
 * @param x The X coordinate in the plane.
 * @param y The Y coordinate in the plane.
 */
Pixel::Pixel(const int x, const int y) : _x(x), _y(y)
{

}

/**
 * @brief operator << for stream insertion.
 * @param os The output stream.
 * @param pixel The Pixel to stream.
 * @return The output stream with the pixel streamed.
 */
std::ostream& operator<<(std::ostream &os, const Pixel &pixel)
{
    os << "(" << pixel.getX() << ", " << pixel.getY() << ")";
    return os;
}

/**
 * @brief Set the neighbours of the Pixel according to the given connectivity value.
 *        The function ignore neighbours that are outside of the image boundaries.
 * @param connectivity The pixel connectivity value.
 * @param maxX The max value in the X coordinates.
 * @param maxY The max value in the Y coordinates.
 */
void Pixel::setNeighbours(const int connectivity, const int maxX, const int maxY)
{
    int connectivityMask[CORD_COUNT] = DEFAULT_CONNECTIVITY_MASK;

    // Set the 4-connectivity neighbours.
    for (int mask : connectivityMask)
    {
        if (_x + mask >= 0 && _x + mask < maxX)
        {
            // If this neighbour is in the image.
            _neighbours.emplace_back(_x + mask, _y);
        }

        if (_y + mask >= 0 && _y + mask < maxY)
        {
            // If this neighbour is in the image.
            _neighbours.emplace_back(_x, _y + mask);
        }
    }

    if (connectivity == 8)
    {
        // Add the 8-connectivity neighbours.
        for (int mask : connectivityMask)
        {
            if (_x + mask >= 0 && _x + mask < maxX)
            {
                if (_y + mask >= 0 && _y + mask < maxY)
                {
                    // If this neighbour is in the image.
                    _neighbours.emplace_back(_x + mask, _y + mask);
                }

                if (_y - mask >= 0 && _y - mask < maxY)
                {
                    // If this neighbour is in the image.
                    _neighbours.emplace_back(_x + mask, _y - mask);
                }
            }
        }
    }

}