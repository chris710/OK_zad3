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
	int czas;		//d�ugo�� trwania operacji
	bool done;		//flaga uko�czenia operacji czyli �e kolejna mo�e si� zacz��
	int numer;		//kt�ra jest to operacja zadania
	Zadanie*	parent;	//wska�nik na rodzica

	//TODO konstruktory

	/******
	*	Konstruktor ustalaj�cy pole		czas
	*	@Argumenty:
	*		int czas	-	d�ugo�� trwania operacji
	*		int numer	-	kt�ra jest to operacja zadania
	****/
	Operacja(int czas, int numer, Zadanie* zadanie);


	//TODO metody operacjau

};


#endif