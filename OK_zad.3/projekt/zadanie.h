#ifndef ZADANIE_H
#define ZADANIE_H

//#include "operacja.h"

/*****************
		TODO List
*
*
*****************/

class Operacja;			//deklaracja wyprzedzaj�ca

class Zadanie			///klasa zadania
{
    public:
		Operacja* operacje[3];	//tablica trzech operacja�w zadania
		int delay;		//czas op�nienia pierwszej operacji
		
		
		//TODO konsturktory
		Zadanie();

		//TODO destruktor
		~Zadanie();
		//TODO metody klasy
    protected:
    private:
};

#endif // ZADANIE_H
