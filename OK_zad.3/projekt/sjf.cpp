#include "sjf.h"

void obliczanie_dlugosci(vector<int*> &dlugosci, vector<Zadanie*> zadania){
	for (int i=0; i<zadania.size();i++){
		int suma=0;
		for(int j=0; j<3; j++)
			suma+=zadania[i]->operacje[j]->czas;
		dlugosci.push_back(new int(suma));
	}
}

int czas_uszeregowania(Generator generator, int i){
	int suma=0;
	for (int j=0; j<generator.maszyny[i]->uszeregowanie.size(); j++)
				suma+= generator.maszyny[i]->uszeregowanie[j]->czas ;
	return suma;
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

bool czy_juz_gotowy(int gotowosc, vector<Operacja*> uszeregowanie){
	int x=0;
	for (int i=0; i<uszeregowanie.size();i++)
		x+=uszeregowanie[0]->czas;
	cout << "\n got=" <<gotowosc << "\t x=" << x<< endl;
	if(gotowosc<=x)
		return true;
	else
		return false;
}




void algorytmSJF(const Generator& generator)
{
	vector<Zadanie*> zadania = generator.zadania;			//tymczasowa tablica do usuwania zadañ
	int rozmiar=zadania.size();
	vector<int*> nr_zadania;
	vector<int*> dlugosci;						// do usuniecia
	obliczanie_dlugosci(dlugosci,zadania);		// do usuniecia
	cout << "=================" << endl ;
	for (int  i=0; i< dlugosci.size();i++)		// do usuniecia
		cout << "\t" << *dlugosci[i] << endl;			// do usuniecia
	cout << "=================" << endl ;
	Zadanie* tmp;											//wskaŸnik do zamieniania miejscami w wektorze
	Maszyna* maszyna;								//wskaŸnik na preferowan¹ maszynê
	Operacja * op = new Operacja(1,98,NULL,98);
	sort(zadania.begin(), zadania.end(), rosnaco);			//sortowanie tablicy po czasach trwania calego zadania
//	for (int  i=0; i< zadania.size();i++)						// do usuniecia		
//		cout << zadania[i]->operacje[0]->czas << endl;			// do usuniecia

	int nrZAD;												//zadanie do wykonania
	int preferred;		
									//preferowana maszyna
	nrZAD = -1;
	
	while (zadania.size() != 0)
	{
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
		
//////////////// tab.erase( tab.begin() + 2 );
		cout << "ROZMIAR ZADANIA=" << zadania.size()-1 << endl;
		if (nrZAD < (zadania.size()-1))
			nrZAD++;
		else
			nrZAD=0;
		//cout << "maszyna=" << preferred << endl;
		while(true)														//póki czegoœ nie wsadzisz i nie trzeba wybieraæ znowu maszyny losuj zadania
		{
			maszyna = generator.maszyny[preferred];
			
			if(zadania[nrZAD]->operacje[2]->done)
			{
				zadania.erase( zadania.begin()+nrZAD);				//usuwamy zadanie, bo wszystkie jego operacje zosta³y wykonane
				break;
			}


			if(!zadania[nrZAD]->operacje[0]->done  )
			//&& czy_juz_gotowy(zadania[nrZAD]->delay, generator.maszyny[preferred]->uszeregowanie))					//wsadŸ pierwsze je¿eli jeszcze tego nie zrobi³eœ
			{		
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[nrZAD]->operacje[0]);		//wtykamy operacjê do uszeregowania
				zadania[nrZAD]->operacje[0]->maszyna = generator.maszyny[preferred];					//ustawiamy gdzie jest dana operacja
				zadania[nrZAD]->operacje[0]->done = true;												//okreœlamy operacjê jako wykonan¹
				break;															//wychodzimy z pêtli, szukamy najmniej zawalonej maszyny
			}

			else if(!zadania[nrZAD]->operacje[1]->done && 
			generator.czyMozna(*zadania[nrZAD]->operacje[1],*generator.maszyny[preferred]) && 
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
					generator.czyMozna(*zadania[nrZAD]->operacje[2],*maszyna) && 
					zadania[nrZAD]->operacje[0]->maszyna != maszyna && 
					zadania[nrZAD]->operacje[1]->maszyna != maszyna)	//trzecie	
				{
					maszyna->uszeregowanie.push_back(zadania[nrZAD]->operacje[2]);
					zadania[nrZAD]->operacje[2]->maszyna = maszyna;
					zadania[nrZAD]->operacje[2]->done = true;
					zadania.pop_back();				//usuwamy zadanie, bo wszystkie jego operacje zosta³y wykonane
					break;
				}
			}

			if (nrZAD != zadania.size()-1)
				nrZAD++;
			else
				nrZAD=0;
				maszyna->uszeregowanie.push_back(op);		//wpychamy zapychacz
				if(0==preferred)
					preferred = rand()%2+1;
				else if(1==preferred)
				{
					preferred = rand()%2;
					if(preferred == 1)
						preferred = 2;
				}
				else 
					preferred = rand()%2;
		
		}
	
	}

	for (int i=0; i<3; i++){
		cout << "NR " << i << " MASZYNA:" << endl<<"------"<<endl;
		for (int j=0; j<generator.maszyny[i]->uszeregowanie.size(); j++){
			cout << "OP = " << (generator.maszyny[i]->uszeregowanie[j]->numer)+1 
				 << "\t\tZAD = " << (generator.maszyny[i]->uszeregowanie[j]->nrZadania)+1 
				 << "\t\tCZAS = " << generator.maszyny[i]->uszeregowanie[j]->czas << endl;
		}}
	
}