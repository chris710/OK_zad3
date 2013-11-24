#include "generator.h"

/*******
		TODO List
*	pouk�ada� te �mieci z maina
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
	Result->operacje[0] = new Operacja(random(minDlugosc, maxDlugosc));
	Result->operacje[1] = new Operacja(random(minDlugosc, maxDlugosc));
	Result->operacje[2] = new Operacja(random(minDlugosc, maxDlugosc));
	
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
	//oszacowanie d�ugo�ci instancji
	for(int i = 0; i<this->liczbaZadan; ++i)
	{
		for(int j=0; j<3; ++j)
			(this->dlugoscInstancji) += this->zadania[i]->operacje[j]->czas;
	}
	for(int j = 0; j < Result->dlugosc.size(); ++j)
			this->dlugoscInstancji += Result->dlugosc[j];

	int przedzial = (this->dlugoscInstancji/3)/Result->nPrzestojow;			//d�ugo�� na jednej maszynie podzielona przez ilo�� przestoj�w
	for(int i = 1; i<=Result->nPrzestojow; ++i)
	{
		Result->rozpoczecie.push_back(i*przedzial);
	}
	return *Result;
}





int random(int min, int max)
{
	int result, lower = max-min;
	if(max == 0) return 0;
	result = rand()%lower + min;
	return result;
}