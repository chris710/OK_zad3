#include<iostream>
#include<time.h>

//linkowanie plikó projektu
#include "naglowek1.h"
#include "maszyna.h"
#include "zadanie.h"
#include "generator.h"


using namespace std;



int main()
{
	int czas_wyk, liczba_przest, liczba_zadan;
	srand(time(NULL));
	interfejs(czas_wyk, liczba_przest, liczba_zadan);


	//////////////////////////////////////////
	zadanie gotowosc, op1,op2,op3;
	gotowosc.numer=new int[liczba_zadan];
	op1.numer=new int[liczba_zadan];
	op2.numer=new int[liczba_zadan];
	op3.numer=new int[liczba_zadan];

	maszyna m1, m2, m3;
	m1.dlugosc=new int[liczba_przest];
	m1.rozpoczecie=new int[liczba_przest];
	m2.dlugosc=new int[liczba_przest];
	m2.rozpoczecie=new int[liczba_przest];
	m3.dlugosc=new int[liczba_przest];
	m3.rozpoczecie=new int[liczba_przest];
	//////////////////////////////////////////

	cout << "======== ZADANIE LOSOWANIE ========\n\n";
	zadanie_losowanie(liczba_zadan, czas_wyk, gotowosc, op1, op2, op3);
	for(int i=0;i<liczba_zadan;i++)
		cout << gotowosc.numer[i] << "  | \t" << op1.numer[i] << "\t" << op2.numer[i] << "\t" << op3.numer[i] << endl;

	cout << "\n======== MASZYNA LOSOWANIE ========\n\n";
	maszyna_losowanie(liczba_przest, m1, m2, m3);


	cout << "\n\nNacisnij klawisz, aby zakonczyc"; cin.get(); cin.get();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

void maszyna_losowanie(int liczba_przest, maszyna m1, maszyna m2, maszyna m3){
	int odd,doo; 
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

}
