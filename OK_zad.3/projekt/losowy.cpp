#include "losowy.h"



void wybierz (int &preferred)
{
	/*if((0==preferred && c<=b) || (1==preferred && c<=a))
		preferred = 2;
	else if((1==preferred && a<=c) || (2==preferred && a<=b))
		preferred = 0;
	else
		preferred = 1;*/
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



void algorytmLosowy(const Generator& generator)
{
	vector<Zadanie*> zadania = generator.zadania;	//tymczasowa tablica do usuwania zada�
	Zadanie* tmp;									//wska�nik do zamieniania miejscami w wektorze
	Maszyna* maszyna;								//wska�nik na preferowan� maszyn�
	Operacja * op = new Operacja(1,98,NULL,98);		//deklaracja zapychacza
	
	ofstream plik("plik.txt");

	int zadanie = zadania.size()-1;					//zadanie do wykonania
	int preferred;									//preferowana maszyna

	while (zadania.size() != 0)
	{
		zadanie = zadania.size()-1;					//przegl�damy wektor od ko�ca

		//wybieramy najmniej zawalon� maszyn�
		int a = generator.dlugosc(*generator.maszyny[0]);
		int b = generator.dlugosc(*generator.maszyny[1]);
		int c = generator.dlugosc(*generator.maszyny[2]);

		if(a<=b && a<=c)
			preferred = 0;
		else if(b<=a && b<=c)
			preferred = 1;
		else
			preferred = 2;
		

		while(true)												//p�ki czego� nie wsadzisz i nie trzeba wybiera� znowu maszyny losuj zadania
		{
			maszyna = generator.maszyny[preferred];

			//zadanie = random(0,zadania.size());		//losowanie zadania do wykonania
			tmp = zadania[zadanie];					//wymieniamy z ostatnim zadaniem w wektorze (do ewentualnego usuwania)
			zadania[zadanie] = zadania[zadania.size()-1];
			zadania[zadania.size()-1] = tmp;

			/*if(zadania[zadanie]->operacje[2]->done)
			{
				zadania.pop_back();				//usuwamy zadanie, bo wszystkie jego operacje zosta�y wykonane
				break;
			}*/

			//std::cout<<(!zadania[zadanie]->operacje[0]->done)<<" "<<(!zadania[zadanie]->operacje[1]->done && generator.czyMozna(*zadania[zadanie]->operacje[1],*generator.maszyny[preferred]))<<" "<<(!zadania[zadanie]->operacje[2]->done && generator.czyMozna(*zadania[zadanie]->operacje[2],*generator.maszyny[preferred]))<<std::endl;
			
			if(!zadania[zadanie]->operacje[0]->done)		//wsad� pierwsze je�eli jeszcze tego nie zrobi�e�
			{
				maszyna->uszeregowanie.push_back(zadania[zadanie]->operacje[0]);					//wtykamy operacj� do uszeregowania
				zadania[zadanie]->operacje[0]->maszyna = maszyna;									//ustawiamy gdzie jest dana operacja
				zadania[zadanie]->operacje[0]->done = true;											//okre�lamy operacj� jako wykonan�
				break;															//wychodzimy z p�tli, szukamy najmniej zawalonej maszyny
			}

			else if( !(zadania[zadanie]->operacje[1]->done) && 
				generator.czyMozna(*zadania[zadanie]->operacje[1],*generator.maszyny[preferred]))	//drugie	
			{
				if(zadania[zadanie]->operacje[0]->maszyna == maszyna)
				{
					wybierz(preferred);
				}
				maszyna->uszeregowanie.push_back(zadania[zadanie]->operacje[1]);
				zadania[zadanie]->operacje[1]->maszyna = maszyna;
				zadania[zadanie]->operacje[1]->done = true;
				break;
			}
			else if((zadania[zadanie]->operacje[1]->done))			//sprawdzenie czy 2 operacja zosta�a wykonana
			{
				if(//!zadania[zadanie]->operacje[2]->done && 
					generator.czyMozna(*zadania[zadanie]->operacje[2],*maszyna))	//trzecie	
				{
					if(zadania[zadanie]->operacje[0]->maszyna == maszyna && 
					zadania[zadanie]->operacje[1]->maszyna == maszyna)
					{

					}

					maszyna->uszeregowanie.push_back(zadania[zadanie]->operacje[2]);
					zadania[zadanie]->operacje[2]->maszyna = maszyna;
					zadania[zadanie]->operacje[2]->done = true;
					zadania.pop_back();				//usuwamy zadanie, bo wszystkie jego operacje zosta�y wykonane
					break;
				}
			}
			if(zadanie>0)							//je�eli nie dojechali�my do pocz�tku wektora zada�
				zadanie--;
			else									// a je�eli tak to losujemy now� maszyn�
			{
				zadanie = zadania.size()-1;

				maszyna->uszeregowanie.push_back(op);		//wpychamy zapychacz
				
				wybierz(preferred);
			}
		}

		
	}

	//usuwanie �mieci z ko�ca uszeregowania
	for (int i=0; i<3; i++)
	{
		generator.czysc(*generator.maszyny[i]);
	}


	int dlugosc = 0, dlugoscRealna = 0;	//do obliczania w�a�ciwej d�ugo�ci uszeergowania
	for (int i=0; i<3; i++)
	{
		cout << "NR " << i << " MASZYNA:" << endl<<"------"<<endl;
		plik << "NR " << i << " MASZYNA:" << endl<<"------"<<endl;
		for (int j=0; j<generator.maszyny[i]->uszeregowanie.size(); j++)
		{
			cout << "OP = " << (generator.maszyny[i]->uszeregowanie[j]->numer)+1 
					<< "\t\tZAD = " << (generator.maszyny[i]->uszeregowanie[j]->nrZadania)+1 
					<< "\t\tCZAS = " << generator.maszyny[i]->uszeregowanie[j]->czas << endl<<endl;	
			plik << "OP = " << (generator.maszyny[i]->uszeregowanie[j]->numer)+1 
					<< "\t\tZAD = " << (generator.maszyny[i]->uszeregowanie[j]->nrZadania)+1 
					<< "\t\tCZAS = " << generator.maszyny[i]->uszeregowanie[j]->czas << endl<<endl;	
		}
		dlugosc = generator.dlugosc(*generator.maszyny[i]);
		dlugoscRealna = (dlugoscRealna > dlugosc) ? dlugoscRealna : dlugosc;
	}
	cout<<"Szacowana optymalna dlugosc uszeregowania "<<generator.dlugoscInstancji/3<<endl;
	plik<<"Szacowana optymalna dlugosc uszeregowania "<<generator.dlugoscInstancji/3<<endl;
	cout<<"Dlugosc rzeczywista generowana przez algorytm "<<dlugoscRealna<<endl;
	plik<<"Dlugosc rzeczywista generowana przez algorytm "<<dlugoscRealna<<endl;
	cout<<"Procent: "<<(float)dlugoscRealna/(generator.dlugoscInstancji/3)<<endl;
	plik<<"Procent: "<<(float)dlugoscRealna/(generator.dlugoscInstancji/3)<<endl;
}
