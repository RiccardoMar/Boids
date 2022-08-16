#include "boids.hpp"

// inserire le varie funzioni implementate insieme agli output

// valori in input
int main() {
  auto const display_width = sf::VideoMode::getDesktopMode().width;
  auto const display_height = sf::VideoMode::getDesktopMode().height;

  int n;  // qui c'era anche un char a, e nell'assert n!=a, però non penso
          // serva
  assert(n >= 2);
  std::cin >> n;
  std::vector<UState> uccelli(n);

  // Creazione n uccelli a random e inserimento con for loop dentro std::vector
  // uccelli

  std::default_random_engine gen;
  for (int i = 0; i != n; ++i) /*si potrebbe anche fare con range loop*/ {
    std::uniform_int_distribution<double> random_position(0., 1.);
    std::uniform_int_distribution<double> random_velocity(
        /*estremi della randomness*/);

    uccelli[i].P.x =
        random_position(gen);  // l'errore va via dopo aver messo gli estremi
    uccelli[i].P.y =
        random_position(gen);  // l'errore va via dopo aver messo gli estremi
    uccelli[i].V.vx =
        random_velocity(gen);  // l'errore va via dopo aver messo gli estremi
    uccelli[i].V.vy =
        random_velocity(gen);  // l'errore va via dopo aver messo gli estremi
    uccelli[i].UPN = i;
  };

  // Input parametri funzionamento

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

  Boids boids{uccelli, separazione, allineamento,
              coesione};  // bisogna fargli il costruttore

  // valori in output
  std::cout
      << "Distanza media tra i boids : ";  // inseriremo vettore di
                                           // UStates con le nuove velocità
}