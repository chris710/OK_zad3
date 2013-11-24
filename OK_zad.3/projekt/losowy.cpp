#include "losowy.h"

void algorytmLosowy(const Generator& generator)
{
	vector<Zadanie*> zadania = generator.zadania;	//tymczasowa tablica do usuwania zadañ
	//sort(zadania.begin(), zadania.end());			//sortowanie tablicy po czasach gotowoœc

	int zadanie;									//zadanie do wykonania
	int preferred;									//preferowana maszyna

	while (zadania.size() != 0)
	{
		//wybieramy najmniej zawalon¹ maszynê
		int a = generator.dlugosc(*generator.maszyny[0]),b = generator.dlugosc(*generator.maszyny[1]), c = generator.dlugosc(*generator.maszyny[2]);

		if(a<=b && a<=c)
			preferred = 0;
		else if(b<=a && b<=c)
			preferred = 1;
		else
			preferred = 2;


		while(true)												//póki czegoœ nie wsadzisz i nie trzeba wybieraæ znowu maszyny losuj zadania
		{
			zadanie = random(0,zadania.size());	//losowanie zadania do wykonania

			if(!zadania[zadanie]->operacje[0]->done)		//wsadŸ pierwsze je¿eli jeszcze tego nie zrobi³eœ
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[zadanie]->operacje[0]);
				zadania[zadanie]->operacje[0]->done = true;
				break;
			}

			else if(!zadania[zadanie]->operacje[1]->done)	//drugie	<---- TODO uzupe³nij warunek
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[zadanie]->operacje[1]);
				zadania[zadanie]->operacje[1]->done = true;
				break;
			}
			else if(!zadania[zadanie]->operacje[2]->done)	//trzecie	<---- TODO uzupe³nij warunek
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[zadanie]->operacje[2]);
				zadania[zadanie]->operacje[2]->done = true;
				break;
			}
		}

	}
}