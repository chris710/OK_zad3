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

bool czy_przestoj(const Maszyna & maszyna, const Operacja & operacja, int &czas, int &przestoj){
	bool flag=false;
	int przypuszczalny=czas+operacja.czas;
	for (int i=0; i<maszyna.rozpoczecie.size();i++)
		if (czas<maszyna.rozpoczecie[i] && przypuszczalny>maszyna.rozpoczecie[i]){
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

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////////////////////////////////            ALGORYTM SJF            ///////////////////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void algorytmSJF(const Generator& generator)
{
	vector<Zadanie*> zadania = generator.zadania;			//tymczasowa tablica do usuwania zadañ
	Maszyna* maszyna;										//wskaŸnik na preferowan¹ maszynê
	vector<int*> dlugosci;						// do usuniecia
	obliczanie_dlugosci(dlugosci,zadania);		// do usuniecia
	cout << "=================" << endl ;
	for (int  i=0; i< dlugosci.size();i++)		// do usuniecia
		cout << "dl=" << *dlugosci[i] << "\tGOT="<< generator.zadania[i]->delay << endl;			
	cout << "=================" << endl ;		// do usuniecia
	for (int i=0;i<3;i++)
		cout << "przestoj o= " << generator.maszyny[i]->rozpoczecie[0] << "\t i o dlugosci= " << generator.maszyny[i]->dlugosc[0] << endl << "=================" << endl;
	Operacja * zap = new Operacja(1,98,NULL,98);				//operacja zapychacz
	Operacja * przest = new Operacja(1,48,NULL,48);				//operacja zapychacz
	sort(zadania.begin(), zadania.end(), rosnaco);			//sortowanie tablicy po czasach trwania calego zadania
	int nrZAD=-1;											//zadanie do wykonania
	int preferred, przestoj=0;											//preferowana maszyna
	int kwantCZASU[3]={0,0,0};


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/	
	
	while (zadania.size() != 0)
	{														
		int a = czas_uszeregowania(generator,0);			//wybieramy najmniej zawalon¹ maszynê
		int b = czas_uszeregowania(generator,1);
		int c = czas_uszeregowania(generator,2);
		//cout << "A=" <<a<< endl;
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
				//cout << "czas=" << kwantCZASU[preferred]<< endl;
				if (czy_przestoj(*maszyna, *zadania[nrZAD]->operacje[0],kwantCZASU[preferred],przestoj)){
						int nowy_czas = ceil(zadania[nrZAD]->operacje[0]->czas*0.3);
						generator.maszyny[preferred]->uszeregowanie.push_back(zadania[nrZAD]->operacje[0]);
						Operacja * przest = new Operacja(generator.maszyny[preferred]->dlugosc[przestoj],48,NULL,48);
						generator.maszyny[preferred]->uszeregowanie.push_back(przest);
						Operacja * przedluzenie = new Operacja(nowy_czas,0,NULL,-nrZAD);
						generator.maszyny[preferred]->uszeregowanie.push_back(przedluzenie);
				} else {
				kwantCZASU[preferred]+=zadania[nrZAD]->operacje[0]->czas;
				generator.maszyny[preferred]->uszeregowanie.push_back(zadania[nrZAD]->operacje[0]);		//wtykamy operacjê do uszeregowania
				}
				zadania[nrZAD]->operacje[0]->maszyna = generator.maszyny[preferred];					//ustawiamy gdzie jest dana operacja
				zadania[nrZAD]->operacje[0]->done = true;												//okreœlamy operacjê jako wykonan¹
				zadania.erase( zadania.begin()+nrZAD); 
				break;															//wychodzimy z pêtli, szukamy najmniej zawalonej maszyny
			}}


			if (nrZAD < (zadania.size()-1))
				nrZAD++;
			else{
				nrZAD=0;
				maszyna->uszeregowanie.push_back(zap);		//wpychamy zapychacz
				kwantCZASU[preferred]++;
				//wybieramy najmniej zawalon¹ maszynê
				int a = czas_uszeregowania(generator,0);
				int b = czas_uszeregowania(generator,1);
				int c = czas_uszeregowania(generator,2);
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
	for (int i=0; i<3; i++){
		generator.czysc(*generator.maszyny[i]);
	//	laczenie(generator.maszyny[i]->uszeregowanie);		
	}
	int dlugosc = 0, dlugoscRealna = 0;	//do obliczania w³aœciwej d³ugoœci uszeergowania
	for (int i=0; i<3; i++){
		cout << "NR " << i << " MASZYNA:" << endl<<"------"<<endl;
		for (int j=0; j<generator.maszyny[i]->uszeregowanie.size(); j++){
			cout << "OP = " << (generator.maszyny[i]->uszeregowanie[j]->numer)+1 
				 << "\t\tZAD = " << (generator.maszyny[i]->uszeregowanie[j]->nrZadania)+1 
				 << "\t\tCZAS = " << generator.maszyny[i]->uszeregowanie[j]->czas << endl;
	//dlugosc = generator.dlugosc(*generator.maszyny[i]);
	//dlugoscRealna = (dlugoscRealna > dlugosc) ? dlugoscRealna : dlugosc;
	}}
	
	cout<<"Szacowana optymalna dlugosc uszeregowania "<<(generator.dlugoscInstancji/9)<<endl;
	cout<<"Dlugosc rzeczywista generowana przez algorytm "<<dlugoscRealna<<endl;
	cout<<"Procent: "<<(float)dlugoscRealna/(generator.dlugoscInstancji/9)<<endl;
}