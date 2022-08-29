#ifndef USTATE_HPP
#define USTATE_HPP

#include <iosfwd>

struct Velocity {
  double vx{};
  double vy{};
  Velocity& operator+=(Velocity const& V2);
  Velocity operator-(Velocity const& V2);
  Velocity operator/(double const& den);
};

struct Position {
  double x{};
  double y{};
  Position& operator+=(Position const& P2);
  Position operator-(Position const& P2);
  Position operator/(double const& den);
  Position move(Velocity const& V, double const& dt);
};

Velocity convertPtoV(
    Position P);  // serve per alcuni passaggi algebrici nelle flight rules
Position convertVtoP(Velocity V);

struct UState {  // stato dei singoli uccelli. Numero progressivo, posizione e
                 // velocità in x,y
  int UPN{};
  Position P{};
  Velocity V{};
  bool operator==(UState const& other) const;  // per i test
  double dist(UState const& other) const;
};

double dist(UState const& u1, UState const& u2);

std::ostream& operator<<(std::ostream& os, UState const& u);

#endif