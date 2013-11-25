#include "sjf.h"

void obliczanie_dlugosci(vector<int*> &dlugosci, vector<Zadanie*> zadania){
	for (int i=0; i<zadania.size();i++){
		int suma=0;
		for(int j=0; j<3; j++)
			suma+=zadania[i]->operacje[j]->czas;
		dlugosci.push_back(new int(suma));
	}
}


bool rosnaco(Zadanie *const a, Zadanie *const b)
{
	int asuma=0, bsuma=0;
	for(int j=0; j<3; j++){
			asuma+=a->operacje[j]->czas;
			bsuma+=b->operacje[j]->czas;
	}
    return asuma < bsuma;
} 



void algorytmSJF(const Generator& generator)
{
	vector<Zadanie*> zadania = generator.zadania;			//tymczasowa tablica do usuwania zadañ
	vector<int*> nr_zadania;
	vector<int*> dlugosci;						// do usuniecia
	obliczanie_dlugosci(dlugosci,zadania);		// do usuniecia
	cout << "=================" << endl ;
	for (int  i=0; i< dlugosci.size();i++)		// do usuniecia
		cout << "\t" << *dlugosci[i] << endl;			// do usuniecia
	cout << "=================" << endl ;
	Zadanie* tmp;											//wskaŸnik do zamieniania miejscami w wektorze
	sort(zadania.begin(), zadania.end(), rosnaco);			//sortowanie tablicy po czasach trwania calego zadania
//	for (int  i=0; i< zadania.size();i++)						// do usuniecia		
//		cout << zadania[i]->operacje[0]->czas << endl;			// do usuniecia

	int nrZAD;												//zadanie do wykonania
	int preferred;											//preferowana maszyna
	
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
		
////////////////
		//cout << "Wybor Maszyny to=" << preferred << endl;
		while(true)														//póki czegoœ nie wsadzisz i nie trzeba wybieraæ znowu maszyny losuj zadania
		{
			nrZAD = 0;													// wybieramy najkrotszy czas
			if(!zadania[nrZAD]->operacje[0]->done)						//wsadŸ pierwsze je¿eli jeszcze tego nie zrobi³eœ
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[nrZAD]->operacje[0]);		//wtykamy operacjê do uszeregowania
				zadania[nrZAD]->operacje[0]->maszyna = generator.maszyny[preferred];					//ustawiamy gdzie jest dana operacja
				zadania[nrZAD]->operacje[0]->done = true;												//okreœlamy operacjê jako wykonan¹
				break;		//wychodzimy z pêtli, szukamy najmniej zawalonej maszyny
			}
			else if(!zadania[nrZAD]->operacje[1]->done && generator.czyMozna(*zadania[nrZAD]->operacje[1],*generator.maszyny[preferred]))	//drugie	<---- TODO uzupe³nij warunek
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[nrZAD]->operacje[1]);
				zadania[nrZAD]->operacje[0]->maszyna = generator.maszyny[preferred];
				zadania[nrZAD]->operacje[1]->done = true;
				break;
			}
			else if(!zadania[nrZAD]->operacje[2]->done && generator.czyMozna(*zadania[nrZAD]->operacje[2],*generator.maszyny[preferred]))	//trzecie	<---- TODO uzupe³nij warunek
			{
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[nrZAD]->operacje[2]);
				zadania[nrZAD]->operacje[0]->maszyna = generator.maszyny[preferred];
				zadania[nrZAD]->operacje[2]->done = true;
				//-------
				tmp = zadania[nrZAD];									//wymieniamy z ostatnim zadaniem w wektorze (do usuwania)
				zadania[nrZAD] = zadania[zadania.size()-1];		
				zadania[zadania.size()-1] = tmp;
				zadania.pop_back();										//usuwamy zadanie, bo wszystkie jego operacje zosta³y wykonane
				break;
			}

		break;
		}
	break;
	}

	for (int i=0; i<3; i++){
		cout << "NR " << i << " MASZYNA:" << endl;
		for (int j=0; j<1; j++){
			cout << "OP = " << generator.maszyny[0]->uszeregowanie[0]->numer << "\t\tZAD = " << generator.maszyny[0]->uszeregowanie[0]->nrZadania << endl;
		}}
}