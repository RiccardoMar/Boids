#ifndef RULES_HPP
#define RULES_HPP
#include "UState.hpp"
#include "neighbours.check.hpp"

// Separazione
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

// Allineamento
class All {};
// Coesione
class Coe {
  double C;

 public:
  Position cdm(std::vector<UState> const& Vicini) {
    double x_cdm = 0.0;
    double y_cdm = 0.0;
    for (int i = 0; i != Vicini.size(); ++i) {
      x_cdm = x_cdm + Vicini[i].P.x;
    };
    x_cdm = x_cdm / (Vicini.size() - 1);
    for (int i = 0; i != Vicini.size(); ++i) {
      y_cdm = y_cdm + Vicini[i].P.y;
    };
    y_cdm = y_cdm / (Vicini.size() - 1);
    Position a{x_cdm, y_cdm};
    return a;
  }

  double operator()(UState const& u, std::vector<UState> const& Vicini) {}
};

#endif