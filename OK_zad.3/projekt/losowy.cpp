#include "losowy.h"

void algorytmLosowy(const Generator& generator)
{
	vector<Zadanie*> zadania = generator.zadania;	//tymczasowa tablica do usuwania zada�
	//sort(zadania.begin(), zadania.end());			//sortowanie tablicy po czasach gotowo�c

	while (zadania.size() != 0)
	{
		int zadanie = random(0,zadania.size());
		if(!zadania[zadanie]->operacje[0]->done)
		{

		}
	}
}