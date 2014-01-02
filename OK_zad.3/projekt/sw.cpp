#include "sw.h"

int ktora_maszyna(const Generator& generator)
{
	int dlugosc = 0;					//d�ugo�� uszeregowania konkretnej masznyny
	int dlugoscRealna = 0;				//najwi�ksza znaleziona d�ugo��
	int nr_maszyny;						//zwracany numer najbardziej zawalonej maszyny

	for (int i=0; i<3; i++)				//dla ka�dej maszyny sprawdzamy d�ugo�� uszeregowania
	{									//i szukamy najwi�ksz� z nich
		dlugosc = czas_uszeregowania(generator.maszyny[i]->uszeregowanie);
		if (dlugoscRealna < dlugosc){
			nr_maszyny=i;
			dlugoscRealna = dlugosc;
		}
	}
	return nr_maszyny;					//zwracamy najbardziej zawalon� maszyn�
}

int wartosc_kary(const Maszyna & maszyna, int nr_przestoju) {
	int start, kara, i=0;
	start = maszyna.rozpoczecie[nr_przestoju];//czas rozpocz�cia szukanego przestoju

	while ( (maszyna.uszeregowanie[i]->begin + maszyna.uszeregowanie[i]->czas) < start){
		i++;							//szukamy operacji, kt�ra nachodzi na przest�j
		if (i==maszyna.uszeregowanie.size())
			return 0;
	}	
	kara = 0.3 * maszyna.uszeregowanie[i]->czas;		
	return kara;						//zwracamy 30% jej d�ugo�ci
}

int czas_do_przestoju(const Maszyna & maszyna, int nr_przestoju) {
	int start, czas, i=0;
	start = maszyna.rozpoczecie[nr_przestoju];
		while ( (maszyna.uszeregowanie[i]->begin + maszyna.uszeregowanie[i]->czas) < start){
			i++;						//szukamy operacji, kt�ra nachodzi na przest�j
		if (i==maszyna.uszeregowanie.size())
			return 0;
	}		
		czas = start - (maszyna.uszeregowanie[i-1]->begin + maszyna.uszeregowanie[i-1]->czas);
										//liczymy czas od zako�czenia operacji poprzedzaj�cej to przestoju
	return czas;						//zwracamy ten czas
}

int max_kara_od_przestoju(const Maszyna & maszyna) {
	int result;							//numer operacji do wywalenia
	int max = 0;						//najwi�ksza strata czasu
	int tmp;							//zmienna tymczasowa do obecnej straty czasu
	int nr_przestoju;					//przestoj, na kt�rym tracimy najwi�cej
	
	for(int i = 0; i<maszyna.nPrzestojow; ++i) {//szukamy numeru najgorszego w skutkach przestoju
		tmp = wartosc_kary(maszyna,i);
		if (tmp > max) {
			max = tmp;
			nr_przestoju = i;
		}
	}
	int i = 0;							//zerowanie i
	int start = maszyna.rozpoczecie[nr_przestoju];//czas rozpocz�cia szukanego przestoju
	while ( (maszyna.uszeregowanie[i]->begin + maszyna.uszeregowanie[i]->czas) < start){
		i++;							//szukamy operacji, kt�ra nachodzi na przest�j
		if (i==maszyna.uszeregowanie.size())
			cout << "blad";
			break;
	}
	result = i;							//ta operacja nam przeszkadza najbardziej
	return result;
}

int liczba_zapychaczy(vector<Operacja*> & uszeregowanie) {
	int licznik=0;
	for (int i=1; i<uszeregowanie.size(); i++)
		if (uszeregowanie[i]->numer==98)
			licznik++;
	return licznik;
}

int czas_zapychaczy(vector<Operacja*> & uszeregowanie){
	int suma=0;
	for (int i=1; i<uszeregowanie.size(); i++)
		if (uszeregowanie[i]->numer==98)
			suma += uszeregowanie[i]->czas;
	return suma;
}

int czas_uszeregowania(vector<Operacja*> & uszeregowanie) {
		int ostatni=uszeregowanie.size()-1;
		int dlugosc = uszeregowanie[ostatni]->begin + uszeregowanie[ostatni]->czas;
		return dlugosc;					//zwracamy czas zako�czenia ostatniej operacji (aka d�ugo�� uszeregowania na danej maszynie)
}

void zamiana(int zad_1,	int zad_2, Maszyna & maszyna, Generator& generator) {
	if(czy_mozna(zad_1,zad_2,maszyna.numer,generator)) {				//je�eli spe�nione s� warunki poprawno�ci
		Operacja* tmp = maszyna.uszeregowanie[zad_1];					//zamieniamy operacje ze sob� miejscami
		maszyna.uszeregowanie[zad_1] = maszyna.uszeregowanie[zad_2];
		maszyna.uszeregowanie[zad_2] = tmp;

		obliczenie_uszeregowania(maszyna);								//obliczamy czasy pozosta�ych operacji w uszeregowaniu
	}
	return;									//je�eli nie s� spe�nione to nic nie robimy
}

bool czy_mozna(int zad_1, int zad_2, int nr_maszyny, const Generator& generator) {
	return true;
}

void obliczenie_uszeregowania(Maszyna & maszyna) {
	int czas = 0;							//obecny kwant czasu
	int czas_przestoju;						//czas rozpocz�cia ka�dego kolejnego przestoju
	int nastepny_przestoj = 0;				//numer nast�pnego przestoju
	//for(vector<Operacja*>::iterator it = maszyna.uszeregowanie.begin(); it != maszyna.uszeregowanie.end(); it++) {
	for(int i = 1; i < maszyna.uszeregowanie.size(); ++i) {
		if(czas != (maszyna.uszeregowanie[i-1]->begin + maszyna.uszeregowanie[i-1]->czas)) {
															//je�eli czas si� nie zgadza
			//for(int j = 0; j < maszyna.nPrzestojow; ++j) {//przestoje
				czas_przestoju = maszyna.rozpoczecie[nastepny_przestoj];
				if ( czas > czas_przestoju ) {//&& czas < (czas_przestoju + maszyna.dlugosc[nastepny_przestoj]) ) {	
															//jeste�my obecnie na przestoju
					if ( czas != (maszyna.uszeregowanie[i-1]->begin + maszyna.uszeregowanie[i-1]->czas*0.3 + maszyna.dlugosc[nastepny_przestoj])) {
																			//jeste�my na przestoju i czas si� nie zgadza
						maszyna.uszeregowanie[i]->begin = czas + maszyna.uszeregowanie[i-1]->begin + maszyna.uszeregowanie[i-1]->czas*0.3 
							+ maszyna.dlugosc[nastepny_przestoj];			//ustawiamy czas rozpocz�cia operacji od pocz�tku bazuj�c na czasie
					}														//poprzedniej operacji
					nastepny_przestoj++;
					czas += maszyna.dlugosc[nastepny_przestoj] + 0.3*maszyna.uszeregowanie[i]->czas; //tylko 0.3 bo reszt� dodajemy p�niej
				}
				else						//czas si� zgadza
					maszyna.uszeregowanie[i]->begin = czas;					//tu to samo tylko nie dodajemy d�ugo�ci przestoju
		}
		czas += maszyna.uszeregowanie[i]->czas;								//przesuwamy kwant czasu
	}
}

bool rosnaco(Operacja *const a, Operacja *const b)
{
	int asuma=0, bsuma=0;
	asuma+=a->czas;
	bsuma+=b->czas;
    return asuma < bsuma;
}

void sortowanie(vector<Operacja*> & uszeregowanie, vector<Operacja*> & zadania) {
	for (int i=0; i<uszeregowanie.size(); i++)
		if (uszeregowanie[i]->numer < 3)
			zadania.push_back(uszeregowanie[i]);
	sort(zadania.begin(), zadania.end(), rosnaco);			//sortowanie vectora po czasach trwania operacji w uszeregowaniu
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////          GLOWNY ALGORYTM           ////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void wyzarzanie(const Generator& generator, int tablica[]){
	// VECTOR USZEREGOWAN 
	vector <Operacja*> zadania;
	Maszyna* maszyna;
	int granica=tablica[0] , optimum=tablica[1] , krok;	// ?
	krok = 0.02 * (granica - optimum);
/*
	for (int i=0; i<generator.liczbaZadan; ++i)																// wypisanie czasow gotowosci wsyzstkich zadan
		cout << "zadanie nr " << i << " jest gotowe o: " << generator.zadania[i]->delay << endl;
*/


	// jakas petla {
	int nr_maszyny = ktora_maszyna(generator);
	maszyna = generator.maszyny[nr_maszyny];
	cout << " Maszyna do poprawy to: " << nr_maszyny << endl;
	cout << " Liczba zapychaczy na niej to: " << liczba_zapychaczy(maszyna->uszeregowanie) << endl;
	cout << " CZAS zapychaczy na niej to: " << czas_zapychaczy(maszyna->uszeregowanie) << endl;
	cout << " Nr operacji DO POPRAWY w  uszeregowaniu to: " << max_kara_od_przestoju(*maszyna) << endl;

	sortowanie(maszyna->uszeregowanie, zadania);
	cout << " Pierwszy lement ma czas to: " << zadania[0]->czas << endl;

	/// zapychacze



	/// na ktore zamienic



	

	// granica -= krok;		 }	// koniec petli

	/// wybor najlepszego

}