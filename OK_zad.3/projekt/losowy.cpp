#include "losowy.h"

void algorytmLosowy(const Generator& generator)
{
	vector<Zadanie*> zadania = generator.zadania;	//tymczasowa tablica do usuwania zada�
	Zadanie* tmp;									//wska�nik do zamieniania miejscami w wektorze
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
			zadanie = random(0,zadania.size());		//losowanie zadania do wykonania

			tmp = zadania[zadanie];					//wymieniamy z ostatnim zadaniem w wektorze (do ewentualnego usuwania)
			zadania[zadanie] = zadania[zadania.size()-1];
			zadania[zadania.size()-1] = tmp;

			if(!zadania[zadanie]->operacje[0]->done)		//wsad� pierwsze je�eli jeszcze tego nie zrobi�e�
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[zadanie]->operacje[0]);	//wtykamy operacj� do uszeregowania
				zadania[zadanie]->operacje[0]->maszyna = generator.maszyny[preferred];					//ustawiamy gdzie jest dana operacja
				zadania[zadanie]->operacje[0]->done = true;												//okre�lamy operacj� jako wykonan�
				break;		//wychodzimy z p�tli, szukamy najmniej zawalonej maszyny
			}

			else if(!zadania[zadanie]->operacje[1]->done && generator.czyMozna(*zadania[zadanie]->operacje[1],*generator.maszyny[preferred]))	//drugie	<---- TODO uzupe�nij warunek
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[zadanie]->operacje[1]);
				zadania[zadanie]->operacje[0]->maszyna = generator.maszyny[preferred];
				zadania[zadanie]->operacje[1]->done = true;
				break;
			}
			else if(!zadania[zadanie]->operacje[2]->done && generator.czyMozna(*zadania[zadanie]->operacje[2],*generator.maszyny[preferred]))	//trzecie	<---- TODO uzupe�nij warunek
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[zadanie]->operacje[2]);
				zadania[zadanie]->operacje[0]->maszyna = generator.maszyny[preferred];
				zadania[zadanie]->operacje[2]->done = true;
				zadania.pop_back();				//usuwamy zadanie, bo wszystkie jego operacje zosta�y wykonane
				break;
			}
		}

	}
}