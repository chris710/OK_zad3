#ifndef operacja_H
#define operacja_H

#include<iostream>

/***********
		TODO LIST
[DONE]	-pola klasy(?)
*	-metody klasy(?)
***********/



//#include "zadanie.h"

///klasa operacja zadania
class Operacja
{
public:
	//TODO pola operacjau
	int czas;		//d�ugo�� trwania operacji
	bool done;		//flaga uko�czenia operacji czyli �e kolejna mo�e si� zacz��
	//int maszyna;	//na kt�rej maszynie jest wykonywana operacja

	//TODO konstruktory

	/******
	*	Konstruktor ustalaj�cy pole		czas
	*	@Argumenty:
	*		int czas	-	d�ugo�� trwania operacji
	****/
	Operacja(int czas);


	//TODO metody operacjau

};


#endif