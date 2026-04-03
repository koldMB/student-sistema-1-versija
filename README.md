# Testavimo kompiuterio specifikacijos

Processor	AMD Ryzen 5 5600H with Radeon Graphics 3.30 GHz

Installed RAM	16,0 GB (13,9 GB usable)

System type	64-bit operating system, x64-based processor

Edition	Windows 11 Home
Version	23H2

Disk 1 (C:)

	WDC PC SN530 SDBPMPZ-512G-1101

	Capacity:	477 GB
	Formatted:	477 GB
	System disk:	Yes
	Page file:	Yes
	Type:	SSD

Disk 0 (D: E:)

	ADATA LEGEND 710

	Capacity:	477 GB
	Formatted:	477 GB
	System disk:	No
	Page file:	No
	Type:	SSD

Memory

	16,0 GB

	Speed:	3200 MT/s
	Slots used:	1 of 2
	Form factor:	SODIMM
	Hardware reserved:	2,1 GB

GPU 0

	NVIDIA GeForce RTX 3060 Laptop GPU

	Driver version:	32.0.15.7283
	Driver date:	2025-03-14
	DirectX version:	12 (FL 12.1)
	Physical location:	PCI bus 1, device 0, function 0

	Dedicated GPU memory	0,1/6,0 GB
	Shared GPU memory	0,0/6,9 GB
	GPU Memory	0,1/12,9 GB

GPU 1

	AMD Radeon(TM) Graphics

	Driver version:	31.0.21921.13001
	Driver date:	2025-07-07
	DirectX version:	12 (FL 12.1)
	Physical location:	PCI bus 6, device 0, function 0

	Dedicated GPU memory	0,5/2,0 GB
	Shared GPU memory	0,1/6,9 GB
	GPU Memory	0,6/8,9 GB


# Laiko efektyvumo testai v0.4

_Čia žiurėkite tik į failų generavimo testą, duomenų apdorojimas yra man kai generavau failus_

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

### Vidurkiai failų apdorojimui (vector 0.4 versija)

| Studentų kiekis | Skaitymas     | Rūšiavimas    | Rašymas       | Visas laikas  |
|----------------|---------------|---------------|---------------|---------------|
| 1 000          | 12 ms         | 2,25 ms       | 3 ms          | 17,25 ms      |
| 10 000         | 75,25 ms      | 24,25 ms      | 22,5 ms       | 122 ms        |
| 100 000        | 730 ms        | 340 ms        | 213,25 ms     | 1283,25 ms    |
| 1 000 000      | 1407 ms       | 712,75 ms     | 428,5 ms      | 2548,25 ms    |
| 10 000 000     | 74361,75 ms   | 52784,5 ms    | 21344,5 ms    | 148490,8 ms   |
# Laiko efektyvumo testai v1.0
(Čia be pritaikitų algoritmų)
## Deque

![deque test 1](deque/Screenshot%202026-03-26%20211141.png)
![deque test 2-5](deque/Screenshot%202026-03-26%20211152.png)
![deque test 5](deque/Screenshot%202026-03-26%20211158.png)

### Vidurkiai failų apdorojimui (Deque v1.0)
| Studentų kiekis | Skaitymas   | Rūšiavimas  | Rašymas     | Visas laikas |
|----------------|-------------|-------------|-------------|---------------|
| 1 000          | 8.6 ms      | 2.6 ms      | 4.8 ms      | 16 ms         |
| 10 000         | 84 ms       | 34.2 ms     | 22.6 ms     | 140.8 ms      |
| 100 000        | 674.4 ms    | 398.4 ms    | 210 ms      | 1282.8 ms     |
| 1 000 000      | 1283.4 ms   | 855.6 ms    | 412.8 ms    | 2551.8 ms     |
| 10 000 000     | 66892.6 ms  | 64840.6 ms  | 21481.8 ms  | 153215 ms     |
## List

![list test 1](list/Screenshot%202026-03-26%20205654.png)
![list test 2-5](list/Screenshot%202026-03-26%20205710.png)
![list test 5](list/Screenshot%202026-03-26%20205720.png)

### Vidurkiai failų apdorojimui (List v1.0)

| Studentų kiekis | Skaitymas     | Rūšiavimas    | Rašymas       | Visas laikas  |
|----------------|---------------|---------------|---------------|---------------|
| 1 000          | 12 ms         | 2.25 ms       | 3 ms          | 17.25 ms      |
| 10 000         | 75.25 ms      | 24.25 ms      | 22.5 ms       | 122 ms        |
| 100 000        | 730 ms        | 340 ms        | 213.25 ms     | 1283.25 ms    |
| 1 000 000      | 1407 ms       | 712.75 ms     | 428.5 ms      | 2548.25 ms    |
| 10 000 000     | 74361.75 ms   | 52784.5 ms    | 21344.5 ms    | 148490.8 ms   |
## Optimizavimo vėliavėlės v1.1

### Klasės versija testas 1

![O1 class 1](Kompiliavimo%20optimizavimas%20nuotraukos/O1%20class%201.png)
![O1 class 2](Kompiliavimo%20optimizavimas%20nuotraukos/O1%20class%202.png)
![O2 class 1](Kompiliavimo%20optimizavimas%20nuotraukos/O2%20class%201.png)
![O2 class 2](Kompiliavimo%20optimizavimas%20nuotraukos/O2%20class%202.png)
![O3 class 1](Kompiliavimo%20optimizavimas%20nuotraukos/O3%20class%201.png)
![O3 class 2](Kompiliavimo%20optimizavimas%20nuotraukos/O3%20class%202.png)

### Klasės versija

 Versija | Exe failo dydis 
---------|-----------------
 O1      | 90 KB           
 O2      | 113 KB          
 O3      | 134 KB          

O1 versija

 Skaitymas | Rušiavimas | Rašmas | Visas laikas 
-----------|------------|--------|--------------
 6,6       | 0,6        | 3,2    | 10,4         
 52,6      | 16,6       | 20,4   | 89,6         
 390,8     | 144,4      | 180,2  | 715,4        
 707,4     | 365,4      | 358,2  | 1431         
 40704,4   | 26894,6    | 24890  | 92489        


O2 versija

 Skaitymas | Rušiavimas | Rašmas  | Visas laikas 
-----------|------------|---------|--------------
 6,8       | 0,8        | 4       | 11,6         
 41,2      | 13,2       | 20,4    | 74,8         
 422,2     | 176,6      | 188,6   | 787,4        
 744,4     | 328        | 345,8   | 1418,2       
 40893,4   | 47441,2    | 21496,6 | 109831,2     

O3 versija

 Skaitymas | Rušiavimas | Rašmas  | Visas laikas 
-----------|------------|---------|--------------
 5,8       | 0,2        | 4       | 10           
 48,4      | 11,4       | 18,6    | 78,4         
 408       | 177,6      | 206     | 791,6        
 714,4     | 380,2      | 368,2   | 1462,8       
 41899,2   | 45956,8    | 22088,2 | 109944,2     


### Struktūros versija testas 1

![O1 struct](Kompiliavimo%20optimizavimas%20nuotraukos/O1%20struct.png)
![O2 struct](Kompiliavimo%20optimizavimas%20nuotraukos/O2%20struct.png)
![O3 struct](Kompiliavimo%20optimizavimas%20nuotraukos/O3%20struct.png)

### Struktūros versija

| Versija | Exe failo dydis |
|---------|-----------------|
| O1      | 462 KB          |
| O2      | 429 KB          |
| O3      | 429 KB          |

O1 versija

| Skaitymas (ms) | Rūšiavimas (ms) | Rašymas (ms) | Iš viso (ms) |
|----------------|-----------------|--------------|--------------|
| 6,6            | 0               | 3,2          | 9,8          |
| 28,4           | 3,6             | 14,2         | 46,2         |
| 232,6          | 53,2            | 155,2        | 441          |
| 454,6          | 105,2           | 285,2        | 845          |
| 22552,2        | 7739,2          | 12592,8      | 42884,2      |

O2 versija

| Skaitymas (ms) | Rūšiavimas (ms) | Rašymas (ms) | Iš viso (ms) |
|----------------|-----------------|--------------|--------------|
| 2,6            | 0               | 2,2          | 4,8          |
| 28             | 3,8             | 16,4         | 48,2         |
| 245,2          | 55,4            | 141          | 441,6        |
| 405,6          | 115,2           | 253,6        | 774,4        |
| 21627,8        | 7808,8          | 12422,2      | 41858,8      |

O3 versija

| Skaitymas (ms) | Rūšiavimas (ms) | Rašymas (ms) | Iš viso (ms) |
|----------------|-----------------|--------------|--------------|
| 2,6            | 0               | 2,6          | 5,2          |
| 22,8           | 3,2             | 14,8         | 40,8         |
| 220,8          | 60              | 155,8        | 436,6        |
| 456,4          | 113,8           | 304,6        | 874,8        |
| 21103,6        | 7508,4          | 12939,6      | 41551,6      |
