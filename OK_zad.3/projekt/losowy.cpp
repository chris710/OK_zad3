#include "losowy.h"



void wybierz (int &preferred)			//funkcja wybiera inn¹ woln¹ maszynê
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

int wybierz (int maszyna1, int maszyna2)	//funkcja wybiera jedyn¹ woln¹ maszynê
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
	vector<Zadanie*> zadania = generator.zadania;	//tymczasowa tablica do usuwania zadañ
	Zadanie* tmp;									//wskaŸnik do zamieniania miejscami w wektorze
	Maszyna* maszyna;								//wskaŸnik na preferowan¹ maszynê
	Operacja * op = new Operacja(1,98,NULL,98);		//deklaracja zapychacza
	
	ofstream plik("plik.txt");

	int zadanie = zadania.size()-1;					//zadanie do wykonania
	int preferred;									//preferowana maszyna
	int czas = 0;									//obecny kwant czasu
	int przestoj = 0;								//numer nastêpnego przestoju

	while (zadania.size() != 0)
	{
		zadanie = zadania.size()-1;					//przegl¹damy wektor od koñca

		//wybieramy najmniej zawalon¹ maszynê
		int a = generator.dlugosc(*generator.maszyny[0]);
		int b = generator.dlugosc(*generator.maszyny[1]);
		int c = generator.dlugosc(*generator.maszyny[2]);

		if(a<=b && a<=c)
			preferred = 0;
		else if(b<=a && b<=c)
			preferred = 1;
		else
			preferred = 2;
		

		while(zadania.size() != 0)												//póki czegoœ nie wsadzisz i nie trzeba wybieraæ znowu maszyny losuj zadania
		{
			maszyna = generator.maszyny[preferred];


			if( maszyna->rozpoczecie[przestoj] < czas)							//je¿eli pierwszy niewykonany przestój ju¿ siê zacz¹³
			{													
				czas += maszyna->dlugosc[przestoj];			//dodajemy ten przestój oraz
				if(przestoj<maszyna->rozpoczecie.size()-1)		//przechodzimy na nastêpny przestój je¿eli jakiœ zosta³
					++przestoj;
				czas += maszyna->uszeregowanie[maszyna->uszeregowanie.size()-1]->czas * 0.3;		//wyw³aszczanie
			}

			if(!zadania[zadanie]->operacje[0]->done && czas>=zadania[zadanie]->delay)	//wsadŸ pierwsz¹ je¿eli min¹³ czas gotowoœci
				//generator.czyWejdzie(*maszyna, *zadania[zadanie]->operacje[0],czas))	
			{
				czas+=zadania[zadanie]->operacje[0]->czas;							//dodajemy czas operacji do bierz¹cego
				maszyna->uszeregowanie.push_back(zadania[zadanie]->operacje[0]);	//wtykamy operacjê do uszeregowania
				zadania[zadanie]->operacje[0]->begin = czas;						//uk³adamy czas rozpoczêcia
				zadania[zadanie]->operacje[0]->maszyna = maszyna;					//ustawiamy gdzie jest dana operacja
				zadania[zadanie]->operacje[0]->done = true;							//okreœlamy operacjê jako wykonan¹
				break;															//wychodzimy z pêtli, szukamy najmniej zawalonej maszyny
			}

			else if( !(zadania[zadanie]->operacje[1]->done))					//druga 			//je¿eli drugia operacja jeszcze nie zosta³a rozpoczêta 
																									//a pierwsza zakoñczy³a siê przed chwil¹ obecn¹
			{
				if(zadania[zadanie]->operacje[0]->maszyna == maszyna)								//je¿eli maszyna jest ta sama co pierwszego zadania
				{																					//to j¹ zmieniamy na inn¹
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
			else if((zadania[zadanie]->operacje[1]->done))			//sprawdzenie czy 2 operacja zosta³a wykonana
			{
				if(!zadania[zadanie]->operacje[2]->done)				//trzecia operacja	
				{
					if(zadania[zadanie]->operacje[0]->maszyna == maszyna ||			//je¿eli operacja le¿y na maszynie na której by³a wykonana poprzednia op
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
						zadania.pop_back();				//usuwamy zadanie, bo wszystkie jego operacje zosta³y wykonane
						break;
					}
				}
			}
			if(zadanie>0)							//je¿eli nie dojechaliœmy do pocz¹tku wektora zadañ
				zadanie--;
			else									// a je¿eli tak to losujemy now¹ maszynê
			{
				zadanie = zadania.size()-1;

				maszyna->uszeregowanie.push_back(op);		//wpychamy zapychacz
				czas+=1;
				
				wybierz(preferred);
			}
		}

		
	}

	
	int dlugosc = 0, dlugoscRealna = 0;	//do obliczania w³aœciwej d³ugoœci uszeergowania
	for (int i=0; i<3; i++)
	{
		generator.czysc(*generator.maszyny[i]);			//usuwanie œmieci z koñca uszeregowania
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
