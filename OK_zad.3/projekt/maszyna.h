#ifndef MASZYNA_H
#define MASZYNA_H

#include<vector>
#include "operacja.h"

using namespace std;
/*************
		TODO List
*
*
*
*************/


class Maszyna				///klasa operacjaora
{
    public:
		//TODO pola klasy
		int nPrzestojow;			//ilo�� przestoj�w
		vector<int> rozpoczecie;				//wska�nik na wektor z czasami rozpocz�cia czas�w przestoj
		vector<int> dlugosc;					//wska�nik na wektor z czasami trwania czas�w przestoju
		vector<Operacja*> uszeregowanie;	//wektor zawieraj�cy uszeregowanie operacja�w

		//TODO konstruktory
		Maszyna();
		//TODO metody

    protected:
    private:
};

#endif // MASZYNA_H
