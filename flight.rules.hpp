#ifndef RULES_HPP
#define RULES_HPP
#include "UState.hpp"
#include "neighbours.check.hpp"

// Separazione
class Sep {
double S = 0.;
double const ds = 3;

public:
Sep(double s) : S{s} {};
std::vector<Velocity> operator()(std::vector<Coppia> const& Vicini) const {
  for (int i = 0; i != Vicini.size(); ++i) {
    if(dist(Vicini[i].u1, Vicini[i].u2 < ds)){
      Velocities[Vicini.u1.UPN] += uccelli[Vicini.u2.UPN].P - uccelli[Vicini.u1.UPN].P;
      Velocities[Vicini.u2.UPN] += uccelli[Vicini.u1.UPN].P - uccelli[Vicini.u2.UPN].P;
    }
  }
  for (int i = 0; i != Velocities.size(); ++i) {
    (Velocities[i]-uccelli[i].P)/(-1/S);
    }
  return Velocities;
}
};

// Allineamento
class All {
 double A;

 public:
 All(double a) : A{a} {};
 std::vector<Velocity> operator()(std::vector<Coppia> const& Vicini) const {
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
  return Velocities;
  };
};

// Coesione
class Coe {
  double C;

 public:
  Coe(double c) : C{c} {};
  std::vector<Velocity> operator()(std::vector<Coppia> const& Vicini) const {
    std::vector<Position> Velocities(uccelli.size());
    std::vector<short int> Counters(uccelli.size());
  for (int i = 0; i != Vicini.size(); ++i) {
    Velocities[Vicini.u1.UPN] += uccelli[Vicini.u2.UPN].P;
    Velocities[Vicini.u2.UPN] += uccelli[Vicini.u1.UPN].P;
    Counters[Vicini.u1.UPN]++;
    Counters[Vicini.u2.UPN]++;
    }
  for (int i = 0; i != Velocities.size(); ++i) {
    Velocities[i]/Counters[i]; //trasforma la sommatoria in media
    (Velocities[i]-uccelli[i].P)/(1/C);
    }
  return Velocities;
  };
};

#endif