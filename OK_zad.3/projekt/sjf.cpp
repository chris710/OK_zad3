#include "sjf.h"
#include <cmath>
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

int czas_uszeregowania(Generator generator, int i){
	int suma=0;
	for (int j=0; j<generator.maszyny[i]->uszeregowanie.size(); j++)
				suma+= generator.maszyny[i]->uszeregowanie[j]->czas ;
	return suma;
}

void kara(vector<Zadanie*> zadania, int op, int zad ){
	zadania[zad]->operacje[op]->czas+= ceil(zadania[zad]->operacje[op]->czas*0.3);
	//cout << zadania[i]->operacje[i]->czas << endl;
}

bool czy_juz_gotowy(int gotowosc, vector<Operacja*> uszeregowanie){
	int x=0;
	//cout << "ROZMIAR SZEREGOWANIA=" << uszeregowanie.size() <<endl;
	for (int i=0; i<uszeregowanie.size();i++)
		x+=uszeregowanie[i]->czas;
	//cout << "\n got=" <<gotowosc << "\t x=" << x<< endl;
	if(gotowosc<=x)
		return true;
	else
		return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////

void algorytmSJF(const Generator& generator)
{
	vector<Zadanie*> zadania = generator.zadania;			//tymczasowa tablica do usuwania zadañ
	vector<int*> dlugosci;						// do usuniecia
	obliczanie_dlugosci(dlugosci,zadania);		// do usuniecia
	cout << "=================" << endl ;
	for (int  i=0; i< dlugosci.size();i++)		// do usuniecia
		cout << "dl=" << *dlugosci[i] << "\tGOT="<< generator.zadania[i]->delay << endl;			
	cout << "=================" << endl ;		// do usuniecia

	Maszyna* maszyna;										//wskaŸnik na preferowan¹ maszynê
	Operacja * op = new Operacja(1,98,NULL,98);				//operacja zapychacz
	sort(zadania.begin(), zadania.end(), rosnaco);			//sortowanie tablicy po czasach trwania calego zadania
	int nrZAD=-1;											//zadanie do wykonania
	int preferred;											//preferowana maszyna
	int kwantCZASU=0;
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/	
	while (zadania.size() != 0)
	{														
		int a = czas_uszeregowania(generator,0);			//wybieramy najmniej zawalon¹ maszynê
		int b = czas_uszeregowania(generator,1);
		int c = czas_uszeregowania(generator,2);
		//cout << "A=" <<a<< endl;
		if(a<=b && a<=c)
			preferred = 0;
		else if(b<=a && b<=c)
			preferred = 1;
		else
			preferred = 2;
		
		//cout << "ROZMIAR ZADANIA=" << zadania.size()-1 << endl;
		if (nrZAD < (zadania.size()-1))
			nrZAD++;
		else
			nrZAD=0;
		//cout << "maszyna=" << preferred << endl;

/**//**//**//**//**//**//**//**//**/		
		while(true)														//póki czegoœ nie wsadzisz i nie trzeba wybieraæ znowu maszyny losuj zadania
		{
			maszyna=generator.maszyny[preferred];
			if(!zadania[nrZAD]->operacje[0]->done && czy_juz_gotowy(zadania[nrZAD]->delay, generator.maszyny[preferred]->uszeregowanie))					//wsadŸ pierwsze je¿eli jeszcze tego nie zrobi³eœ
			{		
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[nrZAD]->operacje[0]);		//wtykamy operacjê do uszeregowania
				zadania[nrZAD]->operacje[0]->maszyna = generator.maszyny[preferred];					//ustawiamy gdzie jest dana operacja
				zadania[nrZAD]->operacje[0]->done = true;												//okreœlamy operacjê jako wykonan¹
				break;															//wychodzimy z pêtli, szukamy najmniej zawalonej maszyny
			}
			else if(zadania[nrZAD]->operacje[0]->done)
				if(!zadania[nrZAD]->operacje[1]->done && 
				generator.czyMozna(*zadania[nrZAD]->operacje[1],kwantCZASU) && 
				zadania[nrZAD]->operacje[0]->maszyna != maszyna)
				{
					maszyna->uszeregowanie.push_back(zadania[nrZAD]->operacje[1]);
					zadania[nrZAD]->operacje[1]->maszyna = maszyna;
					zadania[nrZAD]->operacje[1]->done = true;
					break;	
				}
				else if((zadania[nrZAD]->operacje[1]->done))			//sprawdzenie czy 2 operacja zosta³a wykonana
				{
				if(!zadania[nrZAD]->operacje[2]->done && 
					generator.czyMozna(*zadania[nrZAD]->operacje[2],kwantCZASU) && 
					zadania[nrZAD]->operacje[0]->maszyna != maszyna && 
					zadania[nrZAD]->operacje[1]->maszyna != maszyna)	//trzecie	
				{
					maszyna->uszeregowanie.push_back(zadania[nrZAD]->operacje[2]);
					zadania[nrZAD]->operacje[2]->maszyna = maszyna;
					zadania[nrZAD]->operacje[2]->done = true;
					zadania.erase( zadania.begin()+nrZAD);					//usuwamy zadanie, bo wszystkie jego operacje zosta³y wykonane
					break;
				}
			}

			if (nrZAD != zadania.size()-1)
				nrZAD++;
			else{
				nrZAD=0;
				maszyna->uszeregowanie.push_back(op);		//wpychamy zapychacz
				//wybieramy najmniej zawalon¹ maszynê
				int a = czas_uszeregowania(generator,0);
				int b = czas_uszeregowania(generator,1);
				int c = czas_uszeregowania(generator,2);
				//cout << "A=" <<a<< endl;
				if(a<=b && a<=c)
					preferred = 0;
				else if(b<=a && b<=c)
					preferred = 1;
				else
					preferred = 2;
			}
		}
	}


	for (int i=0; i<3; i++)
		generator.czysc(*generator.maszyny[i]);
	
	for (int i=0; i<3; i++){
		cout << "NR " << i << " MASZYNA:" << endl<<"------"<<endl;
		for (int j=0; j<generator.maszyny[i]->uszeregowanie.size(); j++){
			cout << "OP = " << (generator.maszyny[i]->uszeregowanie[j]->numer)+1 
				 << "\t\tZAD = " << (generator.maszyny[i]->uszeregowanie[j]->nrZadania)+1 
				 << "\t\tCZAS = " << generator.maszyny[i]->uszeregowanie[j]->czas << endl;
	}}
	
}