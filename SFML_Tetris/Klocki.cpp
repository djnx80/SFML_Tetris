#include "stdafx.h"
#include "Klocki.h"


Klocki::Klocki()
{
	ktoryAktywny = 1;
}


Klocki::~Klocki()
{
}

void Klocki::przesunWBok(int ktora, int **tabTemp) {
	//	if (klocek.x == 0 && klocek.budowa) return;

	klocek.x += ktora;


	bool zachaczylo = false;

	// usun poprzednio wpisany klocek z poziomu
	for (int i = 0; i < 5; i++) {
		if (tabTemp[0][25] != -1) {
			int tx = tabTemp[i][25];
			int ty = tabTemp[i][26];
			if (tx != -1 && ty != -1) {
				tabTemp[tabTemp[i][25]][tabTemp[i][26]] = -1;
			}
		}
	}

	// sprawdz czy wyszlo za plansze lub zachaczylo o inny klocek
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int x = klocek.x;
			int y = klocek.y;
			if (klocek.budowa[i][j] != -1) {
				if (x + i < 0 || x + i > 10) {
					std::cout << "wyszlo z lewej strony" << endl;
					zachaczylo = true;
				}
				else {
					if (tabTemp[x + i][y + j] != -1) {
						zachaczylo = true;
						std::cout << "zachaczylo" << endl;
					}
					//			tabTemp[x + i][y + j] = klocek.budowa[i][j];
				}
			}
		}
	}

	// jezeli nic nie zachaczylo ani nie osiagnelo dna to przepisz tablice pomocnicze do normalnych
	if (zachaczylo == true) {
		klocek.x -= ktora;
	}
}

void Klocki::setKlocek(int ktoryKlocek) {
	for (int i = 0; i < 4; i++)
		for (int j = 0; j < 4; j++)
			klocek.budowa[i][j] = -1;

	if (ktoryKlocek == 1) {
		cout << "ustawiam klocka 1" << endl;
		klocek.typKlocka = 0;
		klocek.x = 4;
		klocek.y = 0;
		klocek.budowa[0][3] = 1;
		klocek.budowa[1][3] = 1;
		klocek.budowa[2][3] = 1;
		klocek.budowa[2][2] = 1;
	}

	if (ktoryKlocek == 2) {
		cout << "ustawiam klocka 1" << endl;
		klocek.typKlocka = 0;
		klocek.x = 4;
		klocek.y = 0;
		klocek.budowa[0][3] = 2;
		klocek.budowa[1][3] = 2;
		klocek.budowa[1][2] = 2;
		klocek.budowa[2][2] = 2;
	}

	if (ktoryKlocek == 3) {
		cout << "ustawiam klocka 1" << endl;
		klocek.typKlocka = 0;
		klocek.x = 4;
		klocek.y = 0;
		klocek.budowa[0][3] = 3;
		klocek.budowa[0][2] = 3;
		klocek.budowa[1][2] = 3;
		klocek.budowa[2][2] = 3;
	}

	if (ktoryKlocek == 4) {
		cout << "ustawiam klocka 1" << endl;
		klocek.typKlocka = 0;
		klocek.x = 3;
		klocek.y = 0;
		klocek.budowa[0][0] = 4;
		klocek.budowa[1][0] = 4;
		klocek.budowa[2][0] = 4;
		klocek.budowa[3][0] = 4;
	}

}

void Klocki::obrocKlocek(int **tabTemp) {
	// obroc klocek o 90 stopni
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			klocek.temp[j][i] = klocek.budowa[3 - i][j];
		}
	}


	// sprawdz czy po obrocie o nic nie zachaczy, lub nie wyjdzie za plansze

	bool zachaczylo = false;

	// usun poprzednio wpisany klocek z poziomu
	for (int i = 0; i < 5; i++) {
		if (tabTemp[0][25] != -1) {
			int tx = tabTemp[i][25];
			int ty = tabTemp[i][26];
			if (tx != -1 && ty != -1) {
				tabTemp[tabTemp[i][25]][tabTemp[i][26]] = -1;
			}
		}
	}

	// sprawdz czy wyszlo za plansze lub zachaczylo o inny klocek
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int x = klocek.x;
			int y = klocek.y;
			if (klocek.temp[i][j] != -1) {
				if (x + i < 0 || x + i > 10) {
					std::cout << "wyszlo z lewej strony" << endl;
					zachaczylo = true;
				}
				else {
					if (tabTemp[x + i][y + j] != -1) {
						zachaczylo = true;
						std::cout << "zachaczylo" << endl;
					}
					//			tabTemp[x + i][y + j] = klocek.budowa[i][j];
				}
			}
		}
	}

	// jezeli nic nie zachaczylo ani nie osiagnelo dna to przepisz tablice pomocnicze do normalnych
	if (zachaczylo == false) {
		for (int i = 0; i < 4; i++) {
			for (int j = 0; j < 4; j++) {
				klocek.budowa[i][j] = klocek.temp[i][j];
			}
		}

	}

}
