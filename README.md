# Cub3D - Raycasting Engine

Questo progetto, parte del curriculum della scuola 42, è un'introduzione al mondo del Raycasting. L'obiettivo è creare una rappresentazione dinamica in 3D di un labirinto a partire da una mappa 2D, ispirandosi al celebre videogioco degli anni '90, *Wolfenstein 3D*.

## Funzionalità Principali (Parte Obbligatoria)

Il motore di gioco base (presente nella cartella `cub3D/`) offre un'esperienza fluida e stabile, rispettando rigorosamente le direttive del progetto:

* **Motore di Raycasting:** Calcolo preciso delle intersezioni dei raggi per renderizzare un ambiente 3D in prima persona.
* **Texture Mapping:** Le pareti del labirinto sono texturizzate in base alla loro esposizione cardinale (Nord, Sud, Est, Ovest).
* **Colori RGB:** Il pavimento (Floor) e il soffitto (Ceiling) sono renderizzati con colori RGB personalizzabili direttamente dal file di configurazione della mappa.
* **Movimento Fluido:** Gestione degli input per muoversi nel labirinto (avanti, indietro, strafe a destra e sinistra) e ruotare la telecamera in modo continuo.
* **Parsing Rigoroso:** Un parser robusto (`check_map.c`, `map_loader.c`) che valida il file `.cub` per assicurarsi che la mappa sia chiusa (circondata da muri), che non ci siano caratteri invalidi e che il giocatore abbia una posizione di spawn corretta.
* **Gestione della Memoria:** Assenza totale di memory leaks e chiusura pulita del programma in caso di errori o uscita.

## Compilazione e Utilizzo (Base)

Per compilare la versione base del progetto:

```bash
cd cub3D
make
```

```bash
./cub3D maps/test.cub
```
## Controlli Base

* **W / A / S / D:** Muovi il personaggio (Avanti, Sinistra, Indietro, Destra).

* **Frecce Direzionali (← / →):** Ruota la visuale a sinistra e a destra.

* **ESC (o click sulla 'X' della finestra):** Esci dal gioco.

## Parte BONUS: (Versione Estesa)

La versione Bonus del progetto (cub3D_bonus/) trasforma il semplice motore di raycasting in un vero e proprio mini-gioco completo. È stata aggiunta un'enorme quantità di funzionalità, trasformando l'esplorazione in un'avventura survival con interfaccia grafica e nemici animati.

**Funzionalità Aggiuntive Bonus**

1. **Menu Principale e Interfaccia Utente (UI)**

    * Menu di Selezione: All'avvio, il giocatore viene accolto da un menu interattivo (menu_bonus.c) dove è possibile navigare e selezionare visivamente la mappa da giocare (es. Cheese Maze, Creepy, Dungeon, Matrix).

    * HUD in Game: Durante il gioco è presente una vera e propria interfaccia utente.

    * Healthbar: Una barra della salute dinamica (draw_healthbar_bonus.c) che si svuota quando si subiscono danni.

    * Contatore FPS: Visualizzazione in tempo reale dei frame per secondo (fps_bonus.c) per monitorare le performance del motore.

2. **Minimappa Dinamica**

    * Orientamento in tempo reale: Una minimappa in sovraimpressione (minimap_bonus.c) che disegna la griglia del livello.

    * Tracking del Giocatore: La posizione del giocatore è chiaramente visibile con una freccia (minimap_arrow_bonus.c) che ruota in base alla direzione dello sguardo.

    * Radar Nemici: Sulla minimappa vengono tracciate anche le posizioni degli zombie, utile per pianificare i propri movimenti in anticipo.

3. **Interazione Ambientale: Porte**

    * Porte Apribili/Chiudibili: Il sistema di raycasting è stato potenziato per riconoscere blocchi "porta". Le porte hanno texture dedicate e possono essere attraversate dal giocatore, aggiungendo profondità al level design.

4. **Sistema di Nemici (Zombies AI)**

	* Pathfinding e Movimento: Gli zombie si muovono all'interno della mappa cercando il giocatore.

    * Sistema di Animazione Avanzato: I nemici sono completamente animati tramite una macchina a stati (zombie_animator_bonus.c) che carica ed esegue in sequenza decine di frame in formato .xpm:

        * Walking: Oltre 25 frame per l'animazione della camminata.

        * Attacking: Animazioni dedicate quando lo zombie è a portata per ferire il giocatore.

        * Hitted: Reazione visiva ai danni subiti.

        * Dying: Ben 20 frame fluidi per l'animazione della sconfitta del nemico.


## Compilazione e Utilizzo (Bonus)

Per godere dell'esperienza completa con menu, nemici e minimappa:

```bash
cd cub3D_bonus
make

./cub3D_bonus maps/test.cub
```