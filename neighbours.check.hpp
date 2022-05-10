#ifndef NEIGHBOURS_CHECK_HPP
#define NEIGHBOURS_CHECK_HPP


#include <cmath>

#include "UState.hpp"


class Check {
double d_;
public:
Check(double const d) : d_(d){}

bool operator()(Ustate const& u1, UState const& u2) const {
    return abs((u1.x^2 + u1.y^2)^0.5 - (u2.x^2 + u2.y^2)^0.5) < d;
}
}




//qual è la distanza limite per la definizione di un vicino? 
//siccome il check prende due punti e vede se sono vicini, non ha var private -> lo implemento come struct?
#endif