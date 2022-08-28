#include <SFML/Graphics.hpp>
#include <SFML/System/Time.hpp>

#include "boids.hpp"

auto evolve(Boids& boids, int steps_per_evolution, sf::Time delta_t,
            unsigned int display_width, unsigned int display_height) {
  double const dt{delta_t.asSeconds()};
  for (int i{0}; i != steps_per_evolution; ++i) {
    boids.evolve(dt, display_width, display_height);
    // boids.bordi(boids, display_width, display_height);
  }

  return boids.state();
}

auto meandistance(Boids& boids) {
  auto uccelli = boids.state();
  double sum_distance{0};
  int h{0};
  for (unsigned int i = 0; i != uccelli.size() - 1; ++i) {
    for (unsigned int j = i + 1; j != uccelli.size(); ++j) {
      auto dx = uccelli[i].P.x - uccelli[j].P.x;
      auto dy = uccelli[i].P.y - uccelli[j].P.y;
      sum_distance += std::sqrt((dx * dx) + (dy * dy));
      ++h;
    }
  }
  auto mean = sum_distance / h;
  return (mean);
}

auto STD(Boids& boids, double mean) {
  auto uccelli = boids.state();
  double d{0.};
  int h{0};
  for (unsigned int i = 0; i != uccelli.size() - 1; ++i) {
    for (unsigned int j = i + 1; j != uccelli.size(); ++j) {
      auto dx = uccelli[i].P.x - uccelli[j].P.x;
      auto dy = uccelli[i].P.y - uccelli[j].P.y;
      double xy = std::sqrt((dx * dx) + (dy * dy));

      d += std::pow((xy - mean), 2);
      ++h;
    }
  }

  auto STD = std::sqrt(d / (h));
  return (STD);
}

// valori in input
int main() {
  auto const delta_t{sf::milliseconds(1)};
  int const fps = 60;
  int const steps_per_evolution{1000 / fps};
  auto const display_width = sf::VideoMode::getDesktopMode().width;
  auto const display_height = sf::VideoMode::getDesktopMode().height;
  // auto const display_width = 2700;
  // auto const display_height = 1700;

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
    std::uniform_real_distribution<double> random_height(0.,
                                                         display_height - 200);
    std::uniform_real_distribution<double> random_width(0.,
                                                        display_width - 200);

    std::uniform_real_distribution<double> random_velocity(-50., 50.);

    uccelli[i].P.x = random_width(gen);
    uccelli[i].P.y = random_height(gen);
    uccelli[i].V.vx = random_velocity(gen);
    uccelli[i].V.vy = random_velocity(gen);

    uccelli[i].UPN = i;
  };

  // Input parametri funzionamento

  double s;
  std::cout << "Inserire il parametro di separazione : ";
  std::cin >> s;
  // if (s > 1 || s < 0) {
  //   throw std::runtime_error{"Has to be between 0 and 1"};
  // };
  Sep separazione{s};

  double a;
  std::cout << "Inserire il parametro di allineamento : ";
  std::cin >> a;
  // if (a > 1 || a < 0) {
  //   throw std::runtime_error{"Has to be between 0 and 1"};
  // };
  All allineamento{a};

  double c;
  std::cout << "Inserire il parametro di coesione : ";
  std::cin >> c;
  // if (c > 1 || c < 0) {
  //   throw std::runtime_error{"Has to be between 0 and 1"};
  // };
  Coe coesione{c};

  unsigned int distance;
  std::cout
      << "Inserire la distanza di interazione fra boids (in pixel; ricordare "
         "che il parametro distanza della separazione è 30 pixel) : ";
  std::cin >> distance;
  if (distance > display_width) {
    throw std::runtime_error{"Has to be < width"};
  };

  // Start interazione boids

  Boids boids{uccelli, separazione, allineamento, coesione,
              distance};  // bisogna fargli il costruttore

  // valori in output

  // std::cout <<
  // "/////////////////////////////////////////////////////////////"
  //           << '\n';

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "SFML works!");

  sf::RenderWindow window1(sf::VideoMode(600, 300), "Double window works!");

  sf::Vector2i v1(100, 200);

  sf::Texture texture;
  if (!texture.loadFromFile("freccia.png")) {
    std::cout << "Could not load texture" << std::endl;
    return 0;
  }
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(0.1f, 0.1f);

  sf::Texture texture1;
  if (!texture1.loadFromFile("sky.jpg")) {
    std::cout << "Could not load texture" << std::endl;
    return 0;
  }
  sf::Sprite sprite1;
  sprite1.setTexture(texture1);
  auto f1= (display_width)/728.;
  auto f2 = (display_height - 150.)/410.;
  sprite1.setScale(f1, f2);

  sf::Texture texture2;
  if (!texture2.loadFromFile("pause.png")) {
    std::cout << "Could not load texture" << std::endl;
    return 0;
  }
  sf::Sprite sprite2;
  sprite2.setTexture(texture2);

  sprite2.setScale(4.091f, 5.33f);

  sf::Font font;
  if (!font.loadFromFile("RachelBrown.ttf")) {
    std::cout << "Could not load font" << std::endl;
    return 0;
  }
  sf::Text text;
  text.setFont(font);
  text.setCharacterSize(30);
  text.setFillColor(sf::Color::Black);
  text.setPosition(0, 0);

  sf::Text text1;
  text1.setFont(font);
  text1.setCharacterSize(30);
  text1.setFillColor(sf::Color::Black);
  text1.setPosition(0, 100);

  bool wait = false;

  window.setFramerateLimit(fps);
  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    while (window1.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window1.close();
    }

    if ((event.type == sf::Event::KeyPressed) ||
        (event.key.code == sf::Keyboard::Enter)) {
      wait = true;
    }

    if ((event.type == sf::Event::KeyPressed) ||
        (event.key.code == sf::Keyboard::Escape)) {
      wait = false;
    }

    if (window1.isOpen() == false &&
        sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
      window1.create(sf::VideoMode(700, 600), "Double window works!");
    }

    if (wait == true) {  // codice quando il gioco è in pausa
      window.clear();
      window.draw(sprite2);
      // window.draw(sprite1);
      //   auto b = boids.state();

      //   for (unsigned int i = 0; i != uccelli.size(); ++i) {

      //     sprite.setPosition(b[i].P.x, b[i].P.y);
      //     window.draw(sprite);
      // //      for (auto const& u : boids.state()) {
      // //  std::cout << u << '\n';
      // //}
      //   }

      if (window1.isOpen() == false) {
        window.draw(text);
      }

      window.display();

      window1.clear(sf::Color::White);
      window1.draw(text);
      window1.draw(text1);
      window1.display();
    }

    if (wait == false) {
      window.clear(sf::Color::Black);
      window.draw(sprite1);

      auto const state = evolve(boids, steps_per_evolution, delta_t,
                                display_width, display_height);
      auto b = boids.state();
      auto mean = meandistance(boids);
      auto distanza_m = std::to_string(mean);
      auto s1 = "Distanza media : ";
      auto m = s1 + distanza_m;
      auto SD = STD(boids, mean);
      auto st_dev = std::to_string(SD);
      auto s2 = "Deviazione standard : ";
      auto sd = s2 + st_dev;
      text1.setString(sd);
      text.setString(m);
      // std::cout
      //     << "////////////////////////////////////////////////////////////"
      //     << '\n';
      for (unsigned int i = 0; i != uccelli.size(); ++i) {
        // auto arg = (180. / 3.1415926535) * std::atan(b[i].V.vy / b[i].V.vx);
        // sprite.setRotation(arg);
        sprite.setPosition(b[i].P.x, b[i].P.y);
        window.draw(sprite);
      }

      if (window1.isOpen() == false) {
        window.draw(text);
      }

      window.display();

      window1.clear(sf::Color::White);
      window1.draw(text);
      window1.draw(text1);
      window1.display();
    }
  }

  return 0;
}
