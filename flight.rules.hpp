#ifndef RULES_HPP
#define RULES_HPP
#include "UState.hpp"
#include "neighbours.check.hpp"

//Separazione
class Sep {
double S;
double const ds = 3;

public:
Sep(double s, double d_s) : S{s}, ds{d_s} {};

double operator()(UState const& u1, UState const& u2) {
     if( std::abs(u1.P.x-u2.P.x) < ds){
       return -S * (u2.P.x - u1.P.x);
      } 
};
};

//Allineamento
class All {

};
//Coesione
class Coe {

};

#endif