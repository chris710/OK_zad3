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
	cout << "Wybierz liczbe zadan: " ;
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
	cout << "\n======== GENERATOR ========\n\n";
	int czas_wyk=czas_wykonania(),liczba_zadan = generator.liczbaZadan, liczba_przest=1;
	int x,y,z;
	x=liczba_przestojow();
	y=przestojeMin(x);
	z=przestojeMax(x);
	//generujemy zadania
	for(int i = 0; i < generator.liczbaZadan; ++i)
		generator.generujZadanie(y,z,1);
	
	//generujemy przestoje dla 3 maszyn
	for(int i = 0; i<3; ++i)
	{
		generator.generujMaszyne(y,z,5);
	}

	cout <<"\n===========================\n\n";
	cout <<"Czas wykonania zadan: " << czas_wyk <<endl<<endl;;
	wyswietlZadania(generator);
	cout <<"Liczba przestjow: " << liczba_przest <<endl;
	wyswietlMaszyny(generator);

	cout <<"\n===========================\n\n";
}


void wyswietlZadania(const Generator& generator)
{
	Zadanie *zadanie;
	vector<Zadanie*> zadania = generator.zadania;
	vector<Zadanie*>::iterator it;
	for( it = zadania.begin(); it != zadania.end(); ++it)
	{
		zadanie = *it;
		cout<<"Czas gotowoœci:\t"<<zadanie->delay<<endl;
		cout<<"Czas operacji 1:\t"<<zadanie->operacje[0]->czas<<endl;
		cout<<"Czas operacji 2:\t"<<zadanie->operacje[1]->czas<<endl;
		cout<<"Czas operacji 3:\t"<<zadanie->operacje[2]->czas<<endl<<endl;
	}
	cout<<endl;
}



void wyswietlMaszyny(const Generator& generator)
{
	Maszyna *maszyna;
	vector<Maszyna*> maszyny = generator.maszyny;
	for( int i = 0; i < 3; ++i)
	{
		maszyna = maszyny[i];
		cout<<"Maszyna nr "<<i<<endl;
		cout<<"Liczba przestojow:\t"<<maszyna->nPrzestojow<<endl;
		for(int i = 0; i < maszyna->rozpoczecie.size(); ++i)
		{
			cout<<"Kiedy przestoj:\t"<<maszyna->rozpoczecie[i]<<endl;
			cout<<"Jak dlugo:\t"<<maszyna->dlugosc[i]<<endl;
		}
		cout<<endl;
	}
	cout<<endl;
}