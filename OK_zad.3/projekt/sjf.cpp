#include "sjf.h"
#include <cmath>

void obliczanie_dlugosci(vector<int*> &dlugosci, vector<Zadanie*> zadania){
	for (int i=0; i<zadania.size();i++){
		int suma=0;
		for(int j=0; j<3; j++)
			suma+=zadania[i]->operacje[j]->czas;
		dlugosci.push_back(new int(suma));
	}
}

bool rosnaco(Zadanie *const a, Zadanie *const b)
{
	int asuma=0, bsuma=0;
	for(int j=0; j<3; j++){
			asuma+=a->operacje[j]->czas;
			bsuma+=b->operacje[j]->czas;
	}
    return asuma < bsuma;
} 

void laczenie(vector<Operacja*> & uszeregowanie){
	
	for (int j=0; j<uszeregowanie.size(); j++){
		if (uszeregowanie[j]->numer>3)
			if(uszeregowanie[j+1]->numer > 3)
				{
				uszeregowanie[j+1]->czas ++;//= uszeregowanie[i+1]->czas;
				uszeregowanie.erase(uszeregowanie.begin()+j);
				}
	//j--;
	}


}


int czas_uszeregowania(Generator generator, int i){
	int suma=0;
	for (int j=0; j<generator.maszyny[i]->uszeregowanie.size(); j++)
				suma+= generator.maszyny[i]->uszeregowanie[j]->czas ;
	return suma;
}

bool rozpoczecie_przestoju(const Maszyna & maszyna, int &czas, int &przestoj){
	bool flag=false;
	//int przypuszczalny=czas+operacja.czas;
	for (int i=0; i<maszyna.rozpoczecie.size();i++)
		if (czas==maszyna.rozpoczecie[i]){
			przestoj=i;
			flag = true;
		}
	return flag;
	//cout << operacja.czas << endl;
}

bool czy_przestoj(const Maszyna & maszyna, const Operacja & operacja, int &czas, int &przestoj){
	bool flag=false;
	int przypuszczalny=czas+operacja.czas;
	for (int i=0; i<maszyna.rozpoczecie.size();i++)
		if (czas<maszyna.rozpoczecie[i] && przypuszczalny>maszyna.rozpoczecie[i]) {
			przestoj=i;
			flag = true;
		}
	return flag;
	//cout << operacja.czas << endl;
}

bool czy_juz_gotowy(int gotowosc, int czas){
	//cout << "\n got=" <<gotowosc << "\t x=" << x<< endl;
	if(gotowosc<=czas)
		return true;
	else
		return false;
}

void wybierz_maszyne (int &preferred)			//funkcja wybiera inn¹ woln¹ maszynê
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

int wybierz_maszyne1 (int maszyna1, int maszyna2)	//funkcja wybiera jedyn¹ woln¹ maszynê
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

bool czyMoge(const Operacja & operacja, int czas) 
{
	bool flag = true;
	Operacja *poprzednia = operacja.parent->operacje[operacja.numer-1];
	if(czas < poprzednia->begin)
		flag = false;

	return flag;
}

int optymalnaDlugosc(Generator generator){
	int x=generator.dlugoscInstancji;
	for (int i=0;i<3;i++)
	{
		int licznik=0;
		for (int j=0; j<generator.maszyny[i]->uszeregowanie.size();j++)
				if (generator.maszyny[i]->uszeregowanie[j]->numer==48)
					licznik++;
		if (licznik<generator.maszyny[i]->nPrzestojow)
			for(int k=0;k<(generator.maszyny[i]->nPrzestojow-licznik);k++)
				x-=generator.maszyny[i]->dlugosc[generator.maszyny[i]->nPrzestojow-1-k];
	}
	return (x/3);
}

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////            ALGORYTM SJF            ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void algorytmSJF(const Generator& generator)
{	ofstream plik("plik1.txt");
	vector<Zadanie*> zadania = generator.zadania;			//tymczasowa tablica do usuwania zadañ
	Maszyna* maszyna;										//wskaŸnik na preferowan¹ maszynê
	vector<int*> dlugosci;						// do usuniecia
	//obliczanie_dlugosci(dlugosci,zadania);		// do usuniecia
	//plik << "=================" << endl ;
	//for (int  i=0; i< dlugosci.size();i++)		// do usuniecia
	//	plik << "dl=" << *dlugosci[i] << "\tGOT="<< generator.zadania[i]->delay << endl;			
	//plik << "=================" << endl ;		// do usuniecia
	//for (int i=0;i<3;i++)
	//	cout << "przestoj o= " << generator.maszyny[i]->rozpoczecie[0] << "\t i o dlugosci= " << generator.maszyny[i]->dlugosc[0] << endl << "=================" << endl;
	Operacja * zap = new Operacja(1,98,NULL,98);				//operacja zapychacz
	Operacja * przest = new Operacja(1,48,NULL,48);				//operacja zapychacz
	sort(zadania.begin(), zadania.end(), rosnaco);			//sortowanie tablicy po czasach trwania calego zadania
	int nrZAD=-1;											//zadanie do wykonania
	int preferred, przestoj=0;											//preferowana maszyna
	int kwantCZASU[3]={0,0,0};


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/	
	
	while (zadania.size() != 0)
	{														
		int a = kwantCZASU[0];//czas_uszeregowania(generator,0);			//wybieramy najmniej zawalon¹ maszynê
		int b = kwantCZASU[1];//czas_uszeregowania(generator,1);
		int c = kwantCZASU[2];//czas_uszeregowania(generator,2);
		//cout << "A=" <<a<< "\tB="<< b<<"\tC=" << c << endl;
		//cout << "A=" <<kwantCZASU[0]<< "\tB="<< kwantCZASU[1] <<"\tC=" << kwantCZASU[2] << endl;
		if(a<=b && a<=c)
			preferred = 0;
		else if(b<=a && b<=c)
			preferred = 1;
		else
			preferred = 2;
		
		//cout << "ROZMIAR ZADANIA=" << zadania.size()-1 << endl;
		if (nrZAD < (zadania.size()-1))
			nrZAD++;
		else
			nrZAD=0;
		//cout << "maszyna=" << preferred << endl;

/**//**//**//**//**//**//**//**//**/

	while(true){
		maszyna=generator.maszyny[preferred];
		if (!zadania[nrZAD]->operacje[0]->done){
			if(czy_juz_gotowy(zadania[nrZAD]->delay, kwantCZASU[preferred]))					//wsadŸ pierwsze je¿eli jeszcze tego nie zrobi³eœ
			{	
				if(rozpoczecie_przestoju(*maszyna,kwantCZASU[preferred],przestoj)){
					Operacja * przest = new Operacja(generator.maszyny[preferred]->dlugosc[przestoj],48,NULL,48);
					generator.maszyny[preferred]->uszeregowanie.push_back(przest);
					kwantCZASU[preferred]+=generator.maszyny[preferred]->dlugosc[przestoj];
				}
				if (czy_przestoj(*maszyna, *zadania[nrZAD]->operacje[0],kwantCZASU[preferred],przestoj)){
						int nowy_czas = ceil(zadania[nrZAD]->operacje[0]->czas*0.3);
						generator.maszyny[preferred]->uszeregowanie.push_back(zadania[nrZAD]->operacje[0]);
						Operacja * przest = new Operacja(generator.maszyny[preferred]->dlugosc[przestoj],48,NULL,48);
						generator.maszyny[preferred]->uszeregowanie.push_back(przest);
						Operacja * przedluzenie = new Operacja(nowy_czas,0,NULL,((-1)*nrZAD));
						generator.maszyny[preferred]->uszeregowanie.push_back(przedluzenie);
						kwantCZASU[preferred]+=(zadania[nrZAD]->operacje[0]->czas+nowy_czas+generator.maszyny[preferred]->dlugosc[przestoj]);
				} else {
				kwantCZASU[preferred]+=zadania[nrZAD]->operacje[0]->czas;
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[nrZAD]->operacje[0]);		//wtykamy operacjê do uszeregowania
				}
				zadania[nrZAD]->operacje[0]->begin=kwantCZASU[preferred];
				zadania[nrZAD]->operacje[0]->maszyna = generator.maszyny[preferred];					//ustawiamy gdzie jest dana operacja
				zadania[nrZAD]->operacje[0]->done = true;												//okreœlamy operacjê jako wykonan¹
			break;																//wychodzimy z pêtli, szukamy najmniej zawalonej maszyny
			}}
		else if (!zadania[nrZAD]->operacje[1]->done ){
			//cout << zadania[nrZAD]->operacje[0]->maszyna << " == " << maszyna ;
			if(zadania[nrZAD]->operacje[0]->maszyna == maszyna)										//je¿eli maszyna jest ta sama co pierwszego zadania
				{	//cout << "ZAMIANA" ;																				//to j¹ zmieniamy na inn¹
					wybierz_maszyne(preferred);
					maszyna = generator.maszyny[preferred];
				}
			if (czyMoge(*zadania[nrZAD]->operacje[1],kwantCZASU[preferred])){
				if(rozpoczecie_przestoju(*maszyna,kwantCZASU[preferred],przestoj)){
					Operacja * przest = new Operacja(generator.maszyny[preferred]->dlugosc[przestoj],48,NULL,48);
					generator.maszyny[preferred]->uszeregowanie.push_back(przest);
					kwantCZASU[preferred]+=generator.maszyny[preferred]->dlugosc[przestoj];
				}
				if (czy_przestoj(*maszyna, *zadania[nrZAD]->operacje[1],kwantCZASU[preferred],przestoj)){
						int nowy_czas = ceil(zadania[nrZAD]->operacje[1]->czas*0.3);
						generator.maszyny[preferred]->uszeregowanie.push_back(zadania[nrZAD]->operacje[1]);
						Operacja * przest = new Operacja(generator.maszyny[preferred]->dlugosc[przestoj],48,NULL,48);
						generator.maszyny[preferred]->uszeregowanie.push_back(przest);
						Operacja * przedluzenie = new Operacja(nowy_czas,1,NULL,((-1)*nrZAD));
						generator.maszyny[preferred]->uszeregowanie.push_back(przedluzenie);
						kwantCZASU[preferred]+=(zadania[nrZAD]->operacje[1]->czas + nowy_czas + generator.maszyny[preferred]->dlugosc[przestoj]);
				} else {
						kwantCZASU[preferred]+=zadania[nrZAD]->operacje[1]->czas;
						generator.maszyny[preferred]->uszeregowanie.push_back(zadania[nrZAD]->operacje[1]);		//wtykamy operacjê do uszeregowania
				}
				zadania[nrZAD]->operacje[1]->begin=kwantCZASU[preferred];
				zadania[nrZAD]->operacje[1]->maszyna = generator.maszyny[preferred];					//ustawiamy gdzie jest dana operacja
				zadania[nrZAD]->operacje[1]->done = true;												//okreœlamy operacjê jako wykonan¹
				
				break;			
			}}
			else if (!zadania[nrZAD]->operacje[2]->done ){
			//cout << zadania[nrZAD]->operacje[0]->maszyna << " == " << maszyna ;
				if(zadania[nrZAD]->operacje[0]->maszyna == maszyna ||			//je¿eli operacja le¿y na maszynie na której by³a wykonana poprzednia op
					zadania[nrZAD]->operacje[1]->maszyna == maszyna)
					{
						preferred = wybierz_maszyne1(zadania[nrZAD]->operacje[0]->maszyna->numer, 
								zadania[nrZAD]->operacje[1]->maszyna->numer);		//
						maszyna = generator.maszyny[preferred];						//szukamy innej maszyny
					}
			if (czyMoge(*zadania[nrZAD]->operacje[2],kwantCZASU[preferred])){
				if(rozpoczecie_przestoju(*maszyna,kwantCZASU[preferred],przestoj)){
					Operacja * przest = new Operacja(generator.maszyny[preferred]->dlugosc[przestoj],48,NULL,48);
					generator.maszyny[preferred]->uszeregowanie.push_back(przest);
					kwantCZASU[preferred]+=generator.maszyny[preferred]->dlugosc[przestoj];
				}

				if (czy_przestoj(*maszyna, *zadania[nrZAD]->operacje[2],kwantCZASU[preferred],przestoj)){
						int nowy_czas = ceil(zadania[nrZAD]->operacje[2]->czas*0.3);
						generator.maszyny[preferred]->uszeregowanie.push_back(zadania[nrZAD]->operacje[1]);
						Operacja * przest = new Operacja(generator.maszyny[preferred]->dlugosc[przestoj],48,NULL,48);
						generator.maszyny[preferred]->uszeregowanie.push_back(przest);
						Operacja * przedluzenie = new Operacja(nowy_czas,2,NULL,((-1)*nrZAD));
						generator.maszyny[preferred]->uszeregowanie.push_back(przedluzenie);
						kwantCZASU[preferred]+=(zadania[nrZAD]->operacje[2]->czas + nowy_czas + generator.maszyny[preferred]->dlugosc[przestoj]);
				} else {
						kwantCZASU[preferred]+=zadania[nrZAD]->operacje[2]->czas;
						generator.maszyny[preferred]->uszeregowanie.push_back(zadania[nrZAD]->operacje[2]);		//wtykamy operacjê do uszeregowania
				}
				zadania[nrZAD]->operacje[2]->begin=kwantCZASU[preferred];
				zadania[nrZAD]->operacje[2]->maszyna = generator.maszyny[preferred];					//ustawiamy gdzie jest dana operacja
				zadania[nrZAD]->operacje[2]->done = true;												//okreœlamy operacjê jako wykonan¹
				zadania.erase( zadania.begin()+nrZAD); 
				break;			
			}}
		







			if (nrZAD < (zadania.size()-1))
				nrZAD++;
			else{
				nrZAD=0;
				if(rozpoczecie_przestoju(*maszyna,kwantCZASU[preferred],przestoj)){
						Operacja * przest = new Operacja(generator.maszyny[preferred]->dlugosc[przestoj],48,NULL,48);
						generator.maszyny[preferred]->uszeregowanie.push_back(przest);
						kwantCZASU[preferred]+=generator.maszyny[preferred]->dlugosc[przestoj];
					} else{ 
				maszyna->uszeregowanie.push_back(zap);		//wpychamy zapychacz
				kwantCZASU[preferred]++; }
				//wybieramy najmniej zawalon¹ maszynê
				int a = kwantCZASU[0];//czas_uszeregowania(generator,0);			//wybieramy najmniej zawalon¹ maszynê
				int b = kwantCZASU[1];//czas_uszeregowania(generator,1);
				int c = kwantCZASU[2];//czas_uszeregowania(generator,2);
				//cout << "A=" <<a<< endl;
				if(a<=b && a<=c)
					preferred = 0;
				else if(b<=a && b<=c)
					preferred = 1;
				else
					preferred = 2;
				}
		}


	}
	//wybierz_maszyne
	for (int i=0; i<3; i++){
		generator.czysc(*generator.maszyny[i]);
	//	laczenie(generator.maszyny[i]->uszeregowanie);		
	}
	int dlugosc = 0, dlugoscRealna = 0;	//do obliczania w³aœciwej d³ugoœci uszeergowania
	for (int i=0; i<3; i++){
	//	plik <<endl<< "NR " << i << " MASZYNA:" << endl<<"------"<<endl;
	//	for (int j=0; j<generator.maszyny[i]->uszeregowanie.size(); j++){
	//		plik << "OP = " << (generator.maszyny[i]->uszeregowanie[j]->numer)+1 
	//			 << "\t\tZAD = " << (generator.maszyny[i]->uszeregowanie[j]->nrZadania)+1 
	//			 << "\t\tCZAS = " << generator.maszyny[i]->uszeregowanie[j]->czas << endl;
	//	}
	dlugosc = czas_uszeregowania(generator, i);
	dlugoscRealna = (dlugoscRealna > dlugosc) ? dlugoscRealna : dlugosc;
	}
	int x=optymalnaDlugosc(generator);
	plik<<"//////////////	ALGORYTM SJF	///////////////////"<<endl;
	plik<<"Szacowana optymalna dlugosc uszeregowania "<< generator.dlugoscInstancji/3 <<endl;
	plik<<"Obliczona optymalna dlugosc uszeregowania "<< x <<endl;
	plik<<"Dlugosc rzeczywista generowana przez algorytm "<<dlugoscRealna<<endl;
	plik<<"Procent: "<<(float)dlugoscRealna/(x)<<endl;
}