#include "sw.h"

int ktora_maszyna(const Generator& generator)
{
	int dlugosc = 0, dlugoscRealna = 0, nr_maszyny;	//do obliczania w³aœciwej d³ugoœci uszeergowania
	for (int i=0; i<3; i++)
	{	
		int ostatni=generator.maszyny[i]->uszeregowanie.size()-1;
		dlugosc = generator.maszyny[i]->uszeregowanie[ostatni]->begin + generator.maszyny[i]->uszeregowanie[ostatni]->czas;
		if (dlugoscRealna < dlugosc){
			nr_maszyny=i;
			dlugoscRealna = dlugosc;
		}
	}
	return nr_maszyny;
}

void wyrzazanie(const Generator& generator){
	// VECTOR USZEREGOWAN ???
	Maszyna* maszyna;
	int temperatura, krok;	// ?

	maszyna = generator.maszyny[ktora_maszyna(generator)];
	//cout << ktora_maszyna(generator);
	
	/// zapychacze


	/// na ktore zamienic

	/// wybor najlepszego

}