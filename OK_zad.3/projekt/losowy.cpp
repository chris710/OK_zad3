#include "losowy.h"




void wybierz (int &preferred)			//funkcja wybiera inn¹ woln¹ maszynê
{
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



int optymalnadlugosc(Generator generator){											// sprawdzamy czy jakis przestoj zostal niewykrozystany
	int x=generator.dlugoscInstancji;												// podstawiamy pod x wartosc dlugosci instancji
	for (int i=0;i<3;i++)															// dla 3 maszyn
	{	
		int licznik=0;
		int ostatni=generator.maszyny[i]->uszeregowanie.size()-1;
		int dlugosc=generator.maszyny[i]->uszeregowanie[ostatni]->begin + generator.maszyny[i]->uszeregowanie[ostatni]->czas;
		for(int j=0; j<generator.maszyny[i]->nPrzestojow; j++)								// nastepnie sprawdzamy liczbe niewykorzystanych przestojow 
			if (generator.maszyny[i]->rozpoczecie[j] >= dlugosc)
				licznik++;
		if (licznik>0)
			for(int k=0;k<licznik;k++)			//jesli tak to odejmujemy czas niewykrozystanych przestojow
				x-=generator.maszyny[i]->dlugosc[generator.maszyny[i]->nPrzestojow-1-k];	// od dlugosci instancji
	}
	return (x/3);																	// wynik juz tu dzielimy na 3 (liczba maszyn)
}



void algorytmLosowy(const Generator& generator, int tablica[])
{
	vector<Zadanie*> zadania = generator.zadania;	//tymczasowa tablica do usuwania zadañ
	Zadanie* tmp;									//wskaŸnik do zamieniania miejscami w wektorze
	Maszyna* maszyna;								//wskaŸnik na preferowan¹ maszynê

	
	ofstream plik("plik.txt");

	int zadanie = zadania.size()-1;					//zadanie do wykonania
	int preferred;									//preferowana maszyna
	int czas[3] = {0,0,0};							//obecny kwant czasu na danej maszynie
	int przestoj[3] = {0,0,0};								//numer nastêpnego przestoju
	bool koniec_przestojow[3] = {false, false, false};

	while (zadania.size() != 0)
	{
		zadanie = zadania.size()-1;					//przegl¹damy wektor od koñca

		//wybieramy najmniej zawalon¹ maszynê
		int a = czas[0];
		int b = czas[1];
		int c = czas[2];

		if(a<=b && a<=c)
			preferred = 0;
		else if(b<=a && b<=c)
			preferred = 1;
		else
			preferred = 2;
		

		while(zadania.size() != 0)												//póki czegoœ nie wsadzisz i nie trzeba wybieraæ znowu maszyny losuj zadania
		{
			maszyna = generator.maszyny[preferred];


			if( maszyna->rozpoczecie[przestoj[preferred]] == czas[preferred] && !koniec_przestojow[preferred])							//je¿eli pierwszy niewykonany przestój ju¿ siê zacz¹³
			{													
				czas[preferred] += maszyna->dlugosc[przestoj[preferred]];			//dodajemy ten przestój oraz
				if(przestoj[preferred] < maszyna->rozpoczecie.size()-1)		//przechodzimy na nastêpny przestój je¿eli jakiœ zosta³
					++przestoj[preferred];
				else
					koniec_przestojow[preferred]=true;
			}




			if ( (!zadania[zadanie]->operacje[0]->done) && (czas[preferred]>=zadania[zadanie]->delay))	//wsadŸ pierwsz¹ je¿eli min¹³ czas gotowoœci
				//generator.czyWejdzie(*maszyna, *zadania[zadanie]->operacje[0],czas))	
				{	
					if( maszyna->rozpoczecie[przestoj[preferred]] < (czas[preferred]+zadania[zadanie]->operacje[0]->czas) && !koniec_przestojow[preferred])							//je¿eli pierwszy niewykonany przestój ju¿ siê zacz¹³
					{													
						czas[preferred] += maszyna->dlugosc[przestoj[preferred]];			//dodajemy ten przestój oraz
						if(przestoj[preferred] < maszyna->rozpoczecie.size()-1)		//przechodzimy na nastêpny przestój je¿eli jakiœ zosta³
							++przestoj[preferred];
						else
							koniec_przestojow[preferred]=true;
						czas[preferred] += zadania[zadanie]->operacje[0]->czas * 0.3;		//wyw³aszczanie
					}
				maszyna->uszeregowanie.push_back(zadania[zadanie]->operacje[0]);	//wtykamy operacjê do uszeregowania
				zadania[zadanie]->operacje[0]->begin = czas[preferred];						//uk³adamy czas rozpoczêcia
				czas[preferred] += zadania[zadanie]->operacje[0]->czas;							//dodajemy czas operacji do bierz¹cego
				zadania[zadanie]->operacje[0]->maszyna = maszyna;					//ustawiamy gdzie jest dana operacja
				zadania[zadanie]->operacje[0]->done = true;							//okreœlamy operacjê jako wykonan¹
				break;															//wychodzimy z pêtli, szukamy najmniej zawalonej maszyny
			}

			else if( !(zadania[zadanie]->operacje[1]->done) && (zadania[zadanie]->operacje[0]->done))//druga 			
													//je¿eli drugia operacja jeszcze nie zosta³a rozpoczêta a pierwsza zakoñczy³a siê przed chwil¹ obecn¹
			{
				if(zadania[zadanie]->operacje[0]->maszyna == maszyna)								//je¿eli maszyna jest ta sama co pierwszego zadania
				{																					//to j¹ zmieniamy na inn¹
					wybierz(preferred);
					maszyna = generator.maszyny[preferred];
				}
				if(generator.czyMozna(*zadania[zadanie]->operacje[1],czas[preferred]))
				{
					if( !koniec_przestojow[preferred] && maszyna->rozpoczecie[przestoj[preferred]] < (czas[preferred]+zadania[zadanie]->operacje[1]->czas))							//je¿eli pierwszy niewykonany przestój ju¿ siê zacz¹³
					{													
						czas[preferred] += maszyna->dlugosc[przestoj[preferred]];			//dodajemy ten przestój oraz
						if(przestoj[preferred] < maszyna->rozpoczecie.size()-1)		//przechodzimy na nastêpny przestój je¿eli jakiœ zosta³
							++przestoj[preferred];
						else
							koniec_przestojow[preferred]=true;
						czas[preferred] += zadania[zadanie]->operacje[1]->czas * 0.3;		//wyw³aszczanie
					}
					zadania[zadanie]->operacje[1]->begin = czas[preferred];
					czas[preferred] += zadania[zadanie]->operacje[1]->czas;
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
						preferred = wybierz(zadania[zadanie]->operacje[0]->maszyna->numer, 
								zadania[zadanie]->operacje[1]->maszyna->numer);		//POPRAW
						maszyna = generator.maszyny[preferred];						//szukamy innej maszyny
					}
					if(generator.czyMozna(*zadania[zadanie]->operacje[2],czas[preferred]))
					{

					if(!koniec_przestojow[preferred] && maszyna->rozpoczecie[przestoj[preferred]] < (czas[preferred]+zadania[zadanie]->operacje[2]->czas))							//je¿eli pierwszy niewykonany przestój ju¿ siê zacz¹³
					{													
						czas[preferred] += maszyna->dlugosc[przestoj[preferred]];			//dodajemy ten przestój oraz
						if(przestoj[preferred] < maszyna->rozpoczecie.size()-1)		//przechodzimy na nastêpny przestój je¿eli jakiœ zosta³
							++przestoj[preferred];
						else
							koniec_przestojow[preferred]=true;
						czas[preferred] += zadania[zadanie]->operacje[2]->czas * 0.3;		//wyw³aszczanie
					}
						//cout<<"pyk"<<endl;
						zadania[zadanie]->operacje[2]->begin = czas[preferred];
						czas[preferred] += zadania[zadanie]->operacje[2]->czas;						
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
				//wpychanie zapychacza
				if(maszyna->uszeregowanie.size()>0)				//je¿eli uszeregowanie zawiera wiêcej ni¿ jedn¹ operacjê
				{
					if(maszyna->uszeregowanie[maszyna->uszeregowanie.size()-1]->numer>3)	//i jest to zapychacz
						maszyna->uszeregowanie[maszyna->uszeregowanie.size()-1]->czas += 1;	//to zwiêksz jego czas o jeden			
					else{
						Operacja  *op = new Operacja(1,98,NULL,98);		//deklaracja zapychacza
						op->begin=czas[preferred];
						maszyna->uszeregowanie.push_back(op);	
					}
				}
				else{
					Operacja  *op = new Operacja(1,98,NULL,98);		//deklaracja zapychacza
					op->begin=czas[preferred];
					maszyna->uszeregowanie.push_back(op);		//albo dodaj jako now¹ operacjê nowy zapychacz
				}
				czas[preferred] += 1;				
				wybierz(preferred);
			}
	}}

	
	int dlugosc = 0, dlugoscRealna = 0;	//do obliczania w³aœciwej d³ugoœci uszeergowania
	for (int i=0; i<3; i++)
	{
		//generator.czysc(*generator.maszyny[i]);			//usuwanie œmieci z koñca uszeregowania
		//generator.zlacz(generator.maszyny[i]->uszeregowanie);
		
		//cout << "NR " << i << " MASZYNA:" << endl<<"------"<<endl;
		plik << "NR " << i << " MASZYNA:" << endl<<"------"<<endl;
		for (int j=0; j<generator.maszyny[i]->uszeregowanie.size(); j++)
		{
		//	cout << "OP = " << (generator.maszyny[i]->uszeregowanie[j]->numer)+1 
			//		<< "\t\tZAD = " << (generator.maszyny[i]->uszeregowanie[j]->nrZadania)+1 
				//	<< "\t\tCZAS = " << generator.maszyny[i]->uszeregowanie[j]->czas << endl<<endl;	
			plik << "OP = " << (generator.maszyny[i]->uszeregowanie[j]->numer)+1 
					<< "\t\tZAD = " << (generator.maszyny[i]->uszeregowanie[j]->nrZadania)+1 
					<< "\t\tCZAS = " << generator.maszyny[i]->uszeregowanie[j]->czas << endl<<endl;	
		}
		int ostatni=generator.maszyny[i]->uszeregowanie.size()-1;
		dlugosc = generator.maszyny[i]->uszeregowanie[ostatni]->begin + generator.maszyny[i]->uszeregowanie[ostatni]->czas;
		dlugoscRealna = (dlugoscRealna > dlugosc) ? dlugoscRealna : dlugosc;
	}

	int x=optymalnadlugosc(generator);
	plik<<"//////////////	ALGORYTM LOSOWY	///////////////////"<<endl;
	cout<<"Szacowana optymalna dlugosc uszeregowania "<< generator.dlugoscInstancji/3 <<endl;
	//plik<<"Szacowana optymalna dlugosc uszeregowania "<< generator.dlugoscInstancji/3 <<endl;
	cout<<"Obliczona optymalna dlugosc uszeregowania "<< x <<endl;
	//plik<<"Obliczona optymalna dlugosc uszeregowania "<< x <<endl;
	cout<<"Dlugosc rzeczywista generowana przez algorytm "<<dlugoscRealna<<endl;
	//plik<<"Dlugosc rzeczywista generowana przez algorytm "<<dlugoscRealna<<endl;
	cout<<"Procent: "<<(float)dlugoscRealna/(x)<<endl;
	//plik<<"Procent: "<<(float)dlugoscRealna/(x)<<endl;
	tablica[0]=x;
	tablica[1]=dlugoscRealna;

}




void algorytmLosowy2(const Generator& generator, int tablica[])
{
	vector<Zadanie*> zadania = generator.zadania;	//tymczasowa tablica do usuwania zadañ
	Zadanie* tmp;									//wskaŸnik do zamieniania miejscami w wektorze
	Maszyna* maszyna;								//wskaŸnik na preferowan¹ maszynê
	int ktore = 0;									//które operacje teraz dodajemy
	int ileDodanych = 0;							//liczba dodanych operacji

	
	ofstream plik("plik.txt");

	int zadanie = zadania.size()-1;					//zadanie do wykonania
	int preferred;									//preferowana maszyna
	int czas[3] = {0,0,0};							//obecny kwant czasu na danej maszynie
	int przestoj[3] = {0,0,0};								//numer nastêpnego przestoju
	bool koniec_przestojow[3] = {false, false, false};

	while (zadania.size() != 0)
	{
		zadanie = zadania.size()-1;					//przegl¹damy wektor od koñca

		//wybieramy najmniej zawalon¹ maszynê
		int a = czas[0];
		int b = czas[1];
		int c = czas[2];

		if(a<=b && a<=c)
			preferred = 0;
		else if(b<=a && b<=c)
			preferred = 1;
		else
			preferred = 2;
		

		while(zadania.size() != 0)												//póki czegoœ nie wsadzisz i nie trzeba wybieraæ znowu maszyny losuj zadania
		{
			maszyna = generator.maszyny[preferred];


			if( maszyna->rozpoczecie[przestoj[preferred]] == czas[preferred] && !koniec_przestojow[preferred])							//je¿eli pierwszy niewykonany przestój ju¿ siê zacz¹³
			{													
				czas[preferred] += maszyna->dlugosc[przestoj[preferred]];			//dodajemy ten przestój oraz
				if(przestoj[preferred] < maszyna->rozpoczecie.size()-1)		//przechodzimy na nastêpny przestój je¿eli jakiœ zosta³
					++przestoj[preferred];
				else
					koniec_przestojow[preferred]=true;
			}



			if(ktore == 0) {
				if ( (!zadania[zadanie]->operacje[0]->done) && (czas[preferred]>=zadania[zadanie]->delay))	//wsadŸ pierwsz¹ je¿eli min¹³ czas gotowoœci
					//generator.czyWejdzie(*maszyna, *zadania[zadanie]->operacje[0],czas))	
					{	
						if( maszyna->rozpoczecie[przestoj[preferred]] < (czas[preferred]+zadania[zadanie]->operacje[0]->czas) && !koniec_przestojow[preferred])							//je¿eli pierwszy niewykonany przestój ju¿ siê zacz¹³
						{													
							czas[preferred] += maszyna->dlugosc[przestoj[preferred]];			//dodajemy ten przestój oraz
							if(przestoj[preferred] < maszyna->rozpoczecie.size()-1)		//przechodzimy na nastêpny przestój je¿eli jakiœ zosta³
								++przestoj[preferred];
							else
								koniec_przestojow[preferred]=true;
							czas[preferred] += zadania[zadanie]->operacje[0]->czas * 0.3;		//wyw³aszczanie
						}
					maszyna->uszeregowanie.push_back(zadania[zadanie]->operacje[0]);	//wtykamy operacjê do uszeregowania
					ileDodanych++;		//zwiêkszamy licznik
					zadania[zadanie]->operacje[0]->begin = czas[preferred];						//uk³adamy czas rozpoczêcia
					czas[preferred] += zadania[zadanie]->operacje[0]->czas;							//dodajemy czas operacji do bierz¹cego
					zadania[zadanie]->operacje[0]->maszyna = maszyna;					//ustawiamy gdzie jest dana operacja
					zadania[zadanie]->operacje[0]->done = true;							//okreœlamy operacjê jako wykonan¹
					break;															//wychodzimy z pêtli, szukamy najmniej zawalonej maszyny
				}
			}

			else if(ktore == 1) {
				if( !(zadania[zadanie]->operacje[1]->done) && (zadania[zadanie]->operacje[0]->done))//druga 			
														//je¿eli drugia operacja jeszcze nie zosta³a rozpoczêta a pierwsza zakoñczy³a siê przed chwil¹ obecn¹
				{
					if(zadania[zadanie]->operacje[0]->maszyna == maszyna)								//je¿eli maszyna jest ta sama co pierwszego zadania
					{																					//to j¹ zmieniamy na inn¹
						wybierz(preferred);
						maszyna = generator.maszyny[preferred];
					}
					if(generator.czyMozna(*zadania[zadanie]->operacje[1],czas[preferred]))
					{
						if( !koniec_przestojow[preferred] && maszyna->rozpoczecie[przestoj[preferred]] < (czas[preferred]+zadania[zadanie]->operacje[1]->czas))							//je¿eli pierwszy niewykonany przestój ju¿ siê zacz¹³
						{													
							czas[preferred] += maszyna->dlugosc[przestoj[preferred]];			//dodajemy ten przestój oraz
							if(przestoj[preferred] < maszyna->rozpoczecie.size()-1)		//przechodzimy na nastêpny przestój je¿eli jakiœ zosta³
								++przestoj[preferred];
							else
								koniec_przestojow[preferred]=true;
							czas[preferred] += zadania[zadanie]->operacje[1]->czas * 0.3;		//wyw³aszczanie
						}
						zadania[zadanie]->operacje[1]->begin = czas[preferred];
						czas[preferred] += zadania[zadanie]->operacje[1]->czas;
						zadania[zadanie]->operacje[1]->maszyna = maszyna;
						zadania[zadanie]->operacje[1]->done = true;
						maszyna->uszeregowanie.push_back(zadania[zadanie]->operacje[1]);
						ileDodanych++;		//zwiêkszamy licznik
						break;
					}
				}
			}

			else if(ktore ==2) {
				if((zadania[zadanie]->operacje[1]->done))			//sprawdzenie czy 2 operacja zosta³a wykonana
				{
					if(!zadania[zadanie]->operacje[2]->done)				//trzecia operacja	
					{
						if(zadania[zadanie]->operacje[0]->maszyna == maszyna ||			//je¿eli operacja le¿y na maszynie na której by³a wykonana poprzednia op
						zadania[zadanie]->operacje[1]->maszyna == maszyna)
						{
							preferred = wybierz(zadania[zadanie]->operacje[0]->maszyna->numer, 
									zadania[zadanie]->operacje[1]->maszyna->numer);		//POPRAW
							maszyna = generator.maszyny[preferred];						//szukamy innej maszyny
						}
						if(generator.czyMozna(*zadania[zadanie]->operacje[2],czas[preferred]))
						{

						if(!koniec_przestojow[preferred] && maszyna->rozpoczecie[przestoj[preferred]] < (czas[preferred]+zadania[zadanie]->operacje[2]->czas))							//je¿eli pierwszy niewykonany przestój ju¿ siê zacz¹³
						{													
							czas[preferred] += maszyna->dlugosc[przestoj[preferred]];			//dodajemy ten przestój oraz
							if(przestoj[preferred] < maszyna->rozpoczecie.size()-1)		//przechodzimy na nastêpny przestój je¿eli jakiœ zosta³
								++przestoj[preferred];
							else
								koniec_przestojow[preferred]=true;
							czas[preferred] += zadania[zadanie]->operacje[2]->czas * 0.3;		//wyw³aszczanie
						}
							//cout<<"pyk"<<endl;
							zadania[zadanie]->operacje[2]->begin = czas[preferred];
							czas[preferred] += zadania[zadanie]->operacje[2]->czas;						
							zadania[zadanie]->operacje[2]->maszyna = maszyna;
							zadania[zadanie]->operacje[2]->done = true;
							bool flaga = zadania[0]->operacje[2]->done;
							maszyna->uszeregowanie.push_back(zadania[zadanie]->operacje[2]);
							ileDodanych++;		//zwiêkszamy licznik

							tmp = zadania[zadanie];					//wymieniamy z ostatnim zadaniem w wektorze do usuwania
							zadania[zadanie] = zadania[zadania.size()-1];
							zadania[zadania.size()-1] = tmp;
							zadania.pop_back();				//usuwamy zadanie, bo wszystkie jego operacje zosta³y wykonane
							break;
						}
					}
				}
			}

			if(ileDodanych == generator.liczbaZadan) {//je¿eli skoñczyliœmy ju¿ wszystkie operacje danego numeru
				ileDodanych =0;		//zerujemy licznik
				ktore++;
			}

			if(zadanie>0)							//je¿eli nie dojechaliœmy do pocz¹tku wektora zadañ
				zadanie--;
			else									// a je¿eli tak to losujemy now¹ maszynê
			{
				zadanie = zadania.size()-1;
				//wpychanie zapychacza
				if(maszyna->uszeregowanie.size()>0)				//je¿eli uszeregowanie zawiera wiêcej ni¿ jedn¹ operacjê
				{
					if(maszyna->uszeregowanie[maszyna->uszeregowanie.size()-1]->numer>3)	//i jest to zapychacz
						maszyna->uszeregowanie[maszyna->uszeregowanie.size()-1]->czas += 1;	//to zwiêksz jego czas o jeden			
					else{
						Operacja  *op = new Operacja(1,98,NULL,98);		//deklaracja zapychacza
						op->begin=czas[preferred];
						maszyna->uszeregowanie.push_back(op);	
					}
				}
				else{
					Operacja  *op = new Operacja(1,98,NULL,98);		//deklaracja zapychacza
					op->begin=czas[preferred];
					maszyna->uszeregowanie.push_back(op);		//albo dodaj jako now¹ operacjê nowy zapychacz
				}
				czas[preferred] += 1;				
				wybierz(preferred);
			}
	}}

	
	int dlugosc = 0, dlugoscRealna = 0;	//do obliczania w³aœciwej d³ugoœci uszeergowania
	for (int i=0; i<3; i++)
	{
		//generator.czysc(*generator.maszyny[i]);			//usuwanie œmieci z koñca uszeregowania
		//generator.zlacz(generator.maszyny[i]->uszeregowanie);
		
		//cout << "NR " << i << " MASZYNA:" << endl<<"------"<<endl;
		plik << "NR " << i << " MASZYNA:" << endl<<"------"<<endl;
		for (int j=0; j<generator.maszyny[i]->uszeregowanie.size(); j++)
		{
		//	cout << "OP = " << (generator.maszyny[i]->uszeregowanie[j]->numer)+1 
			//		<< "\t\tZAD = " << (generator.maszyny[i]->uszeregowanie[j]->nrZadania)+1 
				//	<< "\t\tCZAS = " << generator.maszyny[i]->uszeregowanie[j]->czas << endl<<endl;	
			plik << "OP = " << (generator.maszyny[i]->uszeregowanie[j]->numer)+1 
					<< "\t\tZAD = " << (generator.maszyny[i]->uszeregowanie[j]->nrZadania)+1 
					<< "\t\tCZAS = " << generator.maszyny[i]->uszeregowanie[j]->czas << endl<<endl;	
		}
		int ostatni=generator.maszyny[i]->uszeregowanie.size()-1;
		dlugosc = generator.maszyny[i]->uszeregowanie[ostatni]->begin + generator.maszyny[i]->uszeregowanie[ostatni]->czas;
		dlugoscRealna = (dlugoscRealna > dlugosc) ? dlugoscRealna : dlugosc;
	}

	int x=optymalnadlugosc(generator);
	plik<<"//////////////	ALGORYTM LOSOWY	///////////////////"<<endl;
	cout<<"Szacowana optymalna dlugosc uszeregowania "<< generator.dlugoscInstancji/3 <<endl;
	//plik<<"Szacowana optymalna dlugosc uszeregowania "<< generator.dlugoscInstancji/3 <<endl;
	cout<<"Obliczona optymalna dlugosc uszeregowania "<< x <<endl;
	//plik<<"Obliczona optymalna dlugosc uszeregowania "<< x <<endl;
	cout<<"Dlugosc rzeczywista generowana przez algorytm "<<dlugoscRealna<<endl;
	//plik<<"Dlugosc rzeczywista generowana przez algorytm "<<dlugoscRealna<<endl;
	cout<<"Procent: "<<(float)dlugoscRealna/(x)<<endl;
	//plik<<"Procent: "<<(float)dlugoscRealna/(x)<<endl;
	tablica[0]=x;
	tablica[1]=dlugoscRealna;

}





void uszereguj(const Generator& generator, int tablica[]) {
	vector<Zadanie*> zadania = generator.zadania;									//tymczasowa tablica do usuwania zadañ
	
	generator.maszyny[0]->uszeregowanie.push_back(zadania[0]->operacje[0]);
		zadania[0]->operacje[0]->begin = 0;
	generator.maszyny[0]->uszeregowanie.push_back(zadania[1]->operacje[1]);
	zadania[1]->operacje[1]->begin = 5;
{ Operacja  *op = new Operacja(5,98,NULL,98);								//deklaracja zapychacza
  op->begin=10;
	generator.maszyny[0]->uszeregowanie.push_back(op);	}
	generator.maszyny[0]->uszeregowanie.push_back(zadania[2]->operacje[1]);
		zadania[2]->operacje[1]->begin = 15;
	generator.maszyny[0]->uszeregowanie.push_back(zadania[3]->operacje[2]);
		zadania[3]->operacje[2]->begin = 20;
{ Operacja  *op = new Operacja(5,98,NULL,98);								//deklaracja zapychacza
  op->begin=25;
	generator.maszyny[0]->uszeregowanie.push_back(op);	}
	generator.maszyny[0]->uszeregowanie.push_back(zadania[4]->operacje[2]);
		zadania[4]->operacje[2]->begin = 30;

	generator.maszyny[1]->uszeregowanie.push_back(zadania[1]->operacje[0]);
		zadania[1]->operacje[0]->begin = 0;
	generator.maszyny[1]->uszeregowanie.push_back(zadania[4]->operacje[1]);
		zadania[4]->operacje[1]->begin = 5;
	generator.maszyny[1]->uszeregowanie.push_back(zadania[0]->operacje[1]);
		zadania[0]->operacje[1]->begin = 10;
	generator.maszyny[1]->uszeregowanie.push_back(zadania[3]->operacje[1]);
		zadania[3]->operacje[1]->begin = 15;
	generator.maszyny[1]->uszeregowanie.push_back(zadania[2]->operacje[2]);
		zadania[2]->operacje[2]->begin = 20;

	generator.maszyny[2]->uszeregowanie.push_back(zadania[4]->operacje[0]);
		zadania[4]->operacje[0]->begin = 0;
	generator.maszyny[2]->uszeregowanie.push_back(zadania[3]->operacje[0]);
		zadania[3]->operacje[0]->begin = 5;
	generator.maszyny[2]->uszeregowanie.push_back(zadania[2]->operacje[0]);
		zadania[2]->operacje[0]->begin = 10;
	generator.maszyny[2]->uszeregowanie.push_back(zadania[0]->operacje[2]);
		zadania[0]->operacje[2]->begin = 15;
{ Operacja  *op = new Operacja(7,98,NULL,98);								//deklaracja zapychacza
  op->begin=20;
	generator.maszyny[2]->uszeregowanie.push_back(op);	}
	generator.maszyny[2]->uszeregowanie.push_back(zadania[1]->operacje[2]);
		zadania[1]->operacje[2]->begin = 27;

	tablica[0]=37;
	tablica[1]=25;


}