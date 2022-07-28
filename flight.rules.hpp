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

double operator()(UState const& u1, UState const& u2) const {
     if( std::abs(u1.P.x-u2.P.x) < ds){
       return -S * (u2.P.x - u1.P.x);
      } else {
        return 0;
      }
};
};

// Allineamento
class All {
 double A;

 public:
 All(double a) : A{a} {};
 std::vector<Velocity> operator()(std::vector<Coppia> Vicini){
  std::vector<Velocity> Velocities(uccelli.size());
  std::vector<short int> Counters(uccelli.size());
  for (int i = 0; i != Vicini.size(); ++i) {
    Velocities[Vicini.u1.UPN] += uccelli[Vicini.u2.UPN].V - uccelli[Vicini.u1.UPN].V;
    Velocities[Vicini.u2.UPN] += uccelli[Vicini.u1.UPN].V - uccelli[Vicini.u2.UPN].V;
    Counters[Vicini.u1.UPN]++;
    Counters[Vicini.u2.UPN]++;
    }
  for (int i = 0; i != Velocities.size(); ++i) {
    Velocities[i]/Counters[i]; //trasforma la sommatoria in media
    Velocities[i]/(1/A); //Nella struct Velocity ho implementato solo la divisione, quindi per moltiplicare divido per il reciproco.
  }

  };
};
// Coesione
class Coe {
  double C;

 public:
  Coe(double c) : C{c} {};
  std::vector<Velocity> operator()(std::vector<Coppia> Vicini){
    std::vector<Velocity> Velocities(uccelli.size());
    std::vector<short int> Counters(uccelli.size());
  for (int i = 0; i != Vicini.size(); ++i) {
    
    }

  };
  
};

#endif