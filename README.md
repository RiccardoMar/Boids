# Installazione Cmake SFML
```bash
# Mac
brew install cmake sfml

# Ubuntu
sudo apt install cmake libsfml-dev
```

# Configurazione
```bash
#Cambia directory di lavoro in Boids
cd Boids
#Crea directory di build
mkdir build
cd build
#Comando di configurazione
cmake -DCMAKE_BUILD_TYPE=Release ../
```
# Build e creazione dell'eseguibile
```bash
cmake --build . -j4 --target Boids
#Testing
cmake --build build --target boids.t
```
### 2. Esecuzione

```bash
./Boids
```

# Progetto Boids
Questo si propone come progetto di programmazione della fisica.
L'obbiettivo finale e principale è quello di realizzare tramite il linguaggio C++ la Simulazione di Stormi.

Descrizione:
Il progetto consiste nell'implementazione di una simulazione del comportamento degli stormi di uccelli in volo in uno spazio bidimensionale.

Reso noto da un software di intelligenza artificiale realizzato nel 1986, la simulazione si basa sull'interazione tra agenti detti boids in uno spazio. Nel modello più elementare gli agenti determinano la loro traiettoria tramite tre regole:

Separazione: il boid si allontana dai boids vicini;
Allineamento: il boid tende ad allinearsi alle traiettorie dei boids vicini;
Coesione: il boid tende a muoversi verso il baricentro dei boids vicini;
Modelli più complessi introducono altre regole, per esempio per evitare gli ostacoli o per gestire stormi differenti.

