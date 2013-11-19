#ifndef ZADANIE_H
#define ZADANIE_H

#include "operacja.h"

/*****************
		TODO List
*
*
*****************/

class Zadanie			///klasa zadania
{
    public:
		Operacja* operacje[3];	//tablica trzech operacjaów zadania
		int delay;		//czas opóŸnienia pierwszej operacji
		
		
		//TODO konsturktory
		Zadanie();

		//TODO destruktor
		~Zadanie();
		//TODO metody klasy
    protected:
    private:
};

#endif // ZADANIE_H
