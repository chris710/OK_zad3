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
	int czas;		//d�ugo�� trwania operacji
	bool done;		//flaga uko�czenia operacji czyli �e kolejna mo�e si� zacz��
	int numer;		//kt�ra jest to operacja zadania
	int nrZadania;
	Zadanie*	parent;	//wska�nik na rodzica
	Maszyna* maszyna;	//wska�nik na maszyn�, na kt�rej jest operacja

	//TODO konstruktory

	/******
	*	Konstruktor ustalaj�cy pole		czas
	*	@Argumenty:
	*		int czas	-	d�ugo�� trwania operacji
	*		int numer	-	kt�ra jest to operacja zadania
	****/
	Operacja(int czas, int numer, Zadanie* zadanie, int nrZad);


	//TODO metody operacjau

};


#endif