#include "sw.h"

int ktora_maszyna(const Generator& generator)
{
	int dlugosc = 0, dlugoscRealna = 0, nr_maszyny;	//do obliczania w³aœciwej d³ugoœci uszeergowania
	for (int i=0; i<3; i++)
	{	
		
		dlugosc = czas_uszeregowania(generator.maszyny[i]->uszeregowanie);
		if (dlugoscRealna < dlugosc){
			nr_maszyny=i;
			dlugoscRealna = dlugosc;
		}
	}
	return nr_maszyny;
}

int wartosc_kary(const Maszyna & maszyna, int nr_przestoju){
	int start, kara, i=0;
	start = maszyna.rozpoczecie[nr_przestoju];
		while ( (maszyna.uszeregowanie[i]->begin + maszyna.uszeregowanie[i]->czas) < start)
			i++;
	kara = 0.3 * maszyna.uszeregowanie[i]->czas;
	return kara;
}

int czas_do_przestoju(const Maszyna & maszyna, int nr_przestoju){
	int start, czas, i=0;
	start = maszyna.rozpoczecie[nr_przestoju];
		while ( (maszyna.uszeregowanie[i]->begin + maszyna.uszeregowanie[i]->czas) < start)
			i++;
		czas = start - (maszyna.uszeregowanie[i-1]->begin + maszyna.uszeregowanie[i-1]->czas);

	return czas;
}

int liczba_zapychaczy(vector<Operacja*> & uszeregowanie){
	int licznik=0;
	for (int i=0; i<uszeregowanie.size(); i++)
		if (uszeregowanie[i]->numer==48)
			licznik++;
	return licznik;
}

int czas_uszeregowania(vector<Operacja*> & uszeregowanie){
		int ostatni=uszeregowanie.size()-1;
		int dlugosc = uszeregowanie[ostatni]->begin + uszeregowanie[ostatni]->czas;
		return dlugosc;
}


void sortowanie(vector<Operacja*> & uszeregowanie, vector<int*> & zadania){

}

void wyrzazanie(const Generator& generator){
	// VECTOR USZEREGOWAN ???
	Maszyna* maszyna;
	int temperatura, krok;	// ?

	maszyna = generator.maszyny[ktora_maszyna(generator)];
	cout << ktora_maszyna(generator);
	
	/// zapychacze


	/// na ktore zamienic

	/// wybor najlepszego

}