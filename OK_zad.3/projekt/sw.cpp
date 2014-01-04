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
/*		
	int nowa_dlugosc = czas_uszeregowania(kopia_uszeregowania);
	if (nowa_dlugosc > temperatura )
		return false;
*/
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
	int dlugosc = uszeregowanie.size();																		//obecna d³ugoœæ uszeregowania
	//for(vector<Operacja*>::iterator it = maszyna.uszeregowanie.begin(); it != maszyna.uszeregowanie.end(); it++) {
	for(int i = 1; i < dlugosc; ++i) {															//dla ka¿dej operacji na maszynie
		zapychacz = 0;
		if(!uszeregowanie[i]->nrZadania>3) {	
			while(!warunki(*uszeregowanie[i],czas+zapychacz)) {															//sprawdzenie poprawnoœci
				zapychacz++;
			}
			if(zapychacz !=0) {
				Operacja  *op = new Operacja(zapychacz,98,NULL,98);													//tworzenie zapychacza
				vector<Operacja*>::iterator it = uszeregowanie.begin()+i;
				uszeregowanie.insert(it,op);																//wk³adanie go do wektora
				++i;													//omijamy zapychacz i przechodzimy do nastêpnej operacji
				czas +=	zapychacz;									//dodajemy d³ugoœæ zapychacza do czasu
			}
		
			if(czas != (uszeregowanie[i-1]->begin + uszeregowanie[i-1]->czas)) {								//je¿eli czas siê nie zgadza
																											
				//for(int j = 0; j < maszyna.nPrzestojow; ++j) {//przestoje
				czas_przestoju = maszyna.rozpoczecie[nastepny_przestoj];
				if ( czas > czas_przestoju ) {//&& czas < (czas_przestoju + maszyna.dlugosc[nastepny_przestoj]) ) {	
															//jesteœmy obecnie na przestoju
					if ( czas != (uszeregowanie[i-1]->begin + uszeregowanie[i-1]->czas*0.3 + maszyna.dlugosc[nastepny_przestoj])) {
																			//jesteœmy na przestoju i czas siê nie zgadza
						uszeregowanie[i]->begin = czas + uszeregowanie[i-1]->begin + uszeregowanie[i-1]->czas*0.3 
							+ maszyna.dlugosc[nastepny_przestoj];			//ustawiamy czas rozpoczêcia operacji od pocz¹tku bazuj¹c na czasie
					}														//poprzedniej operacji
					nastepny_przestoj++;
					czas += maszyna.dlugosc[nastepny_przestoj] + 0.3*uszeregowanie[i]->czas; //tylko 0.3 bo resztê dodajemy póŸniej
				}
				else						//czas siê zgadza
					uszeregowanie[i]->begin = czas;					//tu to samo tylko nie dodajemy d³ugoœci przestoju
			}
			if(uszeregowanie[i]->numer == 1) {						//sprawdzamy czy nastêpna operacja nie zaczyna siê za wczeœnie
				Operacja *nastepna = uszeregowanie[i]->parent->operacje[2];
				if ( nastepna->begin >= czas + uszeregowanie[i]->czas )		
					return false;									//je¿eli tak to giñ
			}
		}
		czas += uszeregowanie[i]->czas;								//przesuwamy kwant czasu o d³ugoœæ operacji
	}
	return true;
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
	*			-próba zamiany kolejnych s¹siadów tej operacji z lewej i z prawej
	*			-sprawdzanie czy s¹siedzi znajduj¹ siê w granicach uszeregowania
	*			-wsadzenie póŸniejszej operacji na wczeœniejsze miejsce
	*			-przeliczenie wszysktich operacji nastêpuj¹cych po tej wczeœniejszej (ju¿ przestawionej), a¿ do odkrycia miejsca startowego operacji póŸniejszej
	*			-sprawdzenie czy wczeœniejsza operacja mo¿e wejœæ na póŸniejsze miejsce
	*			-je¿eli nie mo¿e to kontynuujemy pêtle zgodnie ze wzorem (n to numer zapychacza): n-1,n+1; n-1,n+2, n-2,n+1, n-2,n+2 itd...
	*			-kontynuowanie pêtli póki nie osi¹gniemy oczekiwanej poprawy (podaæ jako argument?)
	*			-po nieudanej probie zmieniamy wartosc na false w tablicy mozliwosci pracy z danym przestojem
	*	-zapisywanie najlepszego uszeregowania do wyniku

	petle:
		- z czasem
		- tak dlugo az nie poprawimy najgorszej maszyny (bedzie inna najgorsza)
		- z zapychaczami
		- z przestojami

	***********/


	
	
	
	vector <Operacja*> zadania;														// wektor do fukcji sortowanie 
	Maszyna* maszyna;																// wskaznik na dana maszyne
	int granica=tablica[0] , optimum=tablica[1];									// TABLICA pierwszy element to czas uszeregowania algorytmu losowego, a drugi to optimum ponizej ktorego na pewno nie zejdziemy



//	while (granica > optimum) {														// petla
	int przestoj[3] = {-2,-2,-2};													// [0]-> nr_operacji na ktorej jest przestoj	[1]-> wartosc kary dla tej oepracji		[2]-> nr_przestoju z kara;
	int pozostaly_czas = -2;														// jesli -2 to oznacza blad    wyzej tez tak jest
	int nr_maszyny = ktora_maszyna(generator);										// wybieramy najmniej zawalona maszyne
	maszyna = generator.maszyny[nr_maszyny];										// i przypisujemy na nia wskaznik
	int max_zap = max_zapychacz(maszyna->uszeregowanie);							// najdluzszy zapychacza na tej maszynie

	operacja_z_max_kara(*maszyna, przestoj);										// zwraca w przestoj[3] kolejno: numer operacji W USZEREGOWANIU, na której traci siê najwiêcej na przestoju; wartosc kary dla tej oepracji;	nr_przestoju z kara;
	if (przestoj[1] >= 0 )															// sprawdzamy czy istnieje przestoj z kara
		pozostaly_czas = czas_do_przestoju(*maszyna, przestoj[2]);					//jesli tak to sprawdzamy jaki mamy czas do tego przestoju

	cout << " Maszyna: " << nr_maszyny << ", liczba zapychaczy: " << liczba_zapychaczy(maszyna->uszeregowanie) <<", CZAS zapychaczy: " << czas_zapychaczy(maszyna->uszeregowanie) << endl << endl;
	cout << " wartosc kary dla tej operacji to: " << przestoj[1] << endl;
	cout << " MAX zapychacz ma wartosc: " << max_zap << endl << endl;



	if (!mozna_zamienic(2,3, *maszyna, granica))
		cout << endl << "NIE MOZNA ZAMIENIC" << endl << endl;

	
//////          zapychacz vs przestoj           //////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
/*
	if ( max_zap >= przestoj[1] )																// JESLI ZAPYCHACZ JEST WIEKSZY OD KARY 
	{	// ZAPYCHACZE


//		// zmiana zapychacza!

		int miejsce = miejsce_w_uszer(max_zap, *maszyna);

		bool zamieniono=false;
		for (int i=miejsce-1; i>=0; i--){
			for (int j=miejsce+1; j<maszyna->uszeregowanie.size();j++)
				if (maszyna->uszeregowanie[j]->numer != 98)
					if (mozna_zamienic(i,j, *maszyna, granica)){
						cout << endl << "ZAMIENIONO" << endl << endl;
						zamieniono=true;
					}
			if (zamieniono==true)
				break;
		}

	
	}
		else 																					// JESLI KARA JEST WIEKSZA OD ZAPYCHACZA 
	{	 // PRZESTOJE											
		
		cout << " Nr operacji DO POPRAWY w  uszeregowaniu to: " << przestoj[0]+1 << endl;
		cout << " nr_przestoju z kara to: " << przestoj[2]+1<< endl;
		cout << " Pozostaly czas to: " << pozostaly_czas << endl;


//		//zmiana przestoju !!!

		bool zamieniono=false;
		for (int i=(maszyna->uszeregowanie.size()-1); i>przestoj[0]; i--){
			if (maszyna->uszeregowanie[i] < maszyna->uszeregowanie[przestoj[0]])
				if (mozna_zamienic(przestoj[0],i, *maszyna, granica)){
						cout << endl << "ZAMIENIONO" << endl << endl;
						zamieniono=true;
					}		
			if (zamieniono==true)
				break;
		}

	}
*/

	// wybor najlepszego
	return 0;
}