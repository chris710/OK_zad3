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
	int start, kara=0, i=0;
	start = maszyna.rozpoczecie[nr_przestoju];//czas rozpocz�cia szukanego przestoju

	while ( (maszyna.uszeregowanie[i]->begin + maszyna.uszeregowanie[i]->czas) < start){
		i++;							//szukamy operacji, kt�ra nachodzi na przest�j
		if (i==maszyna.uszeregowanie.size())
			return 0;
	}
	if (maszyna.uszeregowanie[i]->numer != 98)
		kara = 0.3 * maszyna.uszeregowanie[i]->czas;		
	return kara;						//zwracamy 30% jej d�ugo�ci
}

void operacja_z_max_kara(const Maszyna & maszyna, int przestoj[]) {
	int result;							//numer operacji do wywalenia
	int max = -1;						//najwi�ksza strata czasu
	int tmp;							//zmienna tymczasowa do obecnej straty czasu
	int nr_przestoju;					//przestoj, na kt�rym tracimy najwi�cej
	
	for(int i = 0; i<maszyna.nPrzestojow; i++) {//szukamy numeru najgorszego w skutkach przestoju
		tmp = wartosc_kary(maszyna,i);
		if (tmp > max) {
			max = tmp;
			nr_przestoju = i;
		}
	}
	if (max > 0){
		przestoj[1] = max;
		przestoj[2] = nr_przestoju;
	}
	int i = 0;							//zerowanie i
	int start = maszyna.rozpoczecie[nr_przestoju];//czas rozpocz�cia szukanego przestoju
	while ( (maszyna.uszeregowanie[i]->begin + maszyna.uszeregowanie[i]->czas) < start){
		i++;							//szukamy operacji, kt�ra nachodzi na przest�j
		if (i==maszyna.uszeregowanie.size()){
			cout << "blad";
			break;
		}
	}
	przestoj[0] = i;							//ta operacja nam przeszkadza najbardziej

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


int liczba_zapychaczy(vector<Operacja*> & uszeregowanie) {
	int licznik=0;
	for (int i=1; i<uszeregowanie.size(); i++)
		if (uszeregowanie[i]->numer==98)
			licznik++;
	return licznik;
}

int max_zapychacz(vector<Operacja*> & uszeregowanie) {
	int max=0;
	for (int i=1; i<uszeregowanie.size(); i++)
		if (uszeregowanie[i]->numer==98)
			if ( uszeregowanie[i]->czas > max)
				max = uszeregowanie[i]->czas;
	return max;
}

int czas_zapychaczy(vector<Operacja*> & uszeregowanie){
	int suma=0;
	for (int i=1; i<uszeregowanie.size(); i++)
		if (uszeregowanie[i]->numer==98)
			suma += uszeregowanie[i]->czas;
	return suma;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int czas_uszeregowania(vector<Operacja*> & uszeregowanie) {
		int ostatni=uszeregowanie.size()-1;
		int dlugosc = uszeregowanie[ostatni]->begin + uszeregowanie[ostatni]->czas;
		return dlugosc;					//zwracamy czas zako�czenia ostatniej operacji (aka d�ugo�� uszeregowania na danej maszynie)
}

void zamiana( Operacja & aaa, Operacja & bbb, Maszyna & maszyna) {
	if(mozna_zamienic(aaa, bbb)) {				//je�eli spe�nione s� warunki poprawno�ci
		Operacja tmp = aaa;					//zamieniamy operacje ze sob� miejscami
		aaa = bbb;
		bbb = tmp;

		obliczenie_uszeregowania(maszyna);								//obliczamy czasy pozosta�ych operacji w uszeregowaniu
	}
																		//je�eli nie s� spe�nione to nic nie robimy
}

bool mozna_zamienic(const Operacja & aaa, const Operacja & bbb) {
	bool w_pierwsza = true;
	if(aaa.numer == 0){
		if (bbb.parent->delay > aaa.begin)
			w_pierwsza = false;
	}
	else{
		Operacja *poprzednia = bbb.parent->operacje[bbb.numer-1];
		if ( (poprzednia->begin + poprzednia->czas) > aaa.begin )
			w_pierwsza = false;
	}
	return w_pierwsza;

}

int miejsce_w_uszer(int nr_ZAD){
	int miejsce=0;


	return miejsce;
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

int wyzarzanie(const Generator& generator, int tablica[], int krok) {
	/***********
	*		TODO
	*	-krok zmniejszania temperatury jako argument funkcji
	*	CO PETLE:
	*		- wybor najgorszej maszyny
	*		- sprawdzenie czy gorszy jest przestoj czy zapychacz
	*	
	*	*** kombinowanie z przestojami 
	*			-zamieniamy kolidujaca operacja z bedaca po przestoju liczona od konca uszeregowania krotsza od kolidujacej
	*			
	*	*** kombinowanie z zapychaczami
	*			-szukanie najdluzszego na start z mozliwych
	*			-pr�ba zamiany kolejnych s�siad�w tej operacji z lewej i z prawej
	*			-sprawdzanie czy s�siedzi znajduj� si� w granicach uszeregowania
	*			-wsadzenie p�niejszej operacji na wcze�niejsze miejsce
	*			-przeliczenie wszysktich operacji nast�puj�cych po tej wcze�niejszej (ju� przestawionej), a� do odkrycia miejsca startowego operacji p�niejszej
	*			-sprawdzenie czy wcze�niejsza operacja mo�e wej�� na p�niejsze miejsce
	*			-je�eli nie mo�e to kontynuujemy p�tle zgodnie ze wzorem (n to numer zapychacza): n-1,n+1; n-1,n+2, n-2,n+1, n-2,n+2 itd...
	*			-kontynuowanie p�tli p�ki nie osi�gniemy oczekiwanej poprawy (poda� jako argument?)
	*			-po nieudanej probie zmieniamy wartosc na false w tablicy mozliwosci pracy z danym przestojem
	*	-zapisywanie najlepszego uszeregowania do wyniku
	***********/

	/*
	petle:
		- z czasem
		- tak dlugo az nie poprawimy najgorszej maszyny (bedzie inna najgorsza)
		- z zapychaczami
		- z przestojami

	*/


	vector <Operacja*> zadania;																				// wektor do fukcji sortowanie 
	Maszyna* maszyna;																						// wskaznik na dana maszyne
	int granica=tablica[0] , optimum=tablica[1];														// TABLICA pierwszy element to czas uszeregowania algorytmu losowego, a drugi to optimum ponizej ktorego na pewno nie zejdziemy
/*
	for (int i=0; i<generator.liczbaZadan; ++i)																// wypisanie czasow gotowosci wsyzstkich zadan
		cout << "zadanie nr " << i << " jest gotowe o: " << generator.zadania[i]->delay << endl;
*/


//	while (granica > optimum) {														// petla
	int przestoj[3] = {-2,-2,-2};													// [0]-> nr_operacji na ktorej jest przestoj	[1]-> wartosc kary dla tej oepracji		[2]-> nr_przestoju z kara;
	int pozostaly_czas = -2;														// jesli -2 to oznacza blad    wyzej tez tak jest
	int nr_maszyny = ktora_maszyna(generator);										// wybieramy najmniej zawalona maszyne
	maszyna = generator.maszyny[nr_maszyny];										// i przypisujemy na nia wskaznik
	int max_zap = max_zapychacz(maszyna->uszeregowanie);							// najdluzszy zapychacza na tej maszynie

	operacja_z_max_kara(*maszyna, przestoj);										// zwraca w przestoj[3] kolejno: numer operacji W USZEREGOWANIU, na kt�rej traci si� najwi�cej na przestoju; wartosc kary dla tej oepracji;	nr_przestoju z kara;
	if (przestoj[1] >= 0 )															// sprawdzamy czy istnieje przestoj z kara
		pozostaly_czas = czas_do_przestoju(*maszyna, przestoj[2]);					//jesli tak to sprawdzamy jaki mamy czas do tego przestoju

	cout << " Maszyna: " << nr_maszyny << ", liczba zapychaczy: " << liczba_zapychaczy(maszyna->uszeregowanie) <<", CZAS zapychaczy: " << czas_zapychaczy(maszyna->uszeregowanie) << endl << endl;
	cout << " wartosc kary dla tej operacji to: " << przestoj[1] << endl;
	cout << " MAX zapychacz ma wartosc: " << max_zap << endl;

//	sortowanie(maszyna->uszeregowanie, zadania);
//	cout << " Pierwszy element ma czas: " << zadania[0]->czas << endl;

	
	
	/// na ktore zamienic!!!	 //w pierwszej iteracji zamieniamy najbli�sze operacje po obu stronach "miejsca", w przypadku niepowodzenia rozszerzamy poszukiwany zakres
	
	//[TODO]doda� zapychacze do wektora miejsc poprawy
	if ( max_zap >= przestoj[1] )																// JESLI ZAPYCHACZ JEST WIEKSZY OD KARY 
	{	//	zamiana na zasadzie wrzucenia zadania												// ZROB Z NIM PORZADEK
		//	dluzszego? krotszego ? LOSOWEGO <- ? 

		

	}
		else 																					// JESLI KARA JEST WIEKSZA OD ZAPYCHACZA 
	{	//	zamiana na zasadzie dopasowania do pozostalego czasu,								// TO Z NIA ZROB PORZADEK
		//	ew nastpeniewrzucenie najkrotszego mozliwego (dla malej kary)																							
		cout << " Nr operacji DO POPRAWY w  uszeregowaniu to: " << przestoj[0]+1 << endl;
		cout << " nr_przestoju z kara to: " << przestoj[2]+1<< endl;
		cout << " Pozostaly czas to: " << pozostaly_czas << endl;

	}
	

	// granica -= krok;		 }	// koniec petli

	// wybor najlepszego
	return 0;
}