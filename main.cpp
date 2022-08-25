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
  std::random_device r;
  std::default_random_engine gen{r()};

  for (unsigned int i = 0; i != uccelli.size(); ++i) {
    std::uniform_real_distribution<double> random_height(0., display_height - 200);
    std::uniform_real_distribution<double> random_width(0., display_width - 200);
    std::uniform_real_distribution<double> random_velocity(0., 50.);

    uccelli[i].P.x = random_width(gen);
    uccelli[i].P.y = random_height(gen);
    uccelli[i].V.vx = random_velocity(gen);
    uccelli[i].V.vy = random_velocity(gen);

    uccelli[i].UPN = i;
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

  for (auto const& u : boids.state()) {
    std::cout << u << '\n';
  }

  std::cout << "/////////////////////////////////////////////////////////////"
            << '\n';

    sf::RenderWindow window(sf::VideoMode(display_width, display_height), "SFML works!");
    
sf::RenderWindow window1(sf::VideoMode(700, 600), "Double window works!");

sf::Vector2i v1(100, 200);

  sf::Texture texture;
if (!texture.loadFromFile("freccia.png")) {
  std::cout << "Could not load texture" << std::endl;
  return 0;
  
}
sf::Sprite sprite;
sprite.setTexture(texture);
sprite.setScale(0.25f, 0.25f);

sf::Texture texture1;
if (!texture1.loadFromFile("windowsxp.jpg")) {
  std::cout << "Could not load texture" << std::endl;
  return 0;
}
sf::Sprite sprite1;
sprite1.setTexture(texture1);
sprite1.setScale(2.5f, 2.5f);

sf::Font font;
if (!font.loadFromFile("RachelBrown.ttf"))
{
    std::cout << "Could not load font" << std::endl;
  return 0;
}
sf::Text text;
text.setFont(font); 
text.setString("Click here to drop down menu");
text.setCharacterSize(50); 
text.setFillColor(sf::Color::Black);
text.setPosition(1000, 100);

  window.setFramerateLimit(60);
  while (window.isOpen())
    {
        
        sf::Event event;
        
        while (window.pollEvent(event))
        {   
            if (event.type == sf::Event::Closed)
                window.close();
            }

        while (window1.pollEvent(event))
        {   
            if (event.type == sf::Event::Closed)
                window1.close();
                
                
            }
        
        if(window1.isOpen()==false && sf::Mouse::isButtonPressed(sf::Mouse::Right)){
                
                window1.create(sf::VideoMode(700, 600), "Double window works!");
                
                }
      
       
      window.clear();
      window.draw(sprite1);
      //auto const state = evolve(boids, steps_per_evolution, delta_t);

      for (unsigned int i = 0; i != uccelli.size(); ++i) {
      sprite.setPosition(uccelli[i].P.x, uccelli[i].P.y);
      window.draw(sprite);
      }

     if(window1.isOpen()==false) {window.draw(text);}
   
        window.display();
          
          window1.clear(sf::Color::White);
          window1.draw(sprite);
          window1.display();
        
    }

    return 0;
  


}

// std::vector<Velocity> Velocities1(uccelli.size());
//   for (unsigned int i = 0; i != Vicini.size(); ++i) {
//       if (dist(Vicini[i].u1, Vicini[i].u2) < 1.) {
//         Velocities1[Vicini[i].u1.UPN] += convertPtoV(
//             uccelli[Vicini[i].u2.UPN].P - uccelli[Vicini[i].u1.UPN].P);
//         Velocities1[Vicini[i].u2.UPN] += convertPtoV(
//             uccelli[Vicini[i].u1.UPN].P - uccelli[Vicini[i].u2.UPN].P);
//       }
//       }  //-> così velocities è un vettore con le velocità v1, però che non sono
//        // ancora state moltiplicate per il fattore s

//     for (unsigned int i = 0; i != Velocities1.size(); ++i) {
//       Velocities1[i] = Velocities1[i] / (-1 / s);
//     }
//     auto vs = Velocities1;

// for (unsigned int i = 0; i != Vicini.size(); ++i) {
//       if (dist(Vicini[i].u1, Vicini[i].u2) < 5.) {
//         std::cout<< "Distanza ok";
//       }
// }