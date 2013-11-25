#ifndef operacja_H
#define operacja_H

#include<iostream>
#include "zadanie.h"
#include "maszyna.h"

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
	int nrZadania;
	Zadanie*	parent;	//wskaŸnik na rodzica
	Maszyna* maszyna;	//wskaŸnik na maszynê, na której jest operacja

	//TODO konstruktory

	/******
	*	Konstruktor ustalaj¹cy pole		czas
	*	@Argumenty:
	*		int czas	-	d³ugoœæ trwania operacji
	*		int numer	-	która jest to operacja zadania
	****/
	Operacja(int czas, int numer, Zadanie* zadanie, int nrZad);


	//TODO metody operacjau

};


#endif