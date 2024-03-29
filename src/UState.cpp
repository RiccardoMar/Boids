#include "../include/UState.hpp"

#include <cmath>
#include <iostream>

// Segue implementazione metodi Position
Position& Position::operator+=(Position const& P2) {
  x += P2.x;
  y += P2.y;
  return *this;
};

Position Position::operator-(Position const& P2) {
  return Position{x - P2.x, y - P2.y};
}
Position Position::operator/(double const& den) {
  return Position{x / den, y / den};
}
Position Position::move(Velocity const& V, double const& dt) {
  return Position{x + V.vx * dt, y + V.vy * dt};
}
// Segue implementazione metodi Velocity
Velocity& Velocity::operator+=(Velocity const& V2) {
  vx += V2.vx;
  vy += V2.vy;
  return *this;
};
Velocity Velocity::operator-(Velocity const& V2) {
  return Velocity{vx - V2.vx, vy - V2.vy};
}
Velocity Velocity::operator/(double const& den) {
  if (den == 0.) {
    throw std::runtime_error{"Denominator is zero: error"};
  }
  return Velocity{vx / den, vy / den};
}
// Segue implementazione metodi UState
double UState::dist(UState const& other) const {
  double d = std::sqrt((P.x - other.P.x) * (P.x - other.P.x) +
                       (P.y - other.P.y) * (P.y - other.P.y));
  return d;
}

// Segue implementazione funzioni libere
std::ostream& operator<<(std::ostream& os, UState const& u) {
  os << "Posizione: (" << u.P.x << ", " << u.P.y << ")  Velocità: (" << u.V.vx
     << ", " << u.V.vy << ") "
     << "Numero progressivo: " << u.UPN << '\n';
  return os;
}
Velocity convertPtoV(Position P) { return Velocity{P.x, P.y}; }
Position convertVtoP(Velocity V) { return Position{V.vx, V.vy}; }

double dist(UState const& u1, UState const& u2) { return u1.dist(u2); }