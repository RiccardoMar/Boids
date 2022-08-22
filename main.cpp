#include "boids.hpp"

// inserire le varie funzioni implementate insieme agli output

// valori in input
int main() {
  auto const display_width = sf::VideoMode::getDesktopMode().width;
  auto const display_height = sf::VideoMode::getDesktopMode().height;

  int n;
  std::cin >> n;
  if (n <= 2) {
    throw std::runtime_error{"Has to be a positive integer > 2"};
  };

  int distance;
  std::cin >> distance;
  if (distance > display_width) {
    throw std::runtime_error{"Has to be < width"};
  };

  std::vector<UState> uccelli(n);

  // Creazione n uccelli a random e inserimento con for loop dentro std::vector
  // uccelli

  std::default_random_engine gen;
  for (auto& u : uccelli) {
    std::uniform_real_distribution<double> random_height(0., display_height);
    std::uniform_real_distribution<double> random_width(0., display_width);
    std::uniform_real_distribution<double> random_velocity(0., 50.);

    u.P.x = random_width(gen);
    u.P.y = random_height(gen);
    u.V.vx = random_velocity(gen);
    u.V.vy = random_velocity(gen);

    for (int i = 0; i != uccelli.size(); ++i) {
      u.UPN = i;
    };
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

  Boids boids{uccelli, separazione, allineamento, coesione,
              distance};  // bisogna fargli il costruttore

  // valori in output
  std::cout
      << "Distanza media tra i boids : ";  // inseriremo vettore di
                                           // UStates con le nuove velocità
}
