#include "main.h"
#include "sjf.h"
/*		MAIN		*/

/**************
		TODO List		
*	wykonaæ pomiary czasu dla obu algorytmów
*
***************/

void algorytmLosowy(const Generator& generator);

int main()
{
	srand(time(NULL));
	clock_t start;
    clock_t end;
    float czas;
    ofstream plik;

	//ofstream plik("plik.txt",ios::app);

	int nZadan = liczba_zadan();
	cout<<"//////////////	GENEROWANIE ZADAN	///////////////////"<<endl;
	Generator generator(nZadan);
	interfejs(generator);

	cout<<"//////////////	ALGORYTM LOSOWY	///////////////////"<<endl;
	//plik<<"//////////////	ALGORYTM LOSOWY	///////////////////"<<endl;
	start=clock();
	algorytmLosowy(generator);
	end=clock();
    czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyœwietlanie czasu
    cout<<"Czas: "<<czas<<endl;
	plik<<"Czas: "<<czas<<endl;
	/*
	cout<<"//////////////	ALGORYTM SJF	///////////////////"<<endl;
	//plik<<"//////////////	ALGORYTM SJF	///////////////////"<<endl;
	start=clock();
	algorytmSJF(generator);
	end=clock();
    czas=(float)(end-start)/CLOCKS_PER_SEC;     //wyœwietlanie czasu
    cout<<"Czas: "<<czas<<endl;
	plik<<"Czas: "<<czas<<endl;

	*/
	cout << "\n\nNacisnij klawisz, aby zakonczyc"; cin.get(); cin.get();
}

