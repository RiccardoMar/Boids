UState.hpp:
-   struct Position: dichiarazione metodi e operatori; 2 variabili pubbliche: x ed y
-   struct Velocity: dichiarazione operatori; 2 variabili pubbliche: vx ed vy
-   struct UState: 3 variabili pubbliche: UPN (ovvero il numero progressivo uccelli), Position, Velocity; dichiarazione operator== e membro dist
-   dichiarazione free function dist e ostream per UState


UState.cpp:
-   Definizioni metodi e operatori di Position, di Velocity e di UState;
-   Definizione free function dist e ostream per UState


neighbours.check.hpp:
-   struct Coppia: 2 variabili pubbliche: UState u1 e UState u2; Da passare by ref? Da farci il costruttore?
-   Definizione della funzione Check : prende un vettore di UState, detto uccelli, e un parametro distanza, e poi, con dei cicli for, da in output un vettore di Coppie, detto Vicini






















<!-- uccelli     :   vettore di tipo std::vector<UState> che contiene tutti gli Ustate degli uccelli, messi in fila. 

Vicini      :   vettore di tipo std::vector<Coppia> che contiene tutte le coppie di uccelli che, nell'istante in cui viene chiamata la funzione, stanno ad una distanza gli uni dagli altri minore di d
Check       :   funzione che prende il vettore uccelli e una distanza e da in output il vettore Vicini -->
