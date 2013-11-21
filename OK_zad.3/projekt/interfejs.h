#ifndef	INTERFEJS_H
#define INTERFEJS_H

#include <iostream>
#include "generator.h"
using namespace std;

/***********
*		TODO List		
*	
***********/

/***********
*	@ czas_wykonania
*		funkcja pokazuj¹ca mo¿liwe opcje wyboru zakresu losowanych liczb dla czasów wykonania operacjaów
*	@ Argumenty:
*		
*	@ Zwraca:
*		wybran¹ opjê			
* 
***********/
int czas_wykonania();



/***********
*	@ liczba_przestojow
*		funkcja pokazuj¹ca mo¿liwe opcje wyboru liczby losowanych przestojow
*	@ Argumenty:
*		
*	@ Zwraca:
*		wybran¹ opjê	
* 
***********/
int liczba_przestojow();


/***********
*	@ interfejs
*		funkcja drukuj¹ca interfejs
*	@ Argumenty:
*		int &czas_wyk			adres zmiennej, która przechowuje wybor zakresow czasow wykonania
		int &liczba_przest		adres zmiennej, która przechowuje wybor zakresu liczby przestojow
		int &liczba_zadan		adres zmiennej, która przechowuje wybor zakresu liczby zadan
*	@ Zwraca:
*		
*	 
* 
***********/
void interfejs(int &czas_wyk,int &liczba_przest, int &liczba_zadan);



/**********
*	@ wyswietlZadanie
*		funkcja wyœwietlaj¹ca w konsoli dane zadania i nale¿¹cych do niego operacji
*	@Argumenty:
*		Zadanie& zadanie		odniesienie do klasy	Zadanie, z której pobierane s¹ dane
*	@Zwraca:
*		nic
**********/
void wyswietlZadanie(const Zadanie& zadanie);

#endif //INTERFEJS_H