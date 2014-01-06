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

	if ((maszyna.uszeregowanie[i]->begin + maszyna.uszeregowanie[i]->czas) == start)
		return 0;

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

bool warunki(const Operacja & bbb, int czas) {
	bool w_pierwsza = true;
	if(bbb.numer == 0){
		if (bbb.parent->delay > czas)
			w_pierwsza = false;
	}
	else{
		Operacja *poprzednia = bbb.parent->operacje[bbb.numer-1];
		if ( (poprzednia->begin + poprzednia->czas) > czas )
			w_pierwsza = false;
	}
	return w_pierwsza;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


int czas_uszeregowania(vector<Operacja*> & uszeregowanie) {
		int ostatni=uszeregowanie.size()-1;
		int dlugosc = uszeregowanie[ostatni]->begin + uszeregowanie[ostatni]->czas;
		return dlugosc;																				//zwracamy czas zako�czenia ostatniej operacji (aka d�ugo�� uszeregowania na danej maszynie)
}

void zamiana( int  aaa, int  bbb, vector<Operacja*> & uszeregowanie ) {
		
		Operacja tmp = *uszeregowanie[aaa];																			//zamieniamy operacje ze sob� miejscami
		*uszeregowanie[aaa] = *uszeregowanie[bbb];
		*uszeregowanie[bbb] = tmp;
}

bool mozna_zamienic(int aaa, int bbb, Maszyna & maszyna, int temperatura) {
	if(maszyna.uszeregowanie[bbb]->numer >5 )
		return false;

	if(maszyna.uszeregowanie[bbb]->numer == 0){
		if (maszyna.uszeregowanie[bbb]->parent->delay > maszyna.uszeregowanie[aaa]->begin)
			return false;
	}
	else{
		int nr =maszyna.uszeregowanie[bbb]->numer-1;
		Operacja *poprzednia = maszyna.uszeregowanie[bbb]->parent->operacje[nr];
		if ( (poprzednia->begin + poprzednia->czas) > maszyna.uszeregowanie[aaa]->begin )
			return false;
	}

	vector <Operacja*> kopia_uszeregowania;	
	for (int i=0; i< maszyna.uszeregowanie.size(); i++)
		kopia_uszeregowania.push_back(maszyna.uszeregowanie[i]);

	zamiana(aaa, bbb, kopia_uszeregowania);
	
	if (!obliczenie_uszeregowania(kopia_uszeregowania, maszyna))																//obliczamy czasy pozosta�ych operacji w uszeregowaniu
		return false;
		
	int nowa_dlugosc = czas_uszeregowania(kopia_uszeregowania);
	if (nowa_dlugosc > temperatura )
		return false;

	maszyna.uszeregowanie.clear();																		// zerujemy uszeregowanie na maszynie
	for (int i=0; i< kopia_uszeregowania.size(); i++)													// wstawiamy nowe uszeregowanie
		maszyna.uszeregowanie.push_back(kopia_uszeregowania[i]);
	// koniec?
 
	return true;
}

int miejsce_w_uszer(int wartosc_zapychacza, Maszyna & maszyna){
		int miejsce=0;
		while (miejsce < maszyna.uszeregowanie.size()){
			if (maszyna.uszeregowanie[miejsce]->numer == 98)
				if (wartosc_zapychacza == maszyna.uszeregowanie[miejsce]->czas)
					break;
		miejsce++;
		}
	return miejsce;
}

bool obliczenie_uszeregowania(vector<Operacja*> & uszeregowanie, Maszyna & maszyna) {
	int czas = uszeregowanie[0]->begin + uszeregowanie[0]->czas;																							//obecny kwant czasu
	int czas_przestoju;																						//czas rozpocz�cia ka�dego kolejnego przestoju
	int nastepny_przestoj = 0;																				//numer nast�pnego przestoju
	int zapychacz = 0;																						//ile potrzeba zapychacza
	bool czyPrzestoje = true;																				//flaga czy zosta�y jakie� przestoje
	int dlugosc = uszeregowanie.size();																		//obecna d�ugo�� uszeregowania

	for(int i = 1; i < dlugosc; ++i) {																		//dla ka�dej operacji na maszynie
		zapychacz = 0;
		if(uszeregowanie[i]->numer < 3) {	
			while(!warunki(*uszeregowanie[i],czas+zapychacz)) {															//sprawdzenie poprawno�ci
				zapychacz++;
			}
			if(zapychacz !=0) {
				Operacja  *op = new Operacja(zapychacz,98,NULL,98);													//tworzenie zapychacza
				vector<Operacja*>::iterator it = uszeregowanie.begin()+i;
				uszeregowanie.insert(it,op);																//wk�adanie go do wektora
				++i;													//omijamy zapychacz i przechodzimy do nast�pnej operacji
				czas +=	zapychacz;									//dodajemy d�ugo�� zapychacza do czasu
				dlugosc++;
			}
		
			if(czas != (uszeregowanie[i-1]->begin + uszeregowanie[i-1]->czas)) {								//je�eli czas si� nie zgadza
																											
				//for(int j = 0; j < maszyna.nPrzestojow; ++j) {//przestoje
				czas_przestoju = maszyna.rozpoczecie[nastepny_przestoj];
				if ( czas > czas_przestoju &&  czyPrzestoje) {//&& czas < (czas_przestoju + maszyna.dlugosc[nastepny_przestoj]) ) {	
															//jeste�my obecnie na przestoju
					if ( czas != (uszeregowanie[i-1]->begin + uszeregowanie[i-1]->czas*0.3 + maszyna.dlugosc[nastepny_przestoj])) {
																			//jeste�my na przestoju i czas si� nie zgadza
						uszeregowanie[i]->begin = czas + uszeregowanie[i-1]->begin + uszeregowanie[i-1]->czas*0.3 
							+ maszyna.dlugosc[nastepny_przestoj];			//ustawiamy czas rozpocz�cia operacji od pocz�tku bazuj�c na czasie
					}														//poprzedniej operacji
					czas += maszyna.dlugosc[nastepny_przestoj] + 0.3*uszeregowanie[i]->czas; //tylko 0.3 bo reszt� dodajemy p�niej
					if(maszyna.nPrzestojow=(nastepny_przestoj+1))		//je�eli sko�czy�y si� przestoje
						czyPrzestoje = false;							//to podnosimy flag� ich braku
					if(czyPrzestoje)
						nastepny_przestoj++;
					
				}
				else						//czas si� zgadza
					uszeregowanie[i]->begin = czas;					//tu to samo tylko nie dodajemy d�ugo�ci przestoju
			}
			if(uszeregowanie[i]->numer == 1 || uszeregowanie[i]->numer == 0) {						//sprawdzamy czy nast�pna operacja nie zaczyna si� za wcze�nie
				Operacja *nastepna = uszeregowanie[i]->parent->operacje[uszeregowanie[i]->numer+1];
				if ( nastepna->begin < (czas + uszeregowanie[i]->czas) )		
					return false;									//je�eli tak to gi�
			}
		czas += uszeregowanie[i]->czas;								//przesuwamy kwant czasu o d�ugo�� operacji
		}
		else{
			uszeregowanie.erase(uszeregowanie.begin() + i); 
			i--;
			dlugosc--;
		}

	}
	return true;
}

void sortowanie_zapychaczy(vector<vector<int> > & zapychacze, vector<Operacja*> & uszeregowanie) {
	
	for(int i = 0; i<uszeregowanie.size(); ++i) {			//dodawanie zapychaczy do wektora
		if(uszeregowanie[i]->numer >4) {
			vector<int> nowy;
			nowy.push_back(uszeregowanie[i]->czas);
			nowy.push_back(i);
			zapychacze.push_back(nowy);
		}
	}
	sort(zapychacze.begin(),zapychacze.end(),porownaj);		//sortowanie
}

bool porownaj(vector<int> a, vector<int> b) {
	return a[0]<b[0];
}

bool wedlug_p(vector <int> a, vector <int> b)
{
	int asuma=0, bsuma=0;
	asuma+=a[0];
	bsuma+=b[0];
    return asuma > bsuma;
}

void sortowanie_przestojow(vector<vector<int> > & przestoje, Maszyna & maszyna){
	for(int i = 0; i<maszyna.nPrzestojow; i++) {//szukamy numeru najgorszego w skutkach przestoju
		vector <int> ten;
		int kara = wartosc_kary(maszyna,i);
		if ( kara == 0 )
			continue;

		ten.push_back( kara );
		int j = 0;						
		int start = maszyna.rozpoczecie[i];														//czas rozpocz�cia szukanego przestoju
		while ( (maszyna.uszeregowanie[j]->begin + maszyna.uszeregowanie[j]->czas) < start){
			j++;																				//szukamy operacji, kt�ra nachodzi na przest�j
			if (i==maszyna.uszeregowanie.size()){
				break;
			}
		}
		ten.push_back(j);
		przestoje.push_back(ten);
	}

	sort(przestoje.begin(), przestoje.end(), wedlug_p);

}




//////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////          G��WNY ALGORYTM           ////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int wyzarzanie(const Generator& generator, int tablica[], int krok) {
    /***********
    *                                ~~~~~~~~<[[ TODO ]]>~~~~~~~~
    *    [DONE]krok zmniejszania temperatury jako argument funkcji
    *    [DONE]zapisanie do 3 int�w d�ugo�ci uszeregowania ka�dej z maszyn
    *    P�TLA Z CZASEM:
    *       [DONE]wyb�r najgorszej maszyny
    *       P�TLA Z MASZYN�
    *             [DONE]kontynuowanie p�tli p�ki nie osi�gniemy oczekiwanej poprawy (tzn. czas uszeregowania na danej maszynie musi by� lepszy od czasu uszeregowania na 2-giej najgorszej maszynie
    *              [DONE]sprawdzenie czy gorszy jest przest�j czy zapychacz
    *    
    *             P�TLA Z PRZESTOJAMI (je�eli najgorszy jest przest�j)
    *                    -pr�bujemy zamieni� koliduj�c� operacja z b�dac� po przestoju liczona od ko�ca uszeregowania kr�tsza od koliduj�cej
    *            -je�eli �adna zamiana nie poprawia czasu/nie jest mo�liwa to przechodzimy na nast�pny przest�j w posortowanym wektorze najgorszych przestoj�w do skutku
    *             P�TLA Z ZAPYCHACZAMI (je�eli najgorszy jest zapychacz)
    *            -szukanie najgorszego zapychacza z mo�liwych na start
    *            -pr�ba zamiany kolejnych s�siad�w tej operacji z lewej i z prawej
    *            -sprawdzanie czy s�siedzi znajduj� si� w granicach uszeregowania
    *            -wsadzenie p�niejszej operacji na wcze�niejsze miejsce
    *            -przeliczenie wszysktich operacji nast�puj�cych po tej wcze�niejszej (ju� przestawionej), a� do odkrycia miejsca startowego operacji p�niejszej
    *            -sprawdzenie czy wcze�niejsza operacja mo�e wej�� na p�niejsze miejsce
    *            -je�eli nie mo�e to kontynuujemy p�tle zgodnie ze wzorem (n to numer zapychacza):  n-1 z n+1, n+2�; n-2 z n+1 itd.
    *            [PRZENIESIONE]sprawdzamy czy osi�gni�ty wynik jest lepszy od obecnej temperatury, je�eli nie to zaniechujemy zmiany
    *     [DONE]je�eli nast�pi�a poprawa wzgl�dem poprzedniego najlepszego wyniku to zapisujemy czas uszeregowania na drugiej najgorszej maszynie jako tymczasowe najlepsze uszergowanie (wynik to int)
    *     [DONE]zmniejszamy temperatur� o krok
    *     [DONE]najlepszy czas uszeregowania zwracany jako wynik
    ***********/

	srand(NULL);																								//zmienne do liczenia czasu
	clock_t start;
	clock_t koniec;
	float czas=0;
	int wynik;    																							// najlepszy tymczasowy wynik (p�niej jest zwracany jako ostateczny)
	Maszyna* maszyna;                   																		// wskaznik na maszyn� kt�ra b�dzie obrabiana
	int granica=tablica[0] , optimum=tablica[1];       														// TABLICA pierwszy element to czas uszeregowania algorytmu losowego, a drugi to optimum ponizej ktorego na pewno nie zejdziemy

///////////////////    pierwsza petla       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	start=clock();         													       						    //rozpoczynamy odliczanie czasu
	while (czas < 60) {						       															// P�TLA Z CZASEM

		int dlugosc0 = czas_uszeregowania(generator.maszyny[0]->uszeregowanie);								 
		int dlugosc1 = czas_uszeregowania(generator.maszyny[1]->uszeregowanie);								//LICZENIE CZAS�W MASZYN
		int dlugosc2 = czas_uszeregowania(generator.maszyny[2]->uszeregowanie);

		bool mozliwa_poprawa = true;
		int najgorsza_maszyna = ktora_maszyna(generator);													// wybieramy najbardziej zawalona maszyne
		maszyna = generator.maszyny[najgorsza_maszyna];														// przypisujemy wskaznik na najgorsza maszyne
		int czas_drugiej_najgorszej;																		// czas drugiej najgorszej
	
		if((dlugosc0>dlugosc1 && dlugosc0<dlugosc2) || (dlugosc0<dlugosc1 && dlugosc0>dlugosc2))
			czas_drugiej_najgorszej = dlugosc0;
		else if((dlugosc1>dlugosc2 && dlugosc1<dlugosc0) || (dlugosc1>dlugosc0 && dlugosc1<dlugosc2))
			czas_drugiej_najgorszej = dlugosc1;
		else
			czas_drugiej_najgorszej = dlugosc2;

		bool koniec_zap = false, koniec_przest = false;		

///////////////////    druga petla       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

		while (czas_uszeregowania(generator.maszyny[najgorsza_maszyna]->uszeregowanie) >= czas_drugiej_najgorszej) {            //P�TLA Z MASZYN�


			cout << " Maszyna: " << najgorsza_maszyna 
				 << ", liczba zapychaczy: " << liczba_zapychaczy(maszyna->uszeregowanie) 
				 <<", CZAS zapychaczy: " << czas_zapychaczy(maszyna->uszeregowanie) << endl << endl;
//			int przestoj[3] = {-2,-2,-2};													// [0]-> nr_operacji na ktorej jest przestoj	[1]-> wartosc kary dla tej oepracji		[2]-> nr_przestoju z kara;
//			int pozostaly_czas = -2;														// jesli -2 to oznacza blad    wyzej tez tak jest
//			int max_zap = max_zapychacz(maszyna->uszeregowanie);							// najdluzszy zapychacza na tej maszynie
//			operacja_z_max_kara(*maszyna, przestoj);										// zwraca w przestoj[3] kolejno: numer operacji W USZEREGOWANIU, na kt�rej traci si� najwi�cej na przestoju; wartosc kary dla tej oepracji;	nr_przestoju z kara;
//			if (przestoj[1] >= 0 )															// sprawdzamy czy istnieje przestoj z kara
//				pozostaly_czas = czas_do_przestoju(*maszyna, przestoj[2]);					//jesli tak to sprawdzamy jaki mamy czas do tego przestoju
//			cout << " wartosc kary dla tej operacji to: " << przestoj[1] << endl;
//			cout << " MAX zapychacz ma wartosc: " << max_zap << endl << endl;

			vector<vector<int> > zapychacze;																
			sortowanie_zapychaczy(zapychacze, maszyna->uszeregowanie);										// sortujemy zapychacze poz wzgledem dlugosci ich trwania

			vector<vector<int> > przestoje;
			sortowanie_przestojow(przestoje, *maszyna);														// sortujemy przestoje poz wzgledem dlugosci ich trwania

			if (przestoje.size()==0)
				koniec_przest=true;

			if (zapychacze.size()==0)
				koniec_zap=true;
/*			cout << endl;
			for (int i=0; i<przestoje.size(); i++){
				for (int j=0; j<2; j++)														// WYPISYWANIE POSORTWANYCH PRZESTOJOW
					cout << przestoje[i][j] << "\t" ;
				cout << endl;
			}													

			if (!mozna_zamienic(2,3, *maszyna, czas_drugiej_najgorszej))					// PROBNA ZAMIANA
				cout << endl << "NIE MOZNA ZAMIENIC" << endl << endl;			*/

	
	//////          zapychacz vs przestoj           //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			
														
			if ( ((koniec_zap == false && koniec_przest == false) && (zapychacze[0][0] >= przestoje[0][0])  ) || (koniec_zap == false && koniec_przest == true))// JESLI ZAPYCHACZ JEST WIEKSZY OD KARY 
			{	// ZAPYCHACZE
				bool zamieniono=false;
				int ktory = 0;
				while ( (zamieniono == false) && (ktory < zapychacze.size()) ){
					int miejsce = zapychacze[ktory][1];
					for (int i=miejsce-1; i>=0; i--){
						for (int j=miejsce+1; j<maszyna->uszeregowanie.size();j++)
							if ( (maszyna->uszeregowanie[i]->numer != 98) && (maszyna->uszeregowanie[j]->numer != 98) )
								if (mozna_zamienic(i,j, *maszyna, czas_drugiej_najgorszej)){
									cout << endl << "ZAMIENIONO" << endl << endl;
									zamieniono=true;
								}
					}	// koniec for
					ktory++;
				}	//koniec while

				if(zamieniono == false)
					koniec_zap = true;
				else
					koniec_zap = false;
			}	//koniec zapychaczy


			if ( ((koniec_zap == false && koniec_przest == false) && (zapychacze[0][0] < przestoje[0][0])  ) || (koniec_zap == true && koniec_przest == false))// JESLI KARA JEST WIEKSZA OD ZAPYCHACZA 
			{	 // PRZESTOJE											
				int ktory=0;
				bool zamieniono=false;
/*				cout << " Nr operacji DO POPRAWY w  uszeregowaniu to: " << przestoj[0]+1 << endl;
				cout << " nr_przestoju z kara to: " << przestoj[2]+1<< endl;
				cout << " Pozostaly czas to: " << pozostaly_czas << endl;										*/
				while ( (zamieniono == false) && (ktory < przestoje.size()) ){
					for (int i=(maszyna->uszeregowanie.size()-1); i>przestoje[ktory][1]; i--){
						if (maszyna->uszeregowanie[i] < maszyna->uszeregowanie[przestoje[ktory][0]])
							if (mozna_zamienic(przestoje[ktory][0],i, *maszyna, czas_drugiej_najgorszej)){
								cout << endl << "ZAMIENIONO" << endl << endl;
								zamieniono=true;
							}
					}
					ktory++;
				}
					if(zamieniono == false)
						koniec_przest = true;
					else
						koniec_przest = false;

				} //koniec p�tli z przestojami
				
			
			if (koniec_zap==true && koniec_przest==true){
					mozliwa_poprawa=false;
					break;
				}

			}  //koniec p�tli z maszyn�
		if (czas_uszeregowania(maszyna->uszeregowanie) < czas_drugiej_najgorszej )
			wynik = czas_drugiej_najgorszej;									//zmiana NAJGORSZEGO CZASU (CZYLI DRUGIEJ MASZYNY)
		else
			wynik = czas_uszeregowania(maszyna->uszeregowanie);
     	koniec=clock();
		czas=(float)(koniec-start)/CLOCKS_PER_SEC;							//obliczanie bie��cego czasu
		if (mozliwa_poprawa==false) {
			cout << "****************** NIEMOZLIWA POPRAWA ****************** " << endl << endl;
			break;
		}
	}    // koniec p�tli z czasem

   //ZWRACANIE WYNIKU (NAJLEPSZEGO NAPOTKANEGO PO DRODZE CZASU NAJGORSZEJ MASZYNY)
   cout << " NASZ WYNIK TO = " <<wynik <<endl;
   return wynik;
}