UState.hpp:
-   struct Position: dichiarazione metodi e operatori; 2 variabili pubbliche: x ed y
-   struct Velocity: dichiarazione operatori; 2 variabili pubbliche: vx ed vy
-   struct UState: 3 variabili pubbliche: UPN (ovvero il numero progressivo uccelli), Position, Velocity; dichiarazione operator== e membro dist
-   dichiarazione free function dist e ostream per UState


UState.cpp:
-   Definizioni metodi e operatori di Position, di Velocity e di UState;
-   Definizione free function dist e ostream per UState






















<!-- uccelli     :   vettore di tipo std::vector<UState> che contiene tutti gli Ustate degli uccelli, messi in fila. 
UState      :   struct che contiene lo stato di un uccello. Come variabili, ha: x, y, vx, vy. 
                Inoltre, ha un metodo operator== che verifica uguaglianza fra UState e una free function operator<< che manda in output gli elementi di UState.
Vicini      :   vettore di tipo std::vector<Coppia> che contiene tutte le coppie di uccelli che, nell'istante in cui viene chiamata la funzione, stanno ad una distanza gli uni dagli altri minore di d
Check       :   funzione che prende il vettore uccelli e una distanza e da in output il vettore Vicini -->
