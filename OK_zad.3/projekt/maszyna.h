#ifndef MASZYNA_H
#define MASZYNA_H

#include<vector>
//#include "operacja.h"
#include "zadanie.h"	//do obliczania d³ugoœci

using namespace std;
/*************
		TODO List
*
*
*
*************/


class Operacja;			//deklaracja wyprzedzaj¹ca


class Maszyna				///klasa operacjaora
{
    public:
		//TODO pola klasy
		int nPrzestojow;					//iloœæ przestojów
		vector<int> rozpoczecie;			//wskaŸnik na wektor z czasami rozpoczêcia czasów przestoj
		vector<int> dlugosc;				//wskaŸnik na wektor z czasami trwania czasów przestoju
		vector<Operacja*> uszeregowanie;	//wektor zawieraj¹cy uszeregowanie operacjaów

		//TODO konstruktory
		Maszyna();


		//TODO metody
		

    protected:
    private:
};

#endif // MASZYNA_H
