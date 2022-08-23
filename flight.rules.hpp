#ifndef FLIGHT_RULES_HPP
#define FLIGHT_RULES_HPP
#include <stdexcept>

#include "UState.hpp"
#include "neighbours.check.hpp"

// Separazione
class Sep {
  double s_;
  double ds_;

 public:
  std::vector<UState> uccelli;
  Sep(double s, double ds = 10.) : s_{s}, ds_{ds} {
    if (s <= 0. || s > 1.) {
      throw std::runtime_error{"Invalid separation parameter"};
    }
    if (ds <= 0.) {
      throw std::runtime_error{"Invalid distance separator parameter"};
    }
  };

  std::vector<Velocity> operator()(std::vector<Coppia> const& Vicini) {
    std::vector<Velocity> Velocities1(uccelli.size());

    for (unsigned int i = 0; i != Vicini.size(); ++i) {
      if (dist(Vicini[i].u1, Vicini[i].u2) < ds_) {
        Velocities1[Vicini[i].u1.UPN] +=
            convert(uccelli[Vicini[i].u2.UPN].P - uccelli[Vicini[i].u1.UPN].P);
        Velocities1[Vicini[i].u2.UPN] +=
            convert(uccelli[Vicini[i].u1.UPN].P - uccelli[Vicini[i].u2.UPN].P);
      }
    }  //-> così velocities è un vettore con le velocità v1, però che non sono
       //ancora state moltiplicate per il fattore s

    for (unsigned int i = 0; i != Velocities1.size(); ++i) {
      Velocities1[i] = Velocities1[i] / (-1 / s_);
    }
    // se v1 di un oggetto è = 0, allora non verrà toccata
    return Velocities1;
  }
}; //applicando auto v1 = sep(vettore vicini che viene da check), avremo in mano un vettore di velocità (x e y) 

// Allineamento
class All {
  double A;

 public:
  std::vector<UState> uccelli;
  All(double a) : A{a} {};
  std::vector<Velocity> operator()(std::vector<Coppia> const& Vicini) {
    std::vector<Velocity> Velocities(uccelli.size());
    std::vector<short int> Counters(uccelli.size());
    for (unsigned int i = 0; i != Vicini.size(); ++i) {
      Velocities[Vicini[i].u1.UPN] +=
          uccelli[Vicini[i].u2.UPN].V - uccelli[Vicini[i].u1.UPN].V;
      Velocities[Vicini[i].u2.UPN] +=
          uccelli[Vicini[i].u1.UPN].V - uccelli[Vicini[i].u2.UPN].V;
      Counters[Vicini[i].u1.UPN]++;
      Counters[Vicini[i].u2.UPN]++;
    }
    for (unsigned int i = 0; i != Velocities.size(); ++i) {
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
  std::vector<UState> uccelli;
  Coe(double c) : C{c} {};
  std::vector<Velocity> operator()(std::vector<Coppia> const& Vicini) const {
    std::vector<Velocity> Velocities(uccelli.size());
    std::vector<short int> Counters(uccelli.size());
    for (unsigned int i = 0; i != Vicini.size(); ++i) {
      Velocities[Vicini[i].u1.UPN] += convert(uccelli[Vicini[i].u2.UPN].P);
      Velocities[Vicini[i].u2.UPN] += convert(uccelli[Vicini[i].u1.UPN].P);
      Counters[Vicini[i].u1.UPN]++;
      Counters[Vicini[i].u2.UPN]++;
    }
    for (unsigned int i = 0; i != Velocities.size(); ++i) {
      Velocities[i] / Counters[i];  // trasforma la sommatoria in media
      (Velocities[i] - convert(uccelli[i].P)) / (1 / C);
    }
    return Velocities;
  };
};

#endif

// bisogna stare molto attenti al calcolo delle medie: devono escludere il punto
// !