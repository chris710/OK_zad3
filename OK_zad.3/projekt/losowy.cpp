#include "losowy.h"

void algorytmLosowy(const Generator& generator)
{
	vector<Zadanie*> zadania = generator.zadania;	//tymczasowa tablica do usuwania zada�
	//sort(zadania.begin(), zadania.end());			//sortowanie tablicy po czasach gotowo�c

	int zadanie;									//zadanie do wykonania
	int preferred;									//preferowana maszyna

	while (zadania.size() != 0)
	{
		//wybieramy najmniej zawalon� maszyn�
		int a = generator.dlugosc(*generator.maszyny[0]),b = generator.dlugosc(*generator.maszyny[1]), c = generator.dlugosc(*generator.maszyny[2]);

		if(a<=b && a<=c)
			preferred = 0;
		else if(b<=a && b<=c)
			preferred = 1;
		else
			preferred = 2;


		while(true)												//p�ki czego� nie wsadzisz i nie trzeba wybiera� znowu maszyny losuj zadania
		{
			zadanie = random(0,zadania.size());	//losowanie zadania do wykonania

			if(!zadania[zadanie]->operacje[0]->done)		//wsad� pierwsze je�eli jeszcze tego nie zrobi�e�
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[zadanie]->operacje[0]);
				zadania[zadanie]->operacje[0]->done = true;
				break;
			}

			else if(!zadania[zadanie]->operacje[1]->done)	//drugie	<---- TODO uzupe�nij warunek
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[zadanie]->operacje[1]);
				zadania[zadanie]->operacje[1]->done = true;
				break;
			}
			else if(!zadania[zadanie]->operacje[2]->done)	//trzecie	<---- TODO uzupe�nij warunek
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[zadanie]->operacje[2]);
				zadania[zadanie]->operacje[2]->done = true;
				break;
			}
		}

	}
}