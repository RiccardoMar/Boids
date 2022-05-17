#ifndef NEIGHBOURS_CHECK_HPP
#define NEIGHBOURS_CHECK_HPP

#include <cmath>
#include <vector>

#include "UState.hpp"

struct Coppia {
  UState u1;
  UState u2;
};
/*class Check {
 private:
  double d_;
  std::vector<UState> uccelli_;
  bool operator()(UState const& u1, UState const& u2) const {
    double base1 = (u1.x * u1.x) + (u1.y * u1.y);
    double base2 = (u2.x * u2.x) + (u2.y * u2.y);
    return std::abs(std::pow(base1, 0.5) - std::pow(base2, 0.5)) < d_;
  }
  // d è la distanza minima da prendere fra 2 uccelli per considerarli vicini

 public:
  Check(double const d) : d_(d) {}
  Check(std::vector<UState> uccelli) : uccelli_(uccelli) {}
  std::vector<UState> Check_All(std::vector<UState>) {
    for (i=0; i != ; ++i){
      if (Check(uccelli_[i], uccelli_[i+1]) == true){

      }
    }
  }

};*/

// std::vector<Coppia> Vicini;

std::vector<Coppia> Check(std::vector<UState> const& uccelli,
                          double const distanza) {
  std::vector<Coppia> Vicini;
  for (int i = 0; i != uccelli.size()-1; ++i) {
    for (int j = i; j != uccelli.size(); ++j) {
      double a;
      double base1 =
          (uccelli[j].x * uccelli[j].x) + (uccelli[j].y * uccelli[j].y);
      double base2 = (uccelli[j + 1].x * uccelli[j + 1].x) +
                     (uccelli[j + 1].y * uccelli[j + 1].y);
      a = std::abs(std::pow(base1, 0.5) - std::pow(base2, 0.5));
      if (a < distanza){

      }
    }
  }
}


#endif