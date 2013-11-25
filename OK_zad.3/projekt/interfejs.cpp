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
	cout << "Wybierz czas wykonania operacji: \n  1) od 1 do 20 \n  2) od 1 do 200 \n  3) mieszane" << endl;
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

int czasOpMin(int wybor)
{
	return 1;
}

int czasOpMax(int wybor)
{
	if (wybor==1)
		return 20;
	else if (wybor==2)
		return 200;
	else 
		return 100;
}


void interfejs(Generator &generator)
{
	cout << "\n======== GENERATOR ========\n\n";
	int liczba_zadan = generator.liczbaZadan;
	int x,y,z;

	//generujemy zadania
	x=czas_wykonania();
	y=czasOpMin(x);
	z=czasOpMax(x);
	int gotowosc=0;
	for(int i = 0; i < generator.liczbaZadan; ++i){
		generator.generujZadanie(y,z,gotowosc);
		gotowosc+=10;
	}

	//generujemy przestoje dla 3 maszyn
	x=liczba_przestojow();
	y=przestojeMin(x);
	z=przestojeMax(x);
	int czasPrzestojow=200;
	for(int i = 0; i<3; ++i)
			generator.generujMaszyne(y,z,czasPrzestojow);
	
	cout <<"\n===========================\n\n";
	cout <<"OPCJA czasu wykonania zadan: " << generator.dlugoscInstancji <<endl<<endl;;
	wyswietlZadania(generator);
	//cout <<"OPCJA Liczba przestjow: " << liczba_przest <<endl;
	//wyswietlMaszyny(generator);

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
		cout<<"Czas gotowosci:\t"<<zadanie->delay<<endl;
		cout<<"Czas operacji "<<zadanie->operacje[0]->numer<<":\t"<<zadanie->operacje[0]->czas<<endl;
		cout<<"Czas operacji "<<zadanie->operacje[1]->numer<<":\t"<<zadanie->operacje[1]->czas<<endl;
		cout<<"Czas operacji "<<zadanie->operacje[2]->numer<<":\t"<<zadanie->operacje[2]->czas<<endl<<endl;
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