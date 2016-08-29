#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>
#include "ListaObiektow.h"

using namespace std;

class Przedmioty
{

private:
	sf::Texture texture;
	sf::Sprite sprite;
	sf::Vector2f pozycja;
	sf::Vector2f przesuniecie;
	sf::Clock zegar;
	float czasZyciaObiektuWSekundach;	// =0 to caly czas aktywne, chyba ze aktywne =false
	int szerokoscSprite;
	int wysokoscSprite;
	int minX, maxX, minY, maxY;		// min i maxymalne wartosci na ktore moze sie przemieszczac sprajt
	bool aktywne;						// aktywne == false -> nie wyswietlaj



public:
	Przedmioty();
	Przedmioty(ListaObiektow);
	~Przedmioty();
	
	// nowe pozycje i przesuniecia
	void setPozycje(sf::Vector2f nowaPozycja) { pozycja = nowaPozycja; }
	void porusz(sf::Vector2f przesuniecie) { pozycja.x += przesuniecie.x; pozycja.y += przesuniecie.y; }
	void setDXY(sf::Vector2f nowePrzesuniecie) { przesuniecie = nowePrzesuniecie; }
	sf::Vector2f getDXY() { return przesuniecie; }
	sf::Vector2f getPozycja() { return pozycja; }
	void negujDX() { przesuniecie.x = -przesuniecie.x; }
	void negujDY() { przesuniecie.y = -przesuniecie.y; }
	void setMinAndMax(int, int, int, int);

	sf::Texture getTeksture() { return texture; }
	sf::Sprite getSprite() { return sprite; }
	bool getSprites(sf::String, int, int, int, int);
	void setTextureAndSprite(ListaObiektow);

	void setCzasZyciaObiektu(float ileSekund) { czasZyciaObiektuWSekundach = ileSekund; zegar.restart(); }
	void setAktywne(bool);
	bool getCzyAktywny() { return aktywne; }
	void updateMe(sf::RenderWindow &);
	int getSzerokoscSprite() { return szerokoscSprite; }
	int getWysokoscSprite() { return wysokoscSprite; }
};

