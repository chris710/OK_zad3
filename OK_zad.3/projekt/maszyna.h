#ifndef MASZYNA_H
#define MASZYNA_H

#include<vector>
#include "zadanie.h"	//do obliczania d�ugo�ci

using namespace std;
/*************
		TODO List
*
*
*
*************/


class Operacja;			//deklaracja wyprzedzaj�ca


class Maszyna				///klasa operacjaora
{
    public:
		//TODO pola klasy
		int numer;							//numer maszyny
		int nPrzestojow;					//ilo�� przestoj�w
		vector<int> rozpoczecie;			//wska�nik na wektor z czasami rozpocz�cia czas�w przestoj
		vector<int> dlugosc;				//wska�nik na wektor z czasami trwania czas�w przestoju
		vector<Operacja*> uszeregowanie;	//wektor zawieraj�cy uszeregowanie operacji

		//TODO konstruktory
		Maszyna(int numer);


    protected:
    private:
};

#endif // MASZYNA_H
