#ifndef NOEUD_H
#define NOEUD_H
#include "point.hpp"
#include <iostream>
#include <cmath>	// for sqrt, fabs


class noeud
{
public:
    int axe; //dimension (axe verticale, horizontale...)
    double med; //valeur de la mediane
    Point p;
    noeud *left;
    noeud *right;

    noeud (Point _p);
    noeud (int _axe, double _med, Point _p, noeud* _left, noeud* _right);

    bool isleaf();


};

#endif // NOEUD_H
