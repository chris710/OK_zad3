#include "interfejs.h"

/**************
		TODO List
*	dostosowaæ funkcje do nowych metod klas
*
*
**************/


int czas_wykonania()
{
	int wybor;
	cout << "Wybierz czas wykonania zadan: \n  1) od 1 do 20 \n  2) od 1 do 200 \n  3) mieszane" << endl;
	cin >> wybor;
	return wybor;
}

int liczba_przestojow()
{
	int wybor;
	cout << "Wybierz liczbe przestojow: \n  1) od 1 do 10 \n  2) od 10 do 50 \n  3) od 1 do 50" << endl;
	cin >> wybor;
	return wybor;
}


void interfejs(int &czas_wyk,int &liczba_przest, int &liczba_zadan)
{
	cout << "======== GENERATOR ========\n\n";
	czas_wyk=czas_wykonania();
	liczba_przest=liczba_przestojow();
	if (liczba_przest==1)
		liczba_przest=10;
	else if (liczba_przest==2)
		liczba_przest=40;
	else 
		liczba_przest=50;
	cout <<"\n===========================\n\n";
	cout <<"Czas wykonania zadan: " << czas_wyk <<endl;
	cout <<"Liczba przestjow: " << liczba_przest <<endl;
	cout << "Liczba zadan to: " ;
	cin >> liczba_zadan;
	cout <<"\n===========================\n\n";
}


void wyswietlZadanie(const Zadanie& zadanie)
{
	cout<<"Czas gotowoœci:\t"<<zadanie.delay<<endl;
	cout<<"Czas operacji 1:\t"<<zadanie.operacje[0]->czas<<endl;
	cout<<"Czas operacji 2:\t"<<zadanie.operacje[1]->czas<<endl;
	cout<<"Czas operacji 3:\t"<<zadanie.operacje[2]->czas<<endl<<endl;
}