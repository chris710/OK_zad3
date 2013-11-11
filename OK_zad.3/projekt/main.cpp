#include<iostream>
#include<time.h>

//linkowanie plików projektu
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

