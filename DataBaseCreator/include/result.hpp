#ifndef RESULT_H
#define RESULT_H
#include <string>
#include "point.hpp"


class result
{
public:
    result(std::string name, Point p, double dist);
    result();
    ~result();
    std::string name;
    Point p;
    double dist;

};

#endif // RESULT_H
