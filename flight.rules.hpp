#ifndef RULES_HPP
#define RULES_HPP
#include "UState.hpp"
#include "neighbours.check.hpp"

//Separazione
class Sep {
double s;
Check coppie;

public:
void v_1(){
     double d_s = coppie.d * s;
     UState u1; 
     UState u2;
     
     if(coppie(u1, u2) < d_s){
        for(int i; i != coppie.size(); ++i){
         double v1 = -s * (u1.x - u2.x);//inserire le coppie di uccelli, in base alle indicazioni del neighbours.check
        }
     } 
}


};
//Allineamento
class All {

};
//Coesione
class Coe {

};

#endif