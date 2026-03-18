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

# Laiko efektyvumo testai v1.0


