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
  int const fps = 200;
  int const steps_per_evolution{1000 / fps};
  auto const display_width = sf::VideoMode::getDesktopMode().width;
  auto const display_height = sf::VideoMode::getDesktopMode().height;

  std::cout << "Display width = " << display_width << " ; "
            << "Display height : " << display_height << '\n';

  int n;
  std::cout << "Inserire il numero desiderato di boids : ";
  std::cin >> n;
  if (n <= 2) {
    throw std::runtime_error{"Has to be a positive integer > 2"};
  };

  std::vector<UState> uccelli(n);

  // Creazione n uccelli a random e inserimento con for loop dentro std::vector
  // uccelli
  std::random_device r;
  std::default_random_engine gen{r()};

  for (unsigned int i = 0; i != uccelli.size(); ++i) {
    // std::uniform_real_distribution<double> random_height(0.,
    //                                                      display_height -
    //                                                      200);
    // std::uniform_real_distribution<double> random_width(0.,
    //                                                     display_width - 200);

    std::uniform_real_distribution<double> random_velocity(25., 50.);

    uccelli[i].P.x = display_width / 2;
    uccelli[i].P.y = display_height / 2;
    uccelli[i].V.vx = random_velocity(gen);
    uccelli[i].V.vy = random_velocity(gen);

    uccelli[i].UPN = i;
  };

  // Input parametri funzionamento

  double s;
  std::cout << "Inserire il parametro di separazione : ";
  std::cin >> s;

  Sep separazione{s};

  double a;
  std::cout << "Inserire il parametro di allineamento : ";
  std::cin >> a;
  All allineamento{a};

  double c;
  std::cout << "Inserire il parametro di coesione : ";
  std::cin >> c;

  Coe coesione{c};

  unsigned int distance;
  std::cout
      << "Inserire la distanza di interazione fra boids (in pixel; ricordare "
         "che il parametro distanza della separazione è 10 pixel) : ";
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

  for (auto const& u : boids.state()) {
    std::cout << u << '\n';
  }

  std::cout << "/////////////////////////////////////////////////////////////"
            << '\n';

  auto vicini = Check(boids.state(), distance);
  auto va = allineamento(vicini, boids.state());
  for (auto& i : va) {
    std::cout << i.vx << "  ;  " << i.vy << '\n';
  }
}
