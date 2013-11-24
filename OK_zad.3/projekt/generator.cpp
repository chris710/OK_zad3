#include "generator.h"

/*******
		TODO List
*	pouk³adaæ te œmieci z maina
*
********/

Generator::Generator(int nZadan)
{
	this->liczbaZadan = nZadan;
	this->dlugoscInstancji = 0;

}



void Generator::generujZadanie(int minDlugosc, int maxDlugosc, int delay)
{
	Zadanie* Result = new Zadanie();
	this->zadania.push_back(Result);
	Result->delay = random(0,delay);
	Result->operacje[0] = new Operacja(random(minDlugosc, maxDlugosc), 0, Result);
	Result->operacje[1] = new Operacja(random(minDlugosc, maxDlugosc), 1, Result);
	Result->operacje[2] = new Operacja(random(minDlugosc, maxDlugosc), 2, Result);
	
	//return Result;
}


Maszyna Generator::generujMaszyne(int nPrzestojowMin,int nPrzestojowMax, int czasPrzestojow)
{
	Maszyna* Result = new Maszyna();
	this->maszyny.push_back(Result);
	Result->nPrzestojow = random(nPrzestojowMin, nPrzestojowMax);
	for (int i = 0; i < Result->nPrzestojow; ++i)
	{
		Result->dlugosc.push_back(random(5,czasPrzestojow));
	}
	//oszacowanie d³ugoœci instancji
	for(int i = 0; i<this->liczbaZadan; ++i)
	{
		for(int j=0; j<3; ++j)
			(this->dlugoscInstancji) += this->zadania[i]->operacje[j]->czas;
	}
	for(int j = 0; j < Result->dlugosc.size(); ++j)
			this->dlugoscInstancji += Result->dlugosc[j];

	int przedzial = (this->dlugoscInstancji/3)/Result->nPrzestojow;			//d³ugoœæ na jednej maszynie podzielona przez iloœæ przestojów
	for(int i = 1; i<=Result->nPrzestojow; ++i)
	{
		Result->rozpoczecie.push_back(i*przedzial);
	}
	return *Result;
}



bool Generator::czyWejdzie(Maszyna & maszyna, Operacja & operacja)
{
	bool flag = true;		//wynik
	//obliczanie obecnej d³ugoœci uszeregowania
	int rozmiar = 0;
	for(int i = 0; i<maszyna.uszeregowanie.size(); ++i)
	{
		rozmiar += maszyna.uszeregowanie[i]->czas;
	}
	//sprawdzenie
	for( int i = 0; i<maszyna.rozpoczecie.size(); ++i)
	{
		if(maszyna.rozpoczecie[i] < rozmiar && (maszyna.rozpoczecie[i]+maszyna.dlugosc[i] > rozmiar+operacja.czas) ||
			maszyna.rozpoczecie[i] > rozmiar && (maszyna.rozpoczecie[i]+maszyna.dlugosc[i] < rozmiar+operacja.czas))
			flag = false;
	}
	return flag;
}


int Generator::dlugosc(Maszyna & maszyna)
{
	int result = 0;
	for(int i = 0; i < maszyna.uszeregowanie.size(); ++i)
	{
		if(maszyna.uszeregowanie[i]->numer == 0)	result += maszyna.uszeregowanie[i]->parent->delay;

		result += maszyna.uszeregowanie[i]->czas;
	}
	return result;
}





int random(int min, int max)
{
	int result, lower = max-min;
	if(max == 0) return 0;
	result = rand()%lower + min;
	return result;
}