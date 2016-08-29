#include "stdafx.h"
#include <SFML/Graphics.hpp>
#include <iostream>
#include "Przedmioty.h"
#include "Plansza.h"
#include "ListaObiektow.h"
#include "Klocki.h"

using namespace std;

int main()	{
	srand(time(NULL));
	sf::RenderWindow okno(sf::VideoMode(320, 530), "Okno");
	okno.setVerticalSyncEnabled(true);	// 60fps

	Plansza level;
	level.setCzcionka("BornAddict.ttf", 16, sf::Color::White);

	ListaObiektow obiekty[20];
	for (int i=0; i<8; i++)
		if (obiekty[i].getSprites("images/tiles.png", 18*i, 0, 18, 18) == false) return -1;
	if (obiekty[10].getSprites("images/background.png", 0, 0, 320, 480) == false) return -1;
	obiekty[10].setPosition(sf::Vector2f(0, 50));
	Klocki klocek;
	klocek.setKlocek(4);


	while (okno.isOpen())
	{
		sf::Event event;
		while (okno.pollEvent(event)) {
			if (event.type == sf::Event::Closed)	okno.close();
		}

		int kierunek = 0;
		level.setIleCzasuCzekac(-1);		//-1 czyli automatycznie ustaw czas wzgledem poziomu
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape))	okno.close();
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))		kierunek = 1;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))	kierunek = 2;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))		kierunek = 3;
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))		level.setIleCzasuCzekac(10); // level.getIleCzasuCzekac() / 10);
		
		int **tabTemp = level.getPoziom();
		if (kierunek == 1)	klocek.przesunWBok(-1, tabTemp);
		if (kierunek == 2)	klocek.przesunWBok(1, tabTemp);
		if (kierunek == 3)	klocek.obrocKlocek(tabTemp);

		level.ustawKlocekNaPlanszy(klocek.getKlocek());
		if (level.getCzyNastepnyKlocek() == true) {
			level.sprawdzCzyJestLinia();
//			klocek.setKlocek(4);
			klocek.setKlocek((rand() % 4) + 1);
		}
		okno.clear();
		level.updateMe(okno, obiekty);
		okno.display();
		level.czekaj(120);
		if (level.czyMoznaRuszycWDol(level.getIleCzasuCzekac()) == true) {
			klocek.updateMe();
		}
	}
	return 0;
}

