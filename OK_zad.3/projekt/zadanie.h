#ifndef ZADANIE_H
#define ZADANIE_H

#include "proces.h"

/*****************
		TODO List
*
*
*****************/

class Zadanie			///klasa zadania
{
    public:
		Proces* procesy[3];	//tablica trzech procesów zadania
		int delay;		//czas opóŸnienia pierwszej operacji
		
		//TODO metody klasy
		//TODO konsturktory
		Zadanie();
    protected:
    private:
};

#endif // ZADANIE_H
