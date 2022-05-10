#ifndef NEIGHBOURS_CHECK_HPP
#define NEIGHBOURS_CHECK_HPP


#include <cmath>

#include "UState.hpp"


class Check {
double d_;

// d è la distanza minima da prendere fra 2 uccelli per considerarli vicini 
    
public:
Check(double const d) : d_(d){}

bool operator()(UState const& u1, UState const& u2) const {
    double base1 = (u1.x*u1.x) + (u1.y*u1.y);
      double base2 = (u2.x*u2.x) + (u2.y*u2.y);
      return std::abs(std::pow(base1, 0.5) - std::pow(base2, 0.5)) < d_;
}
};


#endif
