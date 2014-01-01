#include "sw.h"

int ktora_maszyna(const Generator& generator)
{
	int dlugosc = 0;					//d³ugoœæ uszeregowania konkretnej masznyny
	int dlugoscRealna = 0;				//najwiêksza znaleziona d³ugoœæ
	int nr_maszyny;						//zwracany numer najbardziej zawalonej maszyny

	for (int i=0; i<3; i++)				//dla ka¿dej maszyny sprawdzamy d³ugoœæ uszeregowania
	{									//i szukamy najwiêksz¹ z nich
		dlugosc = czas_uszeregowania(generator.maszyny[i]->uszeregowanie);
		if (dlugoscRealna < dlugosc){
			nr_maszyny=i;
			dlugoscRealna = dlugosc;
		}
	}
	return nr_maszyny;					//zwracamy najbardziej zawalon¹ maszynê
}

int wartosc_kary(const Maszyna & maszyna, int nr_przestoju) {
	int start, kara, i=0;
	start = maszyna.rozpoczecie[nr_przestoju];//czas rozpoczêcia szukanego przestoju

	while ( (maszyna.uszeregowanie[i]->begin + maszyna.uszeregowanie[i]->czas) < start)
		i++;							//szukamy operacji, która nachodzi na przestój
	kara = 0.3 * maszyna.uszeregowanie[i]->czas;		
	return kara;						//zwracamy 30% jej d³ugoœci
}

int czas_do_przestoju(const Maszyna & maszyna, int nr_przestoju) {
	int start, czas, i=0;
	start = maszyna.rozpoczecie[nr_przestoju];
		while ( (maszyna.uszeregowanie[i]->begin + maszyna.uszeregowanie[i]->czas) < start)
			i++;						//szukamy operacji, która nachodzi na przestój
		czas = start - (maszyna.uszeregowanie[i-1]->begin + maszyna.uszeregowanie[i-1]->czas);
										//liczymy czas od zakoñczenia operacji poprzedzaj¹cej to przestoju
	return czas;						//zwracamy ten czas
}

int max_kara_od_przestoju(const Maszyna & maszyna) {
	int result;							//numer operacji do wywalenia
	int max = 0;						//najwiêksza strata czasu
	int tmp;							//zmienna tymczasowa do obecnej straty czasu
	int nr_przestoju;					//przestoj, na którym tracimy najwiêcej
	
	for(int i = 0; i<maszyna.nPrzestojow; ++i) {//szukamy numeru najgorszego w skutkach przestoju
		tmp = wartosc_kary(maszyna,i);
		if (tmp > max) {
			max = tmp;
			nr_przestoju = i;
		}
	}
	int i = 0;							//zerowanie i
	int start = maszyna.rozpoczecie[nr_przestoju];//czas rozpoczêcia szukanego przestoju
	while ( (maszyna.uszeregowanie[i]->begin + maszyna.uszeregowanie[i]->czas) < start)
		i++;							//szukamy operacji, która nachodzi na przestój
	result = i;							//ta operacja nam przeszkadza najbardziej
	return result;
}

int liczba_zapychaczy(vector<Operacja*> & uszeregowanie) {
	int licznik=0;
	for (int i=0; i<uszeregowanie.size(); i++)
		if (uszeregowanie[i]->numer==48)
			licznik++;
	return licznik;
}

int czas_uszeregowania(vector<Operacja*> & uszeregowanie) {
		int ostatni=uszeregowanie.size()-1;
		int dlugosc = uszeregowanie[ostatni]->begin + uszeregowanie[ostatni]->czas;
		return dlugosc;					//zwracamy czas zakoñczenia ostatniej operacji (aka d³ugoœæ uszeregowania na danej maszynie)
}

void zamiana(int zad_1,	int zad_2, Maszyna & maszyna, Generator& generator) {
	if(czy_mozna(zad_1,zad_2,maszyna.numer,generator)) {				//je¿eli spe³nione s¹ warunki poprawnoœci
		Operacja* tmp = maszyna.uszeregowanie[zad_1];					//zamieniamy operacje ze sob¹ miejscami
		maszyna.uszeregowanie[zad_1] = maszyna.uszeregowanie[zad_2];
		maszyna.uszeregowanie[zad_2] = tmp;

		obliczenie_uszeregowania(maszyna);								//obliczamy czasy pozosta³ych operacji w uszeregowaniu
	}
	return;									//je¿eli nie s¹ spe³nione to nic nie robimy
}

bool czy_mozna(int zad_1, int zad_2, int nr_maszyny, const Generator& generator) {
	return true;
}

void obliczenie_uszeregowania(Maszyna & maszyna) {
	int czas = 0;							//obecny kwant czasu
	//for(vector<Operacja*>::iterator it = maszyna.uszeregowanie.begin(); it != maszyna.uszeregowanie.end(); it++) {
	for(int i = 1; i < maszyna.uszeregowanie.size(); ++i) {
		if(czas != (maszyna.uszeregowanie[i-1]->begin + maszyna.uszeregowanie[i]->begin)) { //je¿eli czas siê nie zgadza
			int czas_przestoju;				//czas rozpoczêcia ka¿dego kolejnego przestoju
			int nastepny_przestoj = 0;		////numer nastêpnego przestoju
			//for(int j = 0; j < maszyna.nPrzestojow; ++j) {									//przestoje
				czas_przestoju = maszyna.rozpoczecie[nastepny_przestoj];
				if ( czas > czas_przestoju && czas < (czas_przestoju + maszyna.dlugosc[nastepny_przestoj]) ) {
					if ( czas != (maszyna.uszeregowanie[i-1]->begin + maszyna.uszeregowanie[i]->begin*0.3 + maszyna.dlugosc[nastepny_przestoj]))
						break;
					nastepny_przestoj++;
				}
				else
					break;
		}
		else {
			czas += maszyna.uszeregowanie[i]->begin;
		}
	}
}

void sortowanie(vector<Operacja*> & uszeregowanie, vector<int*> & zadania) {

}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////          GLOWNY ALGORYTM           ////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

void wyrzazanie(const Generator& generator, int tablica[]){
	// VECTOR USZEREGOWAN ???
	Maszyna* maszyna;
	int granica=tablica[0] , optimum=tablica[1] , krok=10;	// ?

	// jakas petla {

	maszyna = generator.maszyny[ktora_maszyna(generator)];
	cout << " Maszyna do poprawy to: " << ktora_maszyna(generator) << endl;
	cout << granica << " " << optimum << endl;
		
	/// zapychacze


	/// na ktore zamienic

	/// wybor najlepszego

}