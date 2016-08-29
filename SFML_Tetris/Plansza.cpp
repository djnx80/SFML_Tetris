#include "stdafx.h"
#include "Plansza.h"



Plansza::Plansza()
{
	czasCalkowitySekundy = 0;
	zegar.restart();
	ileX = 10;
	ileY = 20;

	ofset = {18, 18};
	ofsetOdKrawedzi = { 28, 81 };

	for (int i = 0; i < ileX; i++)
		for (int j = 0; j < ileY; j++)
			poziom[i][j] = -1;

	// ustaw klocki na samym dole 
	for (int i = 0; i < ileX; i++)
			poziom[i][ileY] = 1;

	for (int i = 0; i < 5; i++)
		coBylo[i] = { -1,-1 };


	zycia = 3;
	punkty = 0;
	ktoryPoziom = 1;
	ileLinWyczysciles = 0;
	ileCzasuCzekac = 500;
	czyJuzMoznaRuszyc = true;
	zegar.restart();

//	CzyNastepnyKlocek = false;
}


Plansza::~Plansza()	{	}

void Plansza::ustawKlocekNaPlanszy(Klocki::klocekDane klocek) {
	int nr = 0;
	int poziomTemp[30][30];
	bool zachaczylo = false;

	if (czyNastepnyKlocek == true)	czyNastepnyKlocek = false;

	// skopiuj poziom do tablic pomocniczych
	for (int i = 0; i < ileX; i++) {
		for (int j = 0; j < ileY; j++) {
			poziomTemp[i][j] = poziom[i][j];
		}
	}

	// usun poprzednio wpisany klocek z poziomu
	for (int i = 0; i < 5; i++) {
		if (coBylo[i].x != -1)
			poziomTemp[coBylo[i].x][coBylo[i].y] = -1;
	}

	// dopisz nowa pozycje klocka do poziomu pomocniczego
	for (int i = 0; i < 4; i++) {
		for (int j = 0; j < 4; j++) {
			int x = klocek.x;
			int y = klocek.y;
			if (klocek.budowa[i][j] != -1) {
				if (poziomTemp[x + i][y + j] != -1) {
					zachaczylo = true;
					std::cout << "zachaczylo" << endl;
				}
			//	if (x + i > ileX)	zachaczylo = true;
				if (x + i < 0) {
					zachaczylo = false; }
				else {
					poziomTemp[x + i][y + j] = klocek.budowa[i][j];
					coBylo[nr] = { x + i, y + j };
					nr++;

				}
//				poziomTemp[x + i][y + j] = klocek.budowa[i][j];
//				coBylo[nr] = { x + i, y + j };
//				nr++;
			}
		}
	}

	// jezeli nic nie zachaczylo ani nie osiagnelo dna to przepisz tablice pomocnicze do normalnych
	if (zachaczylo == false) {

		for (int i = 0; i < ileX; i++) {
			for (int j = 0; j < ileY; j++) {
				poziom[i][j] = poziomTemp[i][j];
			}
		}

	}	else	{
		for (int i = 0; i < 5; i++)
			coBylo[i] = { -1, -1 };
		czyNastepnyKlocek = true;
	}

}
void Plansza::updateMe(sf::RenderWindow &okno, ListaObiektow obiekty[]) {
	sf::Sprite tempsprite;
	sf::Texture temptexture;

	tempsprite = obiekty[10].getSprite();
//	temptexture = obiekty[10].getTexture();
	okno.draw(tempsprite);		// tlo

	sf::String napis;
	napis = "Tetris ver 1.0 Made With SFML\n";
	napis = napis + "Zycia " + to_string(zycia) + "    Poziom " + to_string(ktoryPoziom) + "   Punkty " + to_string(punkty);
	napisz(okno, sf::Vector2f(5, 5), napis);

	for (int i = 0; i < ileX; i++) {
		for (int j = 0; j < ileY; j++) {
			int coJest = poziom[i][j];
			if (coJest != -1)
			{
				tempsprite = obiekty[coJest].getSprite();
	//			temptexture = obiekty[coJest].getTexture();

				tempsprite.setPosition(ofsetOdKrawedzi.x + (i * ofset.x), ofsetOdKrawedzi.y + (j * ofset.y));
				okno.draw(tempsprite);
			}
		}
		cout << endl;
	}
}
void Plansza::updateMe(sf::RenderWindow &okno) {
	napisz(okno, sf::Vector2f(50, 50), "jakis tam napis");
}
bool Plansza::setCzcionka(sf::String fontname, int rozmiar, sf::Color kolor) {
	if (!font.loadFromFile(fontname))	{
		cout << "Nie udalo sie wczytac czcionki" << endl;
		return false;
	}

	text.setFont(font);			// wybranie czcionki
	text.setCharacterSize(rozmiar); // w pikselach, nie punktach!
	text.setColor(kolor);
	return true;
}
void Plansza::napisz(sf::RenderWindow &okno, sf::Vector2f pozycjaNapisu , sf::String coNapisac) {
	text.setPosition(pozycjaNapisu);
	text.setString(coNapisac);
	okno.draw(text);
}
void Plansza::czekaj(int ileCzasuWMilisekundach) {
	sf::Clock zegarTemp;
	zegarTemp.restart();
	do {		// odczekaj czas
	} while (zegarTemp.getElapsedTime().asMilliseconds()<ileCzasuWMilisekundach);
}

bool Plansza::czyMoznaRuszycWDol(int ileCzasuWMilisekundach) {
	if (zegar.getElapsedTime().asMilliseconds() < ileCzasuWMilisekundach) {
		cout << zegar.getElapsedTime().asMilliseconds() << endl;
		return false;
	}
	else
	{
		zegar.restart();
		return true;
	}

}
int ** Plansza::getPoziom() {
	int rows = 30;
	int columns = 30;

	int** tabTemp = new int*[rows];
	for (int i = 0; i < rows; i++) {
		tabTemp[i] = new int[columns];
		for (int j = 0; j < columns; j++) { tabTemp[i][j] = 0; }    
	}


	// skopiuj tablice
	for (int i = 0; i < ileX; i++) {
		for (int j = 0; j < ileY; j++) {
			tabTemp[i][j] = poziom[i][j];
		}
	}

	// zapisz do tablicy pozycje coBylo, w wierszu 25 i 26
	for (int i = 0; i < 5; i++) {
		tabTemp[i][25] = coBylo[i].x;
		tabTemp[i][26] = coBylo[i].y;
	}
	return tabTemp;
}
void Plansza::sprawdzCzyJestLinia() {
	int tempIleWX = 0;
	bool czyBylaLinia = false;

	do
	{

		czyBylaLinia = false;

		// sprawdz czy sa pelne linie w poziomie
		for (int j = ileY-1; j > 0; j--) {
			tempIleWX = 0;
			for (int i = 0; i < ileX; i++) {
				if (poziom[i][j] != -1) {
					tempIleWX++;
				}
			}
			// jezeli jest pelna linia to ja wykasuj
			if (tempIleWX == 10) {
				czyBylaLinia = true;
				punkty = punkty + (50 * ktoryPoziom);
				ileLinWyczysciles++;
				cout << "jest linia na poziomie " << j << endl;
				for (int i = 0; i < ileX; i++) {
					poziom[i][j] = -1;
				}
				for (int k = j; k > 1; k--) {
					for (int i = 0; i < ileX; i++) {
						poziom[i][k] = poziom[i][k-1];
					}

				}
				j=1;
			}
		}

	} while (czyBylaLinia == true);
	
		ktoryPoziom = (ileLinWyczysciles / 3) + 1;
		ileCzasuCzekac = 550 - (ktoryPoziom * 100);
		if (ileCzasuCzekac < 50)
			ileCzasuCzekac = 50;

}

void Plansza::setIleCzasuCzekac(int ileCzasu) {
	if (ileCzasu != -1) {
		ileCzasuCzekac = ileCzasu;
	}
	else
	{
		ileCzasuCzekac = 550 - (ktoryPoziom * 100);
		if (ileCzasuCzekac < 50)
			ileCzasuCzekac = 50;

	}
}
