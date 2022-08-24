#include "boids.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

auto evolve(Boids& boids, int steps_per_evolution, sf::Time delta_t)
{
  double const dt{delta_t.asSeconds()};

  for (int i{0}; i != steps_per_evolution; ++i) {
    boids.evolve(dt);
  }

  return boids.state();
}

// valori in input
int main() {
  auto const display_width = sf::VideoMode::getDesktopMode().width;
  auto const display_height = sf::VideoMode::getDesktopMode().height;

  int n;
  std::cin >> n;
  if (n <= 2) {
    throw std::runtime_error{"Has to be a positive integer > 2"};
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
  if (s > 1 || s < 0) {
    throw std::runtime_error{"Has to be between 0 and 1"};
  };
  Sep separazione{s};

  double a;
  std::cin >> a;
  if (a > 1 || a < 0) {
    throw std::runtime_error{"Has to be between 0 and 1"};
  };
  All allineamento{a};

  double c;
  std::cin >> c;
  if (c > 1 || c < 0) {
    throw std::runtime_error{"Has to be between 0 and 1"};
  };
  Coe coesione{c};

  unsigned int distance;
  std::cin >> distance;
  if (distance > display_width) {
    throw std::runtime_error{"Has to be < width"};
  };

  // Start interazione boids

  Boids boids{uccelli, separazione, allineamento, coesione,
              distance};  // bisogna fargli il costruttore

  // valori in output
  std::cout
      << "Distanza media tra i boids : ";  // inseriremo vettore di
                                           // UStates con le nuove velocità
}
