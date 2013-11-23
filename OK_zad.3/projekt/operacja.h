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
	int czas;		//d³ugoœæ trwania operacji
	bool done;		//flaga ukoñczenia operacji czyli ¿e kolejna mo¿e siê zacz¹æ
	//int maszyna;	//na której maszynie jest wykonywana operacja

	//TODO konstruktory

	/******
	*	Konstruktor ustalaj¹cy pole		czas
	*	@Argumenty:
	*		int czas	-	d³ugoœæ trwania operacji
	****/
	Operacja(int czas);


	//TODO metody operacjau

};


#endif