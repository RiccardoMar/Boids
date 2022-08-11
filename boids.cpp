#include "boids.hpp"

#include <cassert>
#include <iostream>
#include <stdexcept>

// inserire le varie funzioni implementate insieme agli output

// valori in input
int main() {
  int n;  // qui c'era anche un char a, e nell'assert n!=a, però non penso serva
  assert(n >= 2);
  std::cin >> n;
  std::vector<UState> uccelli(n);


  //Creazione n uccelli a random e inserimento con for loop dentro std::vector uccelli
// 
// 
// 
// 
// 
// 
  //Input parametri funzionamento

  double s;
  std::cin >> s;
  Sep separazione{s};

  double a;
  std::cin >> a;
  All allineamento{a};

  double c;
  std::cin >> c;
  Coe coesione{c};



  // Start interazione boids

  Boids boids{uccelli, separazione, allineamento, coesione};

  // valori in output
  std::cout
      << "Distanza media tra i boids : ";  // inseriremo vettore di
                                           // UStates con le nuove velocità
}