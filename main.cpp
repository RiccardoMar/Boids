#include "boids.hpp"

auto evolve(Boids& boids, int steps_per_evolution, sf::Time delta_t,
            unsigned int display_width, unsigned int display_height) {
  double const dt{delta_t.asSeconds()};
  for (int i{0}; i != steps_per_evolution; ++i) {
    boids.evolve(dt, display_width, display_height);
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
  std::cout << "///////////////////////////////////////////// Simulazione di Stormi ///////////////////////////////////////////" << '\n';
  auto const delta_t{sf::milliseconds(1)};
  int const fps = 60;
  int const steps_per_evolution{1000 / fps};
  auto const display_width = sf::VideoMode::getDesktopMode().width;
  auto const display_height = sf::VideoMode::getDesktopMode().height;

  std::cout << "Display width = " << display_width << " ; "
            << "Display height : " << display_height << '\n';

  int n;
  std::cout << "Inserire il numero desiderato di boids : ";
  std::cin >> n;
  if (n < 2) {
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
         "che il parametro distanza della separazione è 30 pixel) : ";
  std::cin >> distance;
  if (distance > display_width) {
    throw std::runtime_error{"Has to be < width"};
  };

  // Start interazione boids

  Boids boids{uccelli, separazione, allineamento, coesione, distance};

  std::cout << "/////////////////////////////////////////////////////////////"
            << '\n';

  // comparto grafico

  sf::RenderWindow window(sf::VideoMode(display_width, display_height),
                          "SFML works!");

  sf::RenderWindow window1(sf::VideoMode(500, 300), "Double window works!");

  sf::Vector2i v1(display_width - 500, display_height - 450);
  window1.setPosition(v1);

  sf::Texture texture;
  if (!texture.loadFromFile("Alien.png")) {
    std::cout << "Could not load texture" << std::endl;
    return 0;
  }
  sf::Sprite sprite;
  sprite.setTexture(texture);
  sprite.setScale(0.07f, 0.07f);

  sf::Texture texture1;
  if (!texture1.loadFromFile("space.jpg")) {
    std::cout << "Could not load texture" << std::endl;
    return 0;
  }
  sf::Sprite sprite1;
  sprite1.setTexture(texture1);
  // auto f1 = (display_width) / 728.;
  // auto f2 = (display_height - 150.) / 410.;
  sprite1.setScale(1.3f, 1.5f);

  sf::Texture texture2;
  if (!texture2.loadFromFile("pause.png")) {
    std::cout << "Could not load texture" << std::endl;
    return 0;
  }
  sf::Sprite sprite2;
  sprite2.setTexture(texture2);
  sprite2.setScale(1.f, 1.f);
  auto p1 = (display_width - 660) / 2;
  auto p2 = (display_height - 320) / 2;
  sprite2.setPosition(p1, p2);

  sf::Texture texture3;
  if (!texture3.loadFromFile("unnamed.png")) {
    std::cout << "Could not load texture" << std::endl;
    return 0;
  }
  sf::Sprite sprite3;
  sprite3.setTexture(texture3);

  sf::Texture texture4;
  if (!texture4.loadFromFile("Nave.png")) {
    std::cout << "Could not load texture" << std::endl;
    return 0;
  }
  sf::Sprite sprite4;
  sprite4.setTexture(texture4);
  sprite4.setScale(.2f, .2f);

  // sf::Texture texture5;
  // if (!texture5.loadFromFile("exp.png")) {
  //   std::cout << "Could not load texture" << std::endl;
  //   return 0;
  // }
  // sf::Sprite sprite5;
  // sprite5.setTexture(texture5);
  // sprite5.setScale(.7f, .7f);

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
  text1.setPosition(0, 50);

  sf::Text text2;
  text2.setFont(font);
  text2.setCharacterSize(30);
  text2.setFillColor(sf::Color::Red);
  text2.setPosition(0, 100);
  text2.setString("Press Enter to pause the game");

  sf::Text text3;
  text3.setFont(font);
  text3.setCharacterSize(30);
  text3.setFillColor(sf::Color::Cyan);
  text3.setPosition(0, 100);
  text3.setString("Click here to reopen the small window");

  bool wait = false;
  float x_pos = 0.0f;
  float y_pos = 0.0f;
  float x_pos1 = display_width - 500;
  float y_pos1 = display_height - 1050;
  int i{0};
  float p0 = 0.f;
  float p = display_width - 80.f;

  window.setFramerateLimit(fps);
  while (window.isOpen()) {
    sf::Event event;

    while (window.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window.close();
    }

    while (window1.pollEvent(event)) {
      if (event.type == sf::Event::Closed) window1.close();
    }

    if (event.key.code == sf::Keyboard::Enter) {
      wait = true;
    }

    if (event.key.code == sf::Keyboard::Escape) {
      wait = false;
    }

    if (window1.isOpen() == false &&
        sf::Mouse::isButtonPressed(sf::Mouse::Right)) {
      window1.create(sf::VideoMode(500, 300), "Double window works!");
      window1.setPosition(v1);
    }

    if (wait == true) {  // codice quando il gioco è in pausa

      if (x_pos < x_pos1) {
        sprite3.setPosition(x_pos, y_pos);
        x_pos += 10.1f;
        y_pos += std::sin(30) * -3.3;
      };

      if (x_pos > x_pos1) {
        x_pos1 = sprite3.getPosition().x + 1;
        y_pos1 = sprite3.getPosition().y + 1;

        x_pos1 -= 10.1f;
        y_pos1 -= std::sin(30) * -3.3;
        sprite3.setPosition(x_pos1, y_pos1);
        if (i > 230) {
          sprite3.setColor(sf::Color::Red);
        }
        if (i > 692) {
          sprite3.setColor(sf::Color::Green);
        }
        if (i > 1006) {
          sprite3.setColor(sf::Color::Yellow);
        }
      };

      if (x_pos1 < 0) {
        x_pos = 0.f;
        x_pos1 = display_width - 500.f;
        y_pos = sprite3.getPosition().y - 1;
        y_pos1 = 0.f;
        if (i > 440) {
          sprite3.setColor(sf::Color::Blue);
        }
        if (i > 967) {
          sprite3.setColor(sf::Color::Magenta);
        }
      };
      if (y_pos1 > display_height - 500.f) {
        x_pos = 0.f;
        x_pos1 = display_width - 500.f;
        y_pos = 0.f;
        y_pos1 = sprite3.getPosition().y - 1;
        if (i > 440) {
          sprite3.setColor(sf::Color::Blue);
        }
        if (i > 967) {
          sprite3.setColor(sf::Color::Magenta);
        }
      };

      ++i;

      if (window1.isOpen() == false) {
        window.draw(text);
      }

      window.clear();
      window.draw(sprite2);
      window.draw(sprite3);
      window.display();
      window1.clear(sf::Color::White);
      window1.draw(text);
      window1.draw(text1);
      window1.display();
    }

    if (wait == false) {
      i = 0;
      sprite3.setColor(sf::Color::White);
      x_pos = 0.;
      y_pos = 0.;
      x_pos1 = display_width - 500;
      y_pos1 = display_height - 1050;
      sprite3.setPosition(x_pos, y_pos);

      if (p0 < p) {
        sprite4.setPosition(p0, display_height - 500);
        p0 += 6.f;
      }
      if (p0 > p) {
        sprite4.setPosition(p, display_height - 500);
        p -= 6.f;
      }
      if (p < 0.f) {
        p0 = 0.f;
        p = display_width - 80;
      }

      window.clear(sf::Color::Black);

      window.draw(sprite1);
      window.draw(sprite4);
      // if (p0 > ((display_width -500)/2) && p0 < ((display_width +200)/2)) {
      //   sprite5.setPosition((display_width/2), 500);
      //   window.draw(sprite5);
      // }
      // if (p > ((display_width -200)/2) && p < ((display_width +100)/2)) {
      //   sprite5.setPosition(1200 , 500);
      //   window.draw(sprite5);
      // }
      // if (p > display_width - 300.f && p < display_width - 80.f) {
      //   sprite5.setPosition(display_width - 250.f, 500);
      //   window.draw(sprite5);
      // }
      // if (p > 0 && p < 300) {
      //   sprite5.setPosition(200, 500);
      //   window.draw(sprite5);
      // }
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
      
      
      for (auto& u : state) {
        
        sprite.setPosition(u.P.x, u.P.y);
        window.draw(sprite);
      }
      
      
      if (window1.isOpen() == false) {
        window.draw(text3);
      }

      window.display();

      window1.clear(sf::Color::White);
      window1.draw(text);
      window1.draw(text1);
      window1.draw(text2);
      window1.display();
    }
  }

  return 0;
}
