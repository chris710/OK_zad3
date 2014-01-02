#include "main.h"
#include "sw.h"

/*		MAIN		*/

/**************
		TODO List		
*	wykonaæ pomiary czasu dla obu algorytmów
*
***************/
void zerwoanie(Generator genrator);
void algorytmLosowy(const Generator& generator,  int tablica[]);

int main()
{
	srand(time(NULL));
	clock_t start;
    clock_t end;
    float czas;
    ofstream plik;

	//ofstream plik("plik.txt",ios::app);

	int nZadan = liczba_zadan(), tab[2] = {0, 0};
	cout<<"//////////////	GENEROWANIE ZADAN	///////////////////"<<endl;
	Generator generator(nZadan);
	interfejs(generator);


	cout<<"//////////////	ALGORYTM LOSOWY	///////////////////"<<endl;
	
	start=clock();
	algorytmLosowy(generator, tab);
	end=clock();
    czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyœwietlanie czasu
    cout<<"Czas: "<<czas<<endl;
	plik<<"Czas: "<<czas<<endl;

	cout << endl << endl;
	cout<<"//////////////	WYRZAZANIE SYMULOWANE	///////////////////"<<endl;
	wyzarzanie(generator, tab);

	//generator.zeruj();
	

	
	
	cout << "\n\nNacisnij klawisz, aby zakonczyc"; cin.get(); cin.get();
}

