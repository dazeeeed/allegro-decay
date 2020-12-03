#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <time.h>
#include <math.h>
#include <unistd.h>
#include "grafika.h"

int main (int argc, char *argv[])
{
	if(argc != 2)
	{
		fprintf(stderr,"Zla liczba argumentow\n");
		return 0;		
	}
	
	FILE *we = fopen(argv[1], "rb");
	if(!we)
	{
		fprintf(stderr,"Nie ma takiego pliku.\n");
		return 0;
	}

	uint16_t szerokosc, wysokosc;
	uint8_t n;
	fread(&szerokosc, sizeof(uint16_t),  1, we);
	fread(&wysokosc, sizeof(uint16_t),  1, we);
	fread(&n, sizeof(uint8_t),  1, we);
		
	utworz_okno (szerokosc, wysokosc, argv[1]);
	
	int *kolory = (int*) malloc( sizeof(int) * n);
	float *lambdy = (float*) malloc( sizeof(float) * n);
	uint32_t tmp, RR, GG, BB;
	
	for(int i=0; i<n; i++)
	{
		fread(&lambdy[i], sizeof(float),  1, we);
		fread(&tmp, sizeof(uint32_t),  1, we);
		RR = (tmp & 0x00FF0000) >> 16;
		GG = (tmp & 0x0000FF00) >> 8;
		BB = (tmp & 0x000000FF) >> 0;
		kolory[i] = makecol(RR, GG, BB);
		printf("Kolor %d: %u %u %u\n", i, RR,GG,BB );
	}
	
	struct atom *los=generuj_atomy(szerokosc, wysokosc, n, kolory, lambdy);
	int liczba_atomow=0;
	for(int i=0; i< szerokosc*wysokosc; i++)
	{
		putpixel(screen, los[i].x, los[i].y, los[i].kolor);
		if(los[i].kolor != 0)
			liczba_atomow++;
	}
	
	int zliczenia = 0,t=0, dt=10;			//jeśli psi < lambda * dt to oznacza, że w PRZEDZIALE dt nastąpił rozpad
	srand(time(NULL));
	while(1)  
	{
		int i = (int) rand() % (szerokosc * wysokosc);
		while(los[i].rozpadniety == true)
			i = (int) rand() % (szerokosc * wysokosc);
		double psi = (double) rand() / RAND_MAX;
		if( psi < los[i].lambda*dt ) 
			{
			los[i].rozpadniety = true;
			los[i].kolor = 0;
			zliczenia++;
			}
		putpixel(screen, los[i].x, los[i].y, los[i].kolor);
		printf("%i %i\t\t %lf %lf\n", t, zliczenia, psi, los[i].lambda*dt);
		
		if( liczba_atomow-zliczenia == liczba_atomow/4)
		{
			puts("Zakonczono symulacje!\n");
			break;
		}
		t+=dt;
		
	usleep(10);
	}

	
	free(los);
	free(kolory);
	free(lambdy);
	return 0;
}
