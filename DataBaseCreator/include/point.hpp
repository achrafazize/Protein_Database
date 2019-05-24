#ifndef POINT_H
#define POINT_H
#include <iostream>
#include <string>


//ATTENTION  : d non utilise pour print (13 a la place)
class Point
{
public:
    Point();
    Point(double* c, std::string l);
    ~Point();

    static int d;
    double* coords;
    std::string label;

    double dist( Point &q);
    static bool set_dim (int _d);
    static int get_dim();
    double getcoord(int i);
    void print();

};

#endif // POINT_H
