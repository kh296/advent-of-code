// Implementation of class representing point.

#include "point.h"

// Create Point instance with (x, y) coordinate and height defined.
// Getter and setter methods, including for setting previous, in header file.
Point::Point(int x_, int y_, int height_) {
    x = x_;
    y = y_;
    height = height_;
    previous = nullptr;
}
