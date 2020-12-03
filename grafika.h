#ifndef _grafika_h_
#define _grafika_h_

#include <allegro.h>

// Uruchamia tryb graficzny
void utworz_okno (int szerokosc, int wysokosc, const char *tytul);

// Zamyka tryb graficzny
void zakoncz (void);

struct atom
{
	int x;
	int y;
	float lambda;
	int kolor;
	bool rozpadniety;
	
};

struct atom *generuj_atomy(uint16_t szerokosc, uint16_t wysokosc, uint8_t n, const int kolory[], const float lambdy[]);


#endif
