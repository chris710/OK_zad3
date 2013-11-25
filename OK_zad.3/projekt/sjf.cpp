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
	vector<int*> dlugosci;						// do usuniecia
	obliczanie_dlugosci(dlugosci,zadania);		// do usuniecia
	cout << "=================" << endl ;
	for (int  i=0; i< dlugosci.size();i++)		// do usuniecia
		cout << "\t" << *dlugosci[i] << endl;			// do usuniecia
	cout << "=================" << endl ;
	Zadanie* tmp;											//wskaŸnik do zamieniania miejscami w wektorze
	sort(zadania.begin(), zadania.end(), rosnaco);			//sortowanie tablicy po czasach trwania calego zadania
//	for (int  i=0; i< zadania.size();i++)		// do usuniecia		
//		cout << zadania[i]->operacje[0]->czas << endl;// do usuniecia

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
	

		break;
	}		


}