#include "losowy.h"



void wybierz (int &preferred)			//funkcja wybiera inn� woln� maszyn�
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

int wybierz (int maszyna1, int maszyna2)	//funkcja wybiera jedyn� woln� maszyn�
{
	int result;
	if((0==maszyna1 && 1==maszyna2) || (1==maszyna1 && 0==maszyna2))
		result = 2;
	else if((2==maszyna1 && 1==maszyna2) || (1==maszyna1 && 2==maszyna2))
		result = 0;
	else
		result = 1;

	return result;
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
	int czas = 0;									//obecny kwant czasu
	int przestoj = 0;								//numer nast�pnego przestoju

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
		

		while(zadania.size() != 0)												//p�ki czego� nie wsadzisz i nie trzeba wybiera� znowu maszyny losuj zadania
		{
			maszyna = generator.maszyny[preferred];


			if( maszyna->rozpoczecie[przestoj] < czas)							//je�eli pierwszy niewykonany przest�j ju� si� zacz��
			{													
				czas += maszyna->dlugosc[przestoj];			//dodajemy ten przest�j oraz
				if(przestoj<maszyna->rozpoczecie.size()-1)		//przechodzimy na nast�pny przest�j je�eli jaki� zosta�
					++przestoj;
				czas += maszyna->uszeregowanie[maszyna->uszeregowanie.size()-1]->czas * 0.3;		//wyw�aszczanie
			}

			if(!zadania[zadanie]->operacje[0]->done && czas>=zadania[zadanie]->delay)	//wsad� pierwsz� je�eli min�� czas gotowo�ci
				//generator.czyWejdzie(*maszyna, *zadania[zadanie]->operacje[0],czas))	
			{
				czas+=zadania[zadanie]->operacje[0]->czas;							//dodajemy czas operacji do bierz�cego
				maszyna->uszeregowanie.push_back(zadania[zadanie]->operacje[0]);	//wtykamy operacj� do uszeregowania
				zadania[zadanie]->operacje[0]->begin = czas;						//uk�adamy czas rozpocz�cia
				zadania[zadanie]->operacje[0]->maszyna = maszyna;					//ustawiamy gdzie jest dana operacja
				zadania[zadanie]->operacje[0]->done = true;							//okre�lamy operacj� jako wykonan�
				break;															//wychodzimy z p�tli, szukamy najmniej zawalonej maszyny
			}

			else if( !(zadania[zadanie]->operacje[1]->done))					//druga 			//je�eli drugia operacja jeszcze nie zosta�a rozpocz�ta 
																									//a pierwsza zako�czy�a si� przed chwil� obecn�
			{
				if(zadania[zadanie]->operacje[0]->maszyna == maszyna)								//je�eli maszyna jest ta sama co pierwszego zadania
				{																					//to j� zmieniamy na inn�
					wybierz(preferred);
					maszyna = generator.maszyny[preferred];
				}
				if(generator.czyMozna(*zadania[zadanie]->operacje[1],czas))
				{
					czas+=zadania[zadanie]->operacje[1]->czas;
					zadania[zadanie]->operacje[1]->begin = czas;
					zadania[zadanie]->operacje[1]->maszyna = maszyna;
					zadania[zadanie]->operacje[1]->done = true;
					maszyna->uszeregowanie.push_back(zadania[zadanie]->operacje[1]);
				
					break;
				}
			}
			else if((zadania[zadanie]->operacje[1]->done))			//sprawdzenie czy 2 operacja zosta�a wykonana
			{
				if(!zadania[zadanie]->operacje[2]->done)				//trzecia operacja	
				{
					if(zadania[zadanie]->operacje[0]->maszyna == maszyna ||			//je�eli operacja le�y na maszynie na kt�rej by�a wykonana poprzednia op
					zadania[zadanie]->operacje[1]->maszyna == maszyna)
					{
						preferred = wybierz(zadania[zadanie]->operacje[0]->maszyna->numer, zadania[zadanie]->operacje[1]->maszyna->numer);
						maszyna = generator.maszyny[preferred];						//szukamy innej maszyny
					}
					if(generator.czyMozna(*zadania[zadanie]->operacje[2],czas))
					{
						czas+=zadania[zadanie]->operacje[2]->czas;
						zadania[zadanie]->operacje[2]->begin = czas;
						zadania[zadanie]->operacje[2]->maszyna = maszyna;
						zadania[zadanie]->operacje[2]->done = true;
						bool flaga = zadania[0]->operacje[2]->done;
						maszyna->uszeregowanie.push_back(zadania[zadanie]->operacje[2]);

						tmp = zadania[zadanie];					//wymieniamy z ostatnim zadaniem w wektorze do usuwania
						zadania[zadanie] = zadania[zadania.size()-1];
						zadania[zadania.size()-1] = tmp;
						zadania.pop_back();				//usuwamy zadanie, bo wszystkie jego operacje zosta�y wykonane
						break;
					}
				}
			}
			if(zadanie>0)							//je�eli nie dojechali�my do pocz�tku wektora zada�
				zadanie--;
			else									// a je�eli tak to losujemy now� maszyn�
			{
				zadanie = zadania.size()-1;

				maszyna->uszeregowanie.push_back(op);		//wpychamy zapychacz
				czas+=1;
				
				wybierz(preferred);
			}
		}

		
	}

	
	int dlugosc = 0, dlugoscRealna = 0;	//do obliczania w�a�ciwej d�ugo�ci uszeergowania
	for (int i=0; i<3; i++)
	{
		generator.czysc(*generator.maszyny[i]);			//usuwanie �mieci z ko�ca uszeregowania
		generator.zlacz(generator.maszyny[i]->uszeregowanie);
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
