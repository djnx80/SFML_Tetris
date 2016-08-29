#pragma once
#include <SFML/Graphics.hpp>
#include "ListaObiektow.h"
#include <iostream>
#include "Klocki.h"

using namespace std;

class Plansza
{
private:
	sf::Font font;
	sf::Text text;
	sf::Clock zegar;
	bool czyJuzMoznaRuszyc;
	float czasCalkowitySekundy;
	int poziom[30][30];
	sf::Vector2i coBylo[5];
	sf::Vector2f ofset;
	sf::Vector2f ofsetOdKrawedzi;
	int ileX;
	int ileY;
	bool czyNastepnyKlocek;
	int zycia, punkty, ktoryPoziom;
	int ileLinWyczysciles;
	int ileCzasuCzekac;

public:
	Plansza();
	~Plansza();

	void ustawKlocekNaPlanszy(Klocki::klocekDane);
	void updateMe(sf::RenderWindow &, ListaObiektow []);
	void updateMe(sf::RenderWindow &);

	// funkcje odpowiedzialne za czas
	void restartCzas() { czasCalkowitySekundy += zegar.getElapsedTime().asSeconds(); zegar.restart();}
	sf::Int32 getCzasMilisekundy() { return zegar.getElapsedTime().asMilliseconds(); }
	float getCzasSekundy() { return zegar.getElapsedTime().asSeconds(); }
	float getCzasCalkowity() { return czasCalkowitySekundy; }
	void czekaj(int);
	bool czyMoznaRuszycWDol(int);
	int getIleCzasuCzekac() { return ileCzasuCzekac; }
	void setIleCzasuCzekac(int);

	// funkcje odpowiedzialne za czcionki i napisy
	bool setCzcionka(sf::String, int, sf::Color);
	void napisz(sf::RenderWindow &, sf::Vector2f, sf::String);

	bool sprawdzKolizje(sf::Sprite s1, sf::Sprite s2)	{ return s1.getGlobalBounds().intersects(s2.getGlobalBounds());	}

	int getIleX() { return ileX; }
	int getIleY() { return ileY; }
	bool getCzyNastepnyKlocek() {  return czyNastepnyKlocek; }
	int** getPoziom();
	void sprawdzCzyJestLinia();
//	sf::Vector2i[] getCoBylo() { return coBylo[]; }
};


