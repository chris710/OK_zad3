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

int algorytmLosowy(const Generator& generator);			// zwraca czas najdluzszego uszeregowania

#endif //LOSOWY_H