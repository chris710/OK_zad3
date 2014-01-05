#ifndef LOSOWY_H
#define LOSOWY_H

#include<fstream>	//do plików
#include<iostream>
#include<algorithm>	//do sortowania
#include "generator.h"
#include "maszyna.h"

/***********
*		TODO List
[DONE]	spe³nianie warunków zadania
*	wyw³aszczanie
*	zapis do pliku w odpowiednim formacie
*	wykonywanie operacji na ró¿nych maszynach
*	
***********/
void algorytmLosowy(const Generator& generator, int tablica[]);			// zwraca czas najdluzszego uszeregowania
void uszereguj(const Generator& generator, int tablica[]);

#endif //LOSOWY_H