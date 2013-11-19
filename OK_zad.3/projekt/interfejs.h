#ifndef	INTERFEJS_H
#define INTERFEJS_H

#include <iostream>
using namespace std;

/***********
*		TODO List		
*	
***********/

/***********
*	@ czas_wykonania
*		funkcja pokazuj�ca mo�liwe opcje wyboru zakresu losowanych liczb dla czas�w wykonania proces�w
*	@ Argumenty:
*		
*	@ Zwraca:
*		wybran� opj�			
* 
***********/
int czas_wykonania();



/***********
*	@ liczba_przestojow
*		funkcja pokazuj�ca mo�liwe opcje wyboru liczby losowanych przestojow
*	@ Argumenty:
*		
*	@ Zwraca:
*		wybran� opj�	
* 
***********/
int liczba_przestojow();


/***********
*	@ interfejs
*		funkcja drukuj�ca interfejs
*	@ Argumenty:
*		int &czas_wyk			adres zmiennej, kt�ra przechowuje wybor zakresow czasow wykonania
		int &liczba_przest		adres zmiennej, kt�ra przechowuje wybor zakresu liczby przestojow
		int &liczba_zadan		adres zmiennej, kt�ra przechowuje wybor zakresu liczby zadan
*	@ Zwraca:
*		
*	 
* 
***********/
void interfejs(int &czas_wyk,int &liczba_przest, int &liczba_zadan);


#endif //INTERFEJS_H