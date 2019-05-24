#include "noeud.hpp"

noeud::noeud(Point _p)
{
    //int index;
     p=_p;
     left=nullptr;
     right=nullptr;
}

noeud::noeud(int _axe, double _med, Point _p, noeud* _left, noeud* _right) {
    //int index;
    axe=_axe;
    med=_med;
    p=_p;
    left=_left;
    right=_right;

}

bool noeud::isleaf(){
    if(left==nullptr && right==nullptr){
        return true;
    }
    return false;
}

