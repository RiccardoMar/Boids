#ifndef USTATE_HPP
#define USTATE_HPP

#include <iosfwd> //riguarda l'operatore << 

struct Position {
  double x{};
  double y{};
}

struct Velocity {
  double vx{};
  double vy{};
}

struct UState { // stato dei singoli uccelli. Posizione e velocità in x,y
  Position P{};
  Velocity V{};
  bool operator==(UState const other) const; //per i test
};

std::ostream& operator<<(std::ostream& os, UState const& u);

#endif
