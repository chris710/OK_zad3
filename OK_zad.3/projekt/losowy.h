#ifndef LOSOWY_H
#define LOSOWY_H

#include<fstream>	//do plik�w
#include<iostream>
#include<algorithm>	//do sortowania
#include "generator.h"
#include "maszyna.h"

/***********
*		TODO List
[DONE]	spe�nianie warunk�w zadania
*	wyw�aszczanie
*	zapis do pliku w odpowiednim formacie
*	wykonywanie operacji na r�nych maszynach
*	
***********/
void algorytmLosowy(const Generator& generator, int tablica[]);			// zwraca czas najdluzszego uszeregowania
void uszereguj(const Generator& generator, int tablica[]);

#endif //LOSOWY_H