#include "losowy.h"

void algorytmLosowy(const Generator& generator)
{
	vector<Zadanie*> zadania = generator.zadania;	//tymczasowa tablica do usuwania zadañ
	Zadanie* tmp;									//wskaŸnik do zamieniania miejscami w wektorze
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
			zadanie = random(0,zadania.size());		//losowanie zadania do wykonania

			tmp = zadania[zadanie];					//wymieniamy z ostatnim zadaniem w wektorze (do ewentualnego usuwania)
			zadania[zadanie] = zadania[zadania.size()-1];
			zadania[zadania.size()-1] = tmp;

			if(!zadania[zadanie]->operacje[0]->done)		//wsadŸ pierwsze je¿eli jeszcze tego nie zrobi³eœ
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[zadanie]->operacje[0]);	//wtykamy operacjê do uszeregowania
				zadania[zadanie]->operacje[0]->maszyna = generator.maszyny[preferred];					//ustawiamy gdzie jest dana operacja
				zadania[zadanie]->operacje[0]->done = true;												//okreœlamy operacjê jako wykonan¹
				break;		//wychodzimy z pêtli, szukamy najmniej zawalonej maszyny
			}

			else if(!zadania[zadanie]->operacje[1]->done && generator.czyMozna(*zadania[zadanie]->operacje[1],*generator.maszyny[preferred]))	//drugie	<---- TODO uzupe³nij warunek
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[zadanie]->operacje[1]);
				zadania[zadanie]->operacje[0]->maszyna = generator.maszyny[preferred];
				zadania[zadanie]->operacje[1]->done = true;
				break;
			}
			else if(!zadania[zadanie]->operacje[2]->done && generator.czyMozna(*zadania[zadanie]->operacje[2],*generator.maszyny[preferred]))	//trzecie	<---- TODO uzupe³nij warunek
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[zadanie]->operacje[2]);
				zadania[zadanie]->operacje[0]->maszyna = generator.maszyny[preferred];
				zadania[zadanie]->operacje[2]->done = true;
				zadania.pop_back();				//usuwamy zadanie, bo wszystkie jego operacje zosta³y wykonane
				break;
			}
		}

	}
}