#include "proteine.hpp"

proteine::proteine()
{

}
proteine::proteine(string s, int p){
    name= s;
    score=p;
}
proteine::~proteine(){

}

int proteine::getscore(){
    return score;
}
void proteine::addscore(){
    score=score+1;
}
