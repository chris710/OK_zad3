#include "operacja.h"

Operacja::Operacja(int czas, int numer, Zadanie* zadanie, int nrZad)
{
	this->czas = czas;
	this->numer = numer;
	this->parent = zadanie;
	this->done = false;
	this->nrZadania = nrZad;
}