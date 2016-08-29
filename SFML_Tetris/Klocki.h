#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
//#include "Plansza.h"

using namespace std;

class Klocki
{
private:
	int ktoryAktywny;

public:
	struct klocekDane {
		int x, y;
		int typKlocka;
		int budowa[4][4];
		int temp[4][4];
	} klocek;

	Klocki();
	~Klocki();

	void updateMe() { klocek.y += 1; }
	void przesunWBok(int, int **);
	void setKlocek(int);
	klocekDane getKlocek() { return klocek; }
	void obrocKlocek(int **);
};

