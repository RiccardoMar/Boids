UState.hpp:
-   struct Position: dichiarazione metodi e operatori; 2 variabili pubbliche: x ed y
-   struct Velocity: dichiarazione operatori; 2 variabili pubbliche: vx ed vy
-   struct UState: 3 variabili pubbliche: UPN (ovvero il numero progressivo uccelli), Position, Velocity; dichiarazione operator== e membro dist
-   dichiarazione free function dist e ostream per UState


UState.cpp:
-   Definizioni metodi e operatori di Position, di Velocity e di UState;
-   Definizione free function dist e ostream per UState


neighbours.check.hpp:
-   struct Coppia: 2 variabili pubbliche: UState u1 e UState u2; Da passare by ref? 
-   Definizione della funzione Check : prende un vettore di UState, detto uccelli, e un parametro distanza, e poi, con dei cicli for, da in output un vettore di Coppie, detto Vicini


main.cpp:
-   variabili per la metrica e per sfml
-   input del numero di boids
-   creazione vettore uccelli, che contiene quel numero di UState
-   engine random che assegna posizione x e y e velocità vx e vy random
-   for loop che assegna gli UPN agli uccelli (=identificativo)
-   input dei parametri s, a, c
-   creazione oggetto boids di tipo Boids
<!-- evolve & state & solve -->
<!-- output della media e della deviazione standard -->


flight.rules.hpp:
<!-- da fare  -->


boids.hpp:
-   Dichiarazione classe Boids, che contiene 4 variabili private: vettore uccelli, oggetto sep, oggetto all, oggetto coe; in più, ha un costruttore


boids.test.cpp:
