#ifndef USTATE_HPP
#define USTATE_HPP

#include <iosfwd> //riguarda l'operatore << 

struct UState { // stato dei singoli uccelli. Posizione e velocità in x,y
  double x{};
  double y{};
  double vx{};
  double vy{};
  bool operator==(UState const other) const; //per i test
};

std::ostream& operator<<(std::ostream& os, UState const& u);

#endif
