# Laiko efektyvumo testai v0.4

## Čia žiurėkite tik į failų generavimo testą, duomenų apdorojimas yra man

Milisekundė (ms) - viena tūkstantoji sekundės dalis
![testas](04%20versija%20screenshotai/PirmasTestas.png)
![testas](04%20versija%20screenshotai/AntrasTestas.png)
![testas](04%20versija%20screenshotai/TreciasTestas.png)
![testas](04%20versija%20screenshotai/KetvirtasTestas.png)
![testas](04%20versija%20screenshotai/PenktasTestas.png)

### Vidurkiai failų generavimui:

1. 1 000 studentų - 29,6 ms
2. 10 000 studentų - 285,8 ms
3. 100 000 studentų - 2751,2 ms
4. 1 000 000 studentų - 27461,8 ms
5. 10 000 000 studentų - 275001,6 ms

## Nuo čia yra tikrinamas duomenų apdorojimas su tais pačiais failais

![testas2](04%20versija%20screenshotai/2Testas1.png)
![testas2](04%20versija%20screenshotai/2Testas2.png)

### Vidurkiai failų apdorojimui:

1. 1 000 studentų:
   * Skaitymas - 12 ms
   * Rūšiavimas - 2,25 ms
   * Rašymas - 3 ms
   * Visas laikas - 17,25 ms
2. 10 000 studentų:
   * Skaitymas - 75,25 ms
   * Rūšiavimas - 24,25 ms
   * Rašymas - 22,5 ms
   * Visas laikas - 122 ms
3. 100 000 studentų:
   * Skaitymas - 730 ms
   * Rūšiavimas - 340 ms
   * Rašymas - 213,25 ms
   * Visas laikas - 1283,25 ms
4. 1 000 000 studentų:
   * Skaitymas - 1407 ms
   * Rūšiavimas - 712,75 ms
   * Rašymas - 428,5 ms
   * Visas laikas - 2548,25 ms
5. 10 000 000 studentų:
   * Skaitymas - 74361,75 ms
   * Rūšiavimas - 52784,5 ms
   * Rašymas - 21344,5 ms
   * Visas laikas - 148490,8 ms


