#include <stdio.h>
#include <time.h>
#include <math.h>
#include "grafika.h"

void utworz_okno (int szerokosc, int wysokosc, const char *tytul)
{
	allegro_init ();
	install_keyboard ();
	install_timer ();
	set_color_depth (32);
	set_gfx_mode (GFX_AUTODETECT_WINDOWED, szerokosc, wysokosc, 0, 0);
	set_window_title (tytul);

}


void zakoncz (void)
{
	allegro_exit ();
}

struct atom *generuj_atomy(uint16_t szerokosc, uint16_t wysokosc, uint8_t n, const int kolory[], const float lambdy[])
{
	srand(time(NULL));
	
	struct atom *los;
	los = (struct atom*) malloc( sizeof(struct atom) * szerokosc * wysokosc );
	int i = 0;
	for(unsigned int x=0; x<szerokosc; x++)
	{
		for(unsigned int y=0; y<wysokosc; y++)
		{
			int l = rand()% n;
			los[i].x = x;
			los[i].y = y;
			los[i].lambda = lambdy[l];
			los[i].kolor = kolory[l];
			los[i].rozpadniety = false;
			i++;
			 
		}
	}
	
	return los;
}
