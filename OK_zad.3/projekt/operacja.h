#ifndef operacja_H
#define operacja_H

#include<iostream>
#include "zadanie.h"

/***********
		TODO LIST
[DONE]	-pola klasy(?)
*	-metody klasy(?)
***********/


///klasa operacja zadania
class Operacja
{
public:
	//TODO pola operacjau
	int czas;		//d³ugoœæ trwania operacji
	bool done;		//flaga ukoñczenia operacji czyli ¿e kolejna mo¿e siê zacz¹æ
	int numer;		//która jest to operacja zadania
	Zadanie*	parent;	//wskaŸnik na rodzica

	//TODO konstruktory

	/******
	*	Konstruktor ustalaj¹cy pole		czas
	*	@Argumenty:
	*		int czas	-	d³ugoœæ trwania operacji
	*		int numer	-	która jest to operacja zadania
	****/
	Operacja(int czas, int numer, Zadanie* zadanie);


	//TODO metody operacjau

};


#endif