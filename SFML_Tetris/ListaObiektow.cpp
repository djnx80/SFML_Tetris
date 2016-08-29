#include "stdafx.h"
#include "ListaObiektow.h"


ListaObiektow::ListaObiektow()
{
}


ListaObiektow::~ListaObiektow()
{
}


bool ListaObiektow::getSprites(sf::String filename, int startx, int starty, int szer, int wys) {

	if (!texture.loadFromFile(filename))
	{
		cout << "Nie wczytalem tekstury z pliku" << endl;
		getchar();
		return false;
	}

	sprite.setTextureRect(sf::IntRect(startx, starty, szer, wys));
	sprite.setTexture(texture);
	szerokosc = szer;
	wysokosc = wys;
	return true;
}