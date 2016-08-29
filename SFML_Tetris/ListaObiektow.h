#pragma once
#include <SFML/Graphics.hpp>
#include <iostream>

using namespace std;

class ListaObiektow
{
private:
	sf::Texture texture;
	sf::Sprite sprite;
	int szerokosc;
	int wysokosc;

public:
	ListaObiektow();
	~ListaObiektow();
	bool ListaObiektow::getSprites(sf::String, int, int, int, int);
	void setSprite(sf::Sprite nowySprite) { sprite = nowySprite; }
	void setTexture(sf::Texture nowaTextura) { texture = nowaTextura; }
	void setNewObject(sf::Texture nowaTextura, sf::Sprite nowySprite) {
		sprite = nowySprite;
		texture = nowaTextura;
	}

	sf::Texture getTexture() { return texture; }
	sf::Sprite getSprite() { return sprite; }
	int getSzerokosc() { return szerokosc; }
	int getWysokosc() { return wysokosc; }
	void setPosition(sf::Vector2f newPos) { sprite.setPosition(newPos); }

};

