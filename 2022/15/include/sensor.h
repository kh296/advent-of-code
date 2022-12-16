#ifndef SENSOR_H
#define SENSOR_H

class Sensor {
    private:
    int xs;
    int ys;
    int xb;
    int yb;
    int dxy;
    public:
    Sensor(int, int, int, int);
    int getXs() {return xs;}
    int getYs() {return ys;}
    int getXb() {return xb;}
    int getYb() {return yb;}
    int getDxy() {return dxy;}
};

#endif
