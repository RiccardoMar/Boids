#ifndef FLIGHT_RULES_HPP
#define FLIGHT_RULES_HPP
#include <stdexcept>

#include "neighbours.check.hpp"

// Separazione
class Sep {
  double s_;
  double ds_ = 30.;

 public:
  Sep(double s) : s_{s} {
    if (s <= 0.) {
      throw std::runtime_error{"Invalid separation parameter"};
    }
  };

  std::vector<Velocity> operator()(std::vector<Coppia> const& Vicini,
                                   std::vector<UState> uccelli) {
    std::vector<Velocity> Velocities1(uccelli.size());

    for (unsigned int i = 0; i != Vicini.size(); ++i) {
      if (dist(Vicini[i].u1, Vicini[i].u2) < ds_) {
        Velocities1[Vicini[i].u1.UPN] += convertPtoV(
            uccelli[Vicini[i].u2.UPN].P - uccelli[Vicini[i].u1.UPN].P);
        Velocities1[Vicini[i].u2.UPN] += convertPtoV(
            uccelli[Vicini[i].u1.UPN].P - uccelli[Vicini[i].u2.UPN].P);
      }
    }
    for (unsigned int i = 0; i != Velocities1.size(); ++i) {
      Velocities1[i] = Velocities1[i] / (-1 / s_);
    }

    return Velocities1;
  }
};

// Allineamento
class All {
  double A;

 public:
  All(double a) : A{a} {
    if (a >= 1 || a < 0) {
      throw std::runtime_error{"Has to be between 0 and 1"};
    };
  };

  std::vector<Velocity> operator()(std::vector<Coppia> const& Vicini,
                                   std::vector<UState> uccelli) {
    std::vector<Velocity> Velocities2(uccelli.size());
    std::vector<short int> Counters(uccelli.size());

    for (unsigned int i = 0; i != Vicini.size(); ++i) {
      Velocities2[Vicini[i].u1.UPN] +=
          uccelli[Vicini[i].u2.UPN].V - uccelli[Vicini[i].u1.UPN].V;
      Velocities2[Vicini[i].u2.UPN] +=
          uccelli[Vicini[i].u1.UPN].V - uccelli[Vicini[i].u2.UPN].V;

      Counters[Vicini[i].u1.UPN]++;
      Counters[Vicini[i].u2.UPN]++;
    }
    for (unsigned int i = 0; i != Velocities2.size(); ++i) {
      if (Counters[i] != 0.) {
        Velocities2[i] = Velocities2[i] / Counters[i];
        Velocities2[i] = Velocities2[i] / (1 / A);
      };
    }
    return Velocities2;
  };
};

// Coesione
class Coe {
  double C;

 public:
  Coe(double c) : C{c} {
    if (c <= 0.) {
      throw std::runtime_error{"Invalid separation parameter"};
    }
  };

  std::vector<Velocity> operator()(std::vector<Coppia> const& Vicini,
                                   std::vector<UState> uccelli) const {
    std::vector<Velocity> Velocities3(uccelli.size());
    std::vector<short int> Counters(uccelli.size());
    for (unsigned int i = 0; i != Vicini.size(); ++i) {
      Velocities3[Vicini[i].u1.UPN] += convertPtoV(uccelli[Vicini[i].u2.UPN].P); //0 = 0 + 10
      Velocities3[Vicini[i].u2.UPN] += convertPtoV(uccelli[Vicini[i].u1.UPN].P); //0 = 0 + 0
      Counters[Vicini[i].u1.UPN]++; //
      Counters[Vicini[i].u2.UPN]++;
    }
    for (unsigned int i = 0; i != Velocities3.size(); ++i) {
      if (Counters[i] != 0.) {
        Velocities3[i] =
            Velocities3[i] / Counters[i];  // trasforma la sommatoria in media
        Velocities3[i] = (Velocities3[i] - convertPtoV(uccelli[i].P)) / (1 / C);
      }
    }
    return Velocities3;
  };
};

#endif