// Implementation of class representing a sensor with beacon reading.

#include <cmath>
#include "sensor.h"

Sensor::Sensor(int xs_, int ys_, int xb_, int yb_) {
    xs = xs_;
    ys = ys_;
    xb = xb_;
    yb = yb_;
    dxy = abs(xb - xs) + abs(yb - ys);
}
