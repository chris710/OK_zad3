#include "main.h"
#include "sjf.h"
/*		MAIN		*/

/**************
		TODO List		
*	wykona� pomiary czasu dla obu algorytm�w
*
***************/

void algorytmLosowy(const Generator& generator);

int main()
{
	srand(time(NULL));
	int nZadan = liczba_zadan();
	Generator generator(nZadan);
	interfejs(generator);
	algorytmLosowy(generator);
	//algorytmSJF(generator);


	cout << "\n\nNacisnij klawisz, aby zakonczyc"; cin.get(); cin.get();
}

