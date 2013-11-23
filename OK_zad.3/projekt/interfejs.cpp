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


int liczba_zadan()
{
	int wybor;
	cout << "Wybierz liczbe zadan: " << endl;
	cin >> wybor;
	return wybor;
}


int przestojeMin(int wybor)
{
	if (wybor==2)
		return 10;
	else 
		return 1;
}

int przestojeMax(int wybor)
{
	if (wybor==1)
		return 10;
	else 
		return 50;
}


void interfejs(Generator &generator)
{
	cout << "======== GENERATOR ========\n\n";
	int czas_wyk=czas_wykonania(),liczba_zadan = generator.liczbaZadan, liczba_przest=1;
	int x,y,z;
	x=liczba_przestojow();
	y=przestojeMin(x);
	z=przestojeMax(x);
	generator.generujZadanie(y,z,1);
	cout <<"\n===========================\n\n";
	cout <<"Czas wykonania zadan: " << czas_wyk <<endl;
	cout <<"Liczba przestjow: " << liczba_przest <<endl;
	cout <<"\n===========================\n\n";
}


void wyswietlZadanie(const Zadanie& zadanie)
{
	cout<<"Czas gotowoœci:\t"<<zadanie.delay<<endl;
	cout<<"Czas operacji 1:\t"<<zadanie.operacje[0]->czas<<endl;
	cout<<"Czas operacji 2:\t"<<zadanie.operacje[1]->czas<<endl;
	cout<<"Czas operacji 3:\t"<<zadanie.operacje[2]->czas<<endl<<endl;
}
