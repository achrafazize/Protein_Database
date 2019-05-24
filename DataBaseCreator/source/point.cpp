#include "point.hpp"
#include <cmath>	// for sqrt, fabs

int Point::d;

Point::Point(){
}

Point::Point(double* c, std::string l)
{
    this->coords=c;
    this->label=l;
}
Point::~Point(){

}


double Point::dist(Point &q)
{
    double sqd = 0.0;
    for (int m = 0; m < d; m++)
        sqd += (coords[m]-q.coords[m]) * (coords[m]-q.coords[m]);
    return sqrt(sqd);
}


bool Point::set_dim (int _d) {
    if (d > 0)
        return false;
    d = _d;
    return true;
}


int Point::get_dim () {
    return d;
}


double Point::getcoord(int i){
    return coords[i];
}



void Point::print() {
    std::cout<<"Label :"<<label<<std::endl;
    std::cout<<"Coord :"<<std::endl;
    std::cout << this->coords[0];
    for ( int j = 1; j < 13; j++){
        std::cout << " " << this->coords[j];}
    std::cout << std::endl;
}







