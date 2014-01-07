#include "interfejs.h"




int liczba_zadan()
{
	int wybor;
	cout << "Wybierz liczbe zadan: " ;
	cin >> wybor;
	return wybor;
}


int liczba_przestojow()
{
	int wybor;
	cout << "Wybierz liczbe przestojow: " ;
	cin >> wybor;
	return wybor;
}




void interfejs(Generator &generator, int nPrzestojow)
{
	cout << "\n======== GENERATOR ========\n\n";
	int liczba_zadan = generator.liczbaZadan;
	int x,y,z;

	//generujemy zadania
	y=1;
	z=50;
	int gotowosc=0;
	for(int i = 0; i < generator.liczbaZadan; ++i){				//generowanie zadañ
		generator.generujZadanie(y,z,gotowosc,i);
		//generator.generujZadanie(5,5,2,i);			//TESTOWE
		gotowosc+=10;
	}

	//generujemy przestoje dla 3 maszyn
	x=nPrzestojow;
	int czasPrzestojow=100;

	generator.generujMaszyne(x,x,czasPrzestojow);
	//generator.generujMaszyne(2,2,2);			//TESTOWE
	
	//wyswietlZadania(generator);
	cout <<"\n===========================\n\n";
	cout <<"DLUGOSC INSTANCJI: " << generator.dlugoscInstancji <<endl<<endl;
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