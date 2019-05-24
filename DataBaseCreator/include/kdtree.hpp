#ifndef KDTREE_H
#define KDTREE_H
#include <iostream>
#include "noeud.hpp"
#include "point.hpp"
#include "result.hpp"
#include <list>

class kdtree
{
public:



    noeud * racine;

    noeud * build (Point* P, int start, int end, int c, int dim);

    kdtree(Point* P, int start, int end, int c, int dim);

    kdtree();

    ~kdtree();


    double computeMedian(Point* P, int start, int end, int c) ;
    int partition(Point* P, int start, int end, int c, int dim);
    void swap(Point* P, int i, int j);
    std::list<result*>* search( Point q, double r);
    void printTree(noeud* racine);
    int generation(noeud* racine);

private:

};
#endif

