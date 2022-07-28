#ifndef USTATE_HPP
#define USTATE_HPP

#include <iosfwd> //riguarda l'operatore << 

struct Position {
  double x{};
  double y{};
  Position operator+=(Position const& other);
  Position operator-(Position const& P1, Position const& P2);
  Position operator/(Position const& P, double const& den);
  Position move(Velocity const& V, double const& dt);
};

struct Velocity {
  double vx{};
  double vy{};
  Velocity operator+=(Velocity const& other);
  Velocity operator-(Velocity const& V1, Velocity const& V2);
  Velocity operator/(Velocity const& V, double const& den);
};

struct UState { // stato dei singoli uccelli. Posizione e velocità in x,y
  Position P{};
  Velocity V{};
  bool operator==(UState const& other) const; //per i test
  double dist(UState const& other) const;
};

double dist(UState const& u1, UState const& u2);

std::ostream& operator<<(std::ostream& os, UState const& u);

#endif
