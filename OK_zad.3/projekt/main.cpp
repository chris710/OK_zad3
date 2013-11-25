#include "main.h"

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
	int nZadan = liczba_zadan();
	Generator generator(nZadan);
	interfejs(generator);
	algorytmLosowy(generator);


	cout << "\n\nNacisnij klawisz, aby zakonczyc"; cin.get(); cin.get();
}

