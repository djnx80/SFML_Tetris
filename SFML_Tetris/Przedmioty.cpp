#include "stdafx.h"
#include "Przedmioty.h"


Przedmioty::Przedmioty() {
	pozycja = { 20,20 };
	przesuniecie = { 0,0 };
	//28, 31
	minX = 28;	minY = 31;	maxX = 208; maxY = 391;
	czasZyciaObiektuWSekundach = 0;
	aktywne = true;
	zegar.restart();
}

Przedmioty::Przedmioty(ListaObiektow obiekt)	{
	sprite = obiekt.getSprite();
	texture = obiekt.getTexture();
	szerokoscSprite = obiekt.getSzerokosc();
	wysokoscSprite = obiekt.getWysokosc();
	pozycja = { 0,0 };
	przesuniecie = { 0,0 };
	minX = 28;	minY = 31;	maxX = 208; maxY = 391;
	czasZyciaObiektuWSekundach = 0;
	aktywne = true;
	zegar.restart();
}
Przedmioty::~Przedmioty()	{}

void Przedmioty::setTextureAndSprite(ListaObiektow obiekt) {
	sprite = obiekt.getSprite();
	texture = obiekt.getTexture();
	szerokoscSprite = obiekt.getSzerokosc();
	wysokoscSprite = obiekt.getWysokosc();
}

void Przedmioty::updateMe(sf::RenderWindow &okno) {
	pozycja.x += przesuniecie.x;
	pozycja.y += przesuniecie.y;

	if (pozycja.x < minX)	pozycja.x = minX;
	if (pozycja.x > maxX-szerokoscSprite)	pozycja.x = maxX - szerokoscSprite;
	if (pozycja.y < minY)	pozycja.y = minY;
	if (pozycja.y > maxY - wysokoscSprite) pozycja.y = maxY - wysokoscSprite;
	sprite.setPosition(pozycja);

	float ileUplyneloCzasu = zegar.getElapsedTime().asSeconds();

	if (czasZyciaObiektuWSekundach>0 && ileUplyneloCzasu > czasZyciaObiektuWSekundach)
		aktywne = false;

	if (aktywne == true)	
		okno.draw(sprite);
}

bool Przedmioty::getSprites(sf::String filename, int startx, int starty, int szer, int wys) {

	if (!texture.loadFromFile(filename))
	{
		cout << "Nie wczytalem tekstury z pliku" << endl;
		getchar();
		return false;
	}

	sprite.setTextureRect(sf::IntRect(startx, starty, szer, wys));
	sprite.setTexture(texture);

	szerokoscSprite = szer;
	wysokoscSprite = wys;
	return true;
}

void Przedmioty::setAktywne(bool czyAktywne)	{
	aktywne = czyAktywne; 
	zegar.restart();
}

void Przedmioty::setMinAndMax(int nminx, int nminy, int nmaxx, int nmaxy) {
	minX = nminx;
	maxX = nmaxx;
	minY = nminy;
	maxY = nmaxy;

}