#ifndef FLIGHT_RULES_HPP
#define FLIGHT_RULES_HPP
//#include "UState.hpp"
#include <stdexcept>

#include "neighbours.check.hpp"

// Separazione
class Sep {
  double s_;
  double ds_;

 public:
  Sep(double s, double ds) : s_{s}, ds_{ds} {
    if (s < 0. || s > 1.) {
      throw std::runtime_error{"Invalid separation parameter"};
    }
    if (ds <0.) {
      throw std::runtime_error{"Invalid distance separator parameter"};
      //qui in realtà vorrei anche poterlo confrontare con displaywidth :( come cabbo faccio)
    }
  };

  Sep(double s) : s_{s} {
    if (s < 0. || s > 1.) {
      throw std::runtime_error{"Invalid separation parameter"};
    }
  };

  std::vector<Velocity> operator()(std::vector<Coppia> const& Vicini) const {
    std::vector<Velocity> Velocities(uccelli.size());
    for (int i = 0; i != Vicini.size(); ++i) {
      if (dist(Vicini[i].u1, Vicini[i].u2) < ds) {
        Velocities[Vicini[i].u1.UPN] +=
            uccelli[Vicini[i].u2.UPN].P - uccelli[Vicini[i].u1.UPN].P;
        Velocities[Vicini[i].u2.UPN] +=
            uccelli[Vicini[i].u1.UPN].P - uccelli[Vicini[i].u2.UPN].P;
      }
    }
    for (int i = 0; i != Velocities.size(); ++i) {
      (Velocities[i] - uccelli[i].P) / (-1 / S);
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
      Velocities[Vicini.u1.UPN] +=
          uccelli[Vicini.u2.UPN].V - uccelli[Vicini.u1.UPN].V;
      Velocities[Vicini.u2.UPN] +=
          uccelli[Vicini.u1.UPN].V - uccelli[Vicini.u2.UPN].V;
      Counters[Vicini.u1.UPN]++;
      Counters[Vicini.u2.UPN]++;
    }
    for (int i = 0; i != Velocities.size(); ++i) {
      Velocities[i] / Counters[i];  // trasforma la sommatoria in media
      Velocities[i] /
          (1 / A);  // Nella struct Velocity ho implementato solo la divisione,
                    // quindi per moltiplicare divido per il reciproco.
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
      Velocities[i] / Counters[i];  // trasforma la sommatoria in media
      (Velocities[i] - uccelli[i].P) / (1 / C);
    }
    return Velocities;
  };
};

#endif

// bisogna stare molto attenti al calcolo delle medie: devono escludere il punto
// !