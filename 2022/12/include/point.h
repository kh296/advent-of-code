#ifndef POINT_H
#define POINT_H

class Point {
    private:
    int x;
    int y;
    int height;
    Point* previous;
    public:
    Point(int, int, int);
    int getX() {return x;}
    int getY() {return y;}
    char getH() {return height;}
    void setH(int height_) {height = height_;}
    void setPrevious(Point* previous_) {previous = previous_;}
    Point* getPrevious() {return previous;}
};

#endif
