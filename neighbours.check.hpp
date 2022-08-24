#ifndef NEIGHBOURS_CHECK_HPP
#define NEIGHBOURS_CHECK_HPP

#include <cmath>
#include <vector>

#include "UState.hpp"

struct Coppia {
  UState u1;
  UState u2;
};

std::vector<Coppia> Check(std::vector<UState>& uccelli,
                          double const distanza) {
  std::vector<Coppia> Vicini;
  for (unsigned int i = 0; i != uccelli.size() - 1; ++i) {
    for (unsigned int j = i; j != uccelli.size(); ++j) {
      if (dist(uccelli[i], uccelli[j]) < distanza * distanza) {
        Vicini.push_back(Coppia{uccelli[i], uccelli[j]});
      }
    }
  }
  return Vicini;
}

#endif