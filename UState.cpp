#include "UState.hpp"

#include <iostream>

bool UState::operator==(UState const other) const {}

std::ostream& operator<<(std::ostream& os, UState const& u) {
  os << "Posizione: (" <<u.x << ", " <<u.y <<") \n Velocità: (" << u.vx << ", " <<u.vy <<')';
  return os;
}