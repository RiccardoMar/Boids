#ifndef NEIGHBOURS_CHECK_HPP
#define NEIGHBOURS_CHECK_HPP


#include <cmath>

#include "UState.hpp"


class Check {
double d_;
public:
Check(double const d) : d_(d){}

bool operator()(Ustate const& u1, UState const& u2) const {
    double base1 = (u1.x*u1.x) + (u1.y*u1.y);
      double base2 = (u2.x*u2.x) + (u2.y*u2.y);
      return std::abs(std::pow(base1, 0.5) - std::pow(base2, 0.5)) < d_;
}
};




//qual è la distanza limite per la definizione di un vicino? 
//siccome il check prende due punti e vede se sono vicini, non ha var private -> lo implemento come struct?
#endif
