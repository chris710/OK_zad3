#ifndef	INTERFEJS_H
#define INTERFEJS_H

#include <iostream>
#include "generator.h"

using namespace std;

/***********
*		TODO List		
*	napisz funkcjê pobieraj¹c¹ od u¿ytkownika maksymalny czas trwania przestoju i czasu gotowoœci dla zadañ oraz...
*	popraw te dane u¿ywane do generowania w funkcji	interfejs
***********/




/*********
*	@ liczba_zadan
*		wczytuje od u¿ytkownika liczbê zadañ dla generatora
*	@zwraca:
*		liczbê zadañ podan¹ przez usera
*********/
int liczba_zadan();


/***********
*	@ liczba_przestojow
*		wczytuje od u¿ytkownika liczbê losowanych przestojow
*	@ Argumenty:
*		
*	@ Zwraca:
*		wybran¹ przestojów podan¹ przez usera	
* 
***********/
int liczba_przestojow();

/***********
*	@ przestojeMIN/MAX
*		funkcja zwracaj¹ca min/max liczbê przestojów
*	@ Argumenty:
*		int wybor=wybor opcji otrzymany z liczba_przestojow()
*	@ Zwraca:
*		wybran¹ czas	
* 
***********/


/***********
*	@ interfejs
*		funkcja drukuj¹ca interfejs
*	@ Argumenty:
*		int &czas_wyk			adres zmiennej, która przechowuje wybor zakresow czasow wykonania
		int &liczba_przest		adres zmiennej, która przechowuje wybor zakresu liczby przestojow
		int &liczba_zadan		adres zmiennej, która przechowuje wybor zakresu liczby zadan
*	@ Zwraca:
*		nic
***********/


void interfejs(Generator & generator, int nPrzestojow);



/**********
*	@ wyswietlZadania
*		funkcja wyœwietlaj¹ca w konsoli dane zadania i nale¿¹cych do niego operacji
*	@Argumenty:
*		Generator generator		odniesienie do klasy	Generator, z której pobierane s¹ dane
*	@Zwraca:
*		nic
**********/
void wyswietlZadania(const Generator& generator);



/**********
*	@ wyswietlMaszyny
*		funkcja wyœwietlaj¹ca w konsoli dane maszyny i jej przestoje
*	@Argumenty:
*		Generator generator		odniesienie do klasy	Generator, z której pobierane s¹ dane
*	@Zwraca:
*		nic
**********/
void wyswietlMaszyny(const Generator& generator);

#endif //INTERFEJS_H