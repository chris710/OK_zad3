#include "main.h"



/*		MAIN		*/

/**************
		TODO List		
*	wykonaæ pomiary czasu dla obu algorytmów
*
***************/
void zerwoanie(Generator genrator);
void algorytmLosowy(const Generator& generator,  int tablica[]);
void uszereguj(const Generator& generator, int tablica[]) ;

int main()
{
	srand(time(NULL));
	clock_t start;
    clock_t end;
    float czas;
    ofstream plik;

	//ofstream plik("plik.txt",ios::app);
	int tab[2] = {0, 0};
	
	int nZadan;					//			liczba_zadan();
	int nPrzestojow;			//			liczba_przestojow();
	cout << "Podaj liczbe zadan: ";
	cin >> nZadan;
	cout << endl << "Podaj liczbe przestojow: " ;
	cin >> nPrzestojow;
	cout << endl;

	cout<<"//////////////	GENEROWANIE ZADAN	///////////////////"<<endl;
	Generator generator = Generator(nZadan);
	interfejs(generator, nPrzestojow);

	//Generator generator = Generator();

	cout<<"\n//////////////	ALGORYTM LOSOWY	///////////////////"<<endl;	
	start=clock();
	algorytmLosowy2(generator, tab);
	//uszereguj(generator, tab);
	end=clock();
    czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyœwietlanie czasu
    cout<<"Czas: "<<czas<<endl;
	plik<<"Czas: "<<czas<<endl;
	//generator.wyswietl();

	cout << endl << endl;
	cout<<"//////////////	WYZARZANIE SYMULOWANE	///////////////////"<<endl;
	int krok=1;
	wyzarzanie(generator, tab, krok);
	//generator.wyswietl();

	cout << "Wynik poprzedni to: " << tab[1] << endl;

	
	
	
	
	//generator.zeruj();	
	cout << "\n\nNacisnij klawisz, aby zakonczyc"; cin.get();cin.get();
}

