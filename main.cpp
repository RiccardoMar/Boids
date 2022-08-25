#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "boids.hpp"

auto evolve(Boids& boids, int steps_per_evolution, sf::Time delta_t) {
  double const dt{delta_t.asSeconds()};

  for (int i{0}; i != steps_per_evolution; ++i) {
    boids.evolve(dt);
  }

  return boids.state();
}

// valori in input
int main() {
  auto const delta_t{sf::milliseconds(1)};
  int const fps = 30;
  int const steps_per_evolution{1000 / fps};

  auto const display_width = sf::VideoMode::getDesktopMode().width;
  auto const display_height = sf::VideoMode::getDesktopMode().height;
  int n;
  std::cout << "Metti n: " << '\n';
  std::cin >> n;
  if (n <= 2) {
    throw std::runtime_error{"Has to be a positive integer > 2"};
  };

  std::cout << display_height << display_width << '\n';

  std::vector<UState> uccelli;
  uccelli.reserve(n);

  // Creazione n uccelli a random e inserimento con for loop dentro std::vector
  // uccelli

  std::default_random_engine gen;
  for (unsigned int i = 0; i != uccelli.size(); ++i) {
    std::uniform_real_distribution<double> random_height(0., display_height);
    std::uniform_real_distribution<double> random_width(0., display_width);
    std::uniform_real_distribution<double> random_velocity(0., 50.);

    uccelli[i].P.x = random_width(gen);
    uccelli[i].P.y = random_height(gen);
    uccelli[i].V.vx = random_velocity(gen);
    uccelli[i].V.vy = random_velocity(gen);

    uccelli[i].UPN = i;
  };

  // Input parametri funzionamento

  double s;
  std::cout << "Metti s: " << '\n';
  std::cin >> s;
  if (s > 1 || s < 0) {
    throw std::runtime_error{"Has to be between 0 and 1"};
  };
  Sep separazione{s};

  double a;
  std::cout << "Metti a: " << '\n';
  std::cin >> a;
  if (a > 1 || a < 0) {
    throw std::runtime_error{"Has to be between 0 and 1"};
  };
  All allineamento{a};

  double c;
  std::cout << "Metti c: " << '\n';
  std::cin >> c;
  if (c > 1 || c < 0) {
    throw std::runtime_error{"Has to be between 0 and 1"};
  };
  Coe coesione{c};

  unsigned int distance;
  std::cout << "Metti distanza: " << '\n';
  std::cin >> distance;
  if (distance > display_width) {
    throw std::runtime_error{"Has to be < width"};
  };

  // Start interazione boids

  

  std::cout << "Fine input" << '\n';
  // Start interazione boids
Boids boids(uccelli, separazione, allineamento, coesione, distance);

auto Vicini = Check(uccelli, distance);
auto vs = separazione(Vicini);
std::cout << vs[1].vx << ',' << vs[1].vx << '\n';

  std::cout
      << "Distanza media tra i boids : ";  // inseriremo vettore di
                                           // UStates con le nuove velocità

  for (auto const& u : boids.state()) {
    std::cout << u << '\n';
  }

  std::cout << "/////////////////////////////////////////////////////////////"
            << '\n';

  auto Vicini = Check(uccelli, distance);
  std::cout << Vicini[0].u1 << Vicini[0].u2;
}

