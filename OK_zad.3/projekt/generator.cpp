#include "generator.h"

/*******
		TODO List
*	pouk³adaæ te œmieci z maina
*
********/


/*void maszyna_losowanie(int liczb maszyna m1, maszyna m2, maszyna m3){
	int odd,doo; a_przest,
	switch(liczba_przest){			// wybieram opje 
	case 10: //						// od 1do 10 s
		odd=1;
		doo=10;
		break;
	case 40: //
		odd=10;
		doo=50;
		break;
	case 50: //
		odd=1;
		doo=50;
		break;
	}
	int wynik;
	wynik=(rand()%(doo))+odd;
	for(int i=0;i<wynik;i++){
		m1.dlugosc[i]=(rand()%196)+5;
		m1.rozpoczecie[i]=rand()%100;
		//cout << "\t" << m1.dlugosc[i] << "\t" << m1.rozpoczecie[i] << endl;
	}

	cout << "\n\n";
	wynik=(rand()%(doo))+odd;
	for(int i=0;i<wynik;i++){
		m2.dlugosc[i]=(rand()%196)+5;
		m2.rozpoczecie[i]=rand()%100;
		//cout << "\t" << m2.dlugosc[i] << "\t" << m2.rozpoczecie[i] << endl;
	}

	cout << "\n\n";
	wynik=(rand()%(doo))+odd;
	for(int i=0;i<wynik;i++){
		m3.dlugosc[i]=(rand()%196)+5;
		m3.rozpoczecie[i]=rand()%100;
		//cout << "\t" << m3.dlugosc[i] << "\t" << m3.rozpoczecie[i] << endl;
	}
	
}

void zadanie_losowanie(int liczba_zadan, int czas_wyk, zadanie gotowosc, zadanie op1, zadanie op2, zadanie op3){
	// wykonanie 3 operacji (1-20;1-200;miesz) i gotowosc
	switch(czas_wyk){
	case 1: // 
		for (int i=0;i<liczba_zadan;i++){
			op1.numer[i]=(rand()%20)+1;
			op2.numer[i]=(rand()%20)+1;
			op3.numer[i]=(rand()%20)+1; 
		}
		break;
	
	case 2: //
		for (int i=0;i<liczba_zadan;i++){
			op1.numer[i]=(rand()%200)+1;
			op2.numer[i]=(rand()%200)+1;
			op3.numer[i]=(rand()%200)+1; 
		}
		break;
	
	case 3: //
		int mieszane;
		for (int i=0;i<liczba_zadan;i++){
			mieszane=rand()%2;
			if (mieszane==0){
				op1.numer[i]=(rand()%20)+1;
				op2.numer[i]=(rand()%20)+1;
				op3.numer[i]=(rand()%20)+1; 
			} else{
				op1.numer[i]=(rand()%200)+1;
				op2.numer[i]=(rand()%200)+1;
				op3.numer[i]=(rand()%200)+1; 
			}}
		break;
	}
	int suma=0;
	for (int i=0;i<liczba_zadan;i++){
		suma+=op1.numer[i];
		suma+=op2.numer[i];
		suma+=op3.numer[i];
	}
	suma/=3;
	for (int i=0;i<liczba_zadan;i++)
		gotowosc.numer[i]=rand()%suma;

}*/


Zadanie Generator::generujZadanie(int minDlugosc, int maxDlugosc, int delay)
{
	Zadanie* Result = new Zadanie();
	Result->delay = random(0,delay);
	Result->operacje[0] = new Operacja(random(minDlugosc, maxDlugosc));
	Result->operacje[1] = new Operacja(random(minDlugosc, maxDlugosc));
	Result->operacje[2] = new Operacja(random(minDlugosc, maxDlugosc));
	this->zadania.push_back(Result);
	return *Result;
}


Maszyna Generator::generujMaszyne(int nPrzestojow, int czasPrzestojow)
{
	Maszyna* Result = new Maszyna();
	for (int i = 0; i < nPrzestojow; ++i)
	{
		Result->dlugosc.push_back(random(0,czasPrzestojow));
	}
	//oszacowanie d³ugoœci instancji
	for(int i = 0; i<this->liczbaZadan; ++i)
	{
		for(int j=0; j<3; ++j)
			(this->dlugoscInstancji) += this->zadania[i]->operacje[j]->czas;
		for(int j = 0; j<Result->dlugosc.size(); ++j)
			this->dlugoscInstancji += Result->dlugosc[j];
	}

	//TODO znormalizuj czasy aby siê nie pierdoli³y
	//TODO zrób coœ aby siê nie nak³ada³y
	int przedzial = (this->dlugoscInstancji/3)/nPrzestojow;			//d³ugoœæ na jednej maszynie podzielona przez iloœæ przestojów
	for(int i = 1; i<=nPrzestojow; ++i)
	{
		Result->rozpoczecie.push_back(i*przedzial);
	}
	return *Result;
}


int random(int min, int max)
{
	int result, lower = max-min;
	result = rand()%lower + min;
	return result;
}