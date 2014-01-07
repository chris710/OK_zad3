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
	int start, kara=0, i=0;
	start = maszyna.rozpoczecie[nr_przestoju];//czas rozpoczêcia szukanego przestoju

	while ( (maszyna.uszeregowanie[i]->begin + maszyna.uszeregowanie[i]->czas) < start){
		i++;							//szukamy operacji, która nachodzi na przestój
		if (i==maszyna.uszeregowanie.size())
			return 0;
	}

	if ((maszyna.uszeregowanie[i]->begin + maszyna.uszeregowanie[i]->czas) == start)
		return 0;

	if (maszyna.uszeregowanie[i]->numer != 98)
		kara = 0.3 * maszyna.uszeregowanie[i]->czas;		
	return kara;						//zwracamy 30% jej d³ugoœci
}


void operacja_z_max_kara(const Maszyna & maszyna, int przestoj[]) {
	int result;							//numer operacji do wywalenia
	int max = -1;						//najwiêksza strata czasu
	int tmp;							//zmienna tymczasowa do obecnej straty czasu
	int nr_przestoju;					//przestoj, na którym tracimy najwiêcej
	
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
	int start = maszyna.rozpoczecie[nr_przestoju];//czas rozpoczêcia szukanego przestoju
	while ( (maszyna.uszeregowanie[i]->begin + maszyna.uszeregowanie[i]->czas) < start){
		i++;							//szukamy operacji, która nachodzi na przestój
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
			i++;						//szukamy operacji, która nachodzi na przestój
		if (i==maszyna.uszeregowanie.size())
			return 0;
	}		
		czas = start - (maszyna.uszeregowanie[i-1]->begin + maszyna.uszeregowanie[i-1]->czas);
										//liczymy czas od zakoñczenia operacji poprzedzaj¹cej to przestoju
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
		return dlugosc;																				//zwracamy czas zakoñczenia ostatniej operacji (aka d³ugoœæ uszeregowania na danej maszynie)
}

void zamiana( int  aaa, int  bbb, vector<Operacja*> & uszeregowanie ) {
		
		Operacja tmp = *uszeregowanie[aaa];																			//zamieniamy operacje ze sob¹ miejscami
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
	
	if (!obliczenie_uszeregowania(kopia_uszeregowania, maszyna))																//obliczamy czasy pozosta³ych operacji w uszeregowaniu
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
	int czas_przestoju;																						//czas rozpoczêcia ka¿dego kolejnego przestoju
	int nastepny_przestoj = 0;																				//numer nastêpnego przestoju
	int zapychacz = 0;																						//ile potrzeba zapychacza
	bool czyPrzestoje = true;																				//flaga czy zosta³y jakieœ przestoje
	int dlugosc = uszeregowanie.size();																		//obecna d³ugoœæ uszeregowania

	for(int i = 1; i < dlugosc; ++i) {																		//dla ka¿dej operacji na maszynie
		zapychacz = 0;
		if(uszeregowanie[i]->numer < 3) {	
			while(!warunki(*uszeregowanie[i],czas+zapychacz)) {															//sprawdzenie poprawnoœci
				zapychacz++;
			}
			if(zapychacz !=0) {
				Operacja  *op = new Operacja(zapychacz,98,NULL,98);													//tworzenie zapychacza
				op->begin=czas;
				vector<Operacja*>::iterator it = uszeregowanie.begin()+i;
				uszeregowanie.insert(it,op);																//wk³adanie go do wektora
				++i;													//omijamy zapychacz i przechodzimy do nastêpnej operacji
				czas +=	zapychacz;									//dodajemy d³ugoœæ zapychacza do czasu
				dlugosc++;
			}
		
			if(czas != (uszeregowanie[i-1]->begin + uszeregowanie[i-1]->czas)) {								//je¿eli czas siê nie zgadza
																											
				//for(int j = 0; j < maszyna.nPrzestojow; ++j) {//przestoje
				czas_przestoju = maszyna.rozpoczecie[nastepny_przestoj];
				if ( czas > czas_przestoju &&  czyPrzestoje) {//&& czas < (czas_przestoju + maszyna.dlugosc[nastepny_przestoj]) ) {	
															//jesteœmy obecnie na przestoju
					if ( czas != (uszeregowanie[i-1]->begin + uszeregowanie[i-1]->czas*0.3 + maszyna.dlugosc[nastepny_przestoj])) {
																			//jesteœmy na przestoju i czas siê nie zgadza
						uszeregowanie[i]->begin = czas + uszeregowanie[i-1]->begin + uszeregowanie[i-1]->czas*0.3 
							+ maszyna.dlugosc[nastepny_przestoj];			//ustawiamy czas rozpoczêcia operacji od pocz¹tku bazuj¹c na czasie
					}														//poprzedniej operacji
					czas += maszyna.dlugosc[nastepny_przestoj] + 0.3*uszeregowanie[i]->czas; //tylko 0.3 bo resztê dodajemy póŸniej
					if(maszyna.nPrzestojow==(nastepny_przestoj+1))		//je¿eli skoñczy³y siê przestoje
						czyPrzestoje = false;							//to podnosimy flagê ich braku
					if(czyPrzestoje)
						nastepny_przestoj++;
					
				}
				else						//czas siê zgadza
					uszeregowanie[i]->begin = czas;					//tu to samo tylko nie dodajemy d³ugoœci przestoju
			}
			if(uszeregowanie[i]->numer == 1 || uszeregowanie[i]->numer == 0) {						//sprawdzamy czy nastêpna operacja nie zaczyna siê za wczeœnie
				Operacja *nastepna = uszeregowanie[i]->parent->operacje[uszeregowanie[i]->numer+1];
				if ( nastepna->begin < (czas + uszeregowanie[i]->czas) )		
					return false;									//je¿eli tak to giñ
			}
		czas += uszeregowanie[i]->czas;								//przesuwamy kwant czasu o d³ugoœæ operacji
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
		int start = maszyna.rozpoczecie[i];														//czas rozpoczêcia szukanego przestoju
		while ( (maszyna.uszeregowanie[j]->begin + maszyna.uszeregowanie[j]->czas) < start){
			j++;																				//szukamy operacji, która nachodzi na przestój
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
//////          G£ÓWNY ALGORYTM           ////////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////

int wyzarzanie(const Generator& generator, int tablica[], int krok) {
    /***********
    *                                ~~~~~~~~<[[ TODO ]]>~~~~~~~~
    *    [DONE]krok zmniejszania temperatury jako argument funkcji
    *    [DONE]zapisanie do 3 intów d³ugoœci uszeregowania ka¿dej z maszyn
    *    PÊTLA Z CZASEM:
    *       [DONE]wybór najgorszej maszyny
    *       PÊTLA Z MASZYN¥
    *             [DONE]kontynuowanie pêtli póki nie osi¹gniemy oczekiwanej poprawy (tzn. czas uszeregowania na danej maszynie musi byæ lepszy od czasu uszeregowania na 2-giej najgorszej maszynie
    *              [DONE]sprawdzenie czy gorszy jest przestój czy zapychacz
    *    
    *             PÊTLA Z PRZESTOJAMI (je¿eli najgorszy jest przestój)
    *                    -próbujemy zamieniæ koliduj¹c¹ operacja z bêdac¹ po przestoju liczona od koñca uszeregowania krótsza od koliduj¹cej
    *            -je¿eli ¿adna zamiana nie poprawia czasu/nie jest mo¿liwa to przechodzimy na nastêpny przestój w posortowanym wektorze najgorszych przestojów do skutku
    *             PÊTLA Z ZAPYCHACZAMI (je¿eli najgorszy jest zapychacz)
    *            -szukanie najgorszego zapychacza z mo¿liwych na start
    *            -próba zamiany kolejnych s¹siadów tej operacji z lewej i z prawej
    *            -sprawdzanie czy s¹siedzi znajduj¹ siê w granicach uszeregowania
    *            -wsadzenie póŸniejszej operacji na wczeœniejsze miejsce
    *            -przeliczenie wszysktich operacji nastêpuj¹cych po tej wczeœniejszej (ju¿ przestawionej), a¿ do odkrycia miejsca startowego operacji póŸniejszej
    *            -sprawdzenie czy wczeœniejsza operacja mo¿e wejœæ na póŸniejsze miejsce
    *            -je¿eli nie mo¿e to kontynuujemy pêtle zgodnie ze wzorem (n to numer zapychacza):  n-1 z n+1, n+2…; n-2 z n+1 itd.
    *            [PRZENIESIONE]sprawdzamy czy osi¹gniêty wynik jest lepszy od obecnej temperatury, je¿eli nie to zaniechujemy zmiany
    *     [DONE]je¿eli nast¹pi³a poprawa wzglêdem poprzedniego najlepszego wyniku to zapisujemy czas uszeregowania na drugiej najgorszej maszynie jako tymczasowe najlepsze uszergowanie (wynik to int)
    *     [DONE]zmniejszamy temperaturê o krok
    *     [DONE]najlepszy czas uszeregowania zwracany jako wynik
    ***********/
	const float max_czas =10;
	ofstream pliki("pliki.txt");
	srand(NULL);																								//zmienne do liczenia czasu
	clock_t start;
	clock_t koniec;
	float czas=0;
	int wynik;    																							// najlepszy tymczasowy wynik (póŸniej jest zwracany jako ostateczny)
	Maszyna* maszyna;                   																		// wskaznik na maszynê która bêdzie obrabiana
	int granica=tablica[1] , optimum=tablica[0];       														// TABLICA pierwszy element to czas uszeregowania algorytmu losowego, a drugi to optimum ponizej ktorego na pewno nie zejdziemy
	//cout <<  granica << "\t" << optimum;
///////////////////    pierwsza petla       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

	start=clock();         													       						    //rozpoczynamy odliczanie czasu
	while (czas < max_czas) {						       															// PÊTLA Z CZASEM

		int dlugosc0 = czas_uszeregowania(generator.maszyny[0]->uszeregowanie);								 
		int dlugosc1 = czas_uszeregowania(generator.maszyny[1]->uszeregowanie);								//LICZENIE CZASÓW MASZYN
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

		int do_poprawy = czas_drugiej_najgorszej;

///////////////////    druga petla       //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
		bool koniec_zap = false, koniec_przest = false;	
		while (czas_uszeregowania(generator.maszyny[najgorsza_maszyna]->uszeregowanie) >= czas_drugiej_najgorszej) {            //PÊTLA Z MASZYN¥

//			cout << " Maszyna: " << najgorsza_maszyna 
//				 << ", liczba zapychaczy: " << liczba_zapychaczy(maszyna->uszeregowanie) 
//				 <<", CZAS zapychaczy: " << czas_zapychaczy(maszyna->uszeregowanie) << endl << endl;


			vector<vector<int> > zapychacze;																
			sortowanie_zapychaczy(zapychacze, maszyna->uszeregowanie);										// sortujemy zapychacze poz wzgledem dlugosci ich trwania

			vector<vector<int> > przestoje;
			sortowanie_przestojow(przestoje, *maszyna);														// sortujemy przestoje poz wzgledem dlugosci ich trwania

			if (przestoje.size()==0)
				koniec_przest=true;

			if (zapychacze.size()==0)
				koniec_zap=true;

//////          zapychacz vs przestoj           //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
																	
			if ( ((koniec_zap == false && koniec_przest == false) && (zapychacze[0][0] >= przestoje[0][0])  ) || (koniec_zap == false && koniec_przest == true))// JESLI ZAPYCHACZ JEST WIEKSZY OD KARY 
			{	// ZAPYCHACZE
				bool zamieniono=false;
				int ktory = 0;
				while ( (zamieniono == false) && (ktory < zapychacze.size()) ){
					int miejsce = zapychacze[ktory][1];
					for (int i=miejsce-1; i>=0; i--){
						for (int j=miejsce+1; j<maszyna->uszeregowanie.size();j++)
							if ( (maszyna->uszeregowanie[i]->numer != 98) && (maszyna->uszeregowanie[j]->numer != 98) ){
								if (mozna_zamienic(i,j, *maszyna, do_poprawy)){
									cout << endl << "ZAMIENIONO" << endl << endl;
									zamieniono=true;
								koniec=clock();
								czas=(float)(koniec-start)/CLOCKS_PER_SEC;
								float a = czas_uszeregowania(maszyna->uszeregowanie);
								pliki << czas << "\t" << (a/granica) << endl;
								break;
								}}
							if(zamieniono==true)
								break;
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
				while ( (zamieniono == false) && (ktory < przestoje.size()) ){
					for (int i=(maszyna->uszeregowanie.size()-1); i>przestoje[ktory][1]; i--){
						if (maszyna->uszeregowanie[i]->czas < maszyna->uszeregowanie[przestoje[ktory][1]]->czas){
							float b = czas_uszeregowania(maszyna->uszeregowanie);
							if (mozna_zamienic(przestoje[ktory][1],i, *maszyna, do_poprawy)){
								cout << endl << "ZAMIENIONO" << endl << endl;
								zamieniono=true;
								koniec=clock();
								czas=(float)(koniec-start)/CLOCKS_PER_SEC;
								float a = czas_uszeregowania(maszyna->uszeregowanie);
								//cout << "\t" << a;
								pliki << czas << "\t" << (a/granica) << endl;
								break;
							}}
					}
					ktory++;
				}
					if(zamieniono == false)
						koniec_przest = true;
					else
						koniec_przest = false;

				} //koniec pêtli z przestojami
				
			
			if (koniec_zap==true && koniec_przest==true){
					//mozliwa_poprawa=false;
					//cout << " Nie udalo sie " << endl;
					do_poprawy += krok;
					koniec_zap = false;
					koniec_przest = false;	
					//cout << do_poprawy << endl;
				}

			koniec=clock();
			czas=(float)(koniec-start)/CLOCKS_PER_SEC;
			if (czas > max_czas)
				break;

			}  //koniec pêtli z maszyn¹
			int worst= ktora_maszyna(generator);
			wynik = czas_uszeregowania(generator.maszyny[worst]->uszeregowanie);
     		koniec=clock();
			czas=(float)(koniec-start)/CLOCKS_PER_SEC;							//obliczanie bie¿¹cego czasu

	}    // koniec pêtli z czasem

	
/*	for (int i=0; i<3; i++)
	{		
		//cout << "NR " << i << " MASZYNA:" << endl<<"------"<<endl;
		pliki << "NR " << i << " MASZYNA:" << endl<<"------"<<endl;
		for (int j=0; j<generator.maszyny[i]->uszeregowanie.size(); j++)
		{
			pliki << "OP = " << (generator.maszyny[i]->uszeregowanie[j]->numer)+1 
					<< "\t\tZAD = " << (generator.maszyny[i]->uszeregowanie[j]->nrZadania)+1 
					<< "\t\tCZAS = " << generator.maszyny[i]->uszeregowanie[j]->czas << endl<<endl;	
		}
	}
*/
   //ZWRACANIE WYNIKU (NAJLEPSZEGO NAPOTKANEGO PO DRODZE CZASU NAJGORSZEJ MASZYNY)
   cout << " NASZ WYNIK TO = " <<wynik <<endl << endl;
   return wynik;
}