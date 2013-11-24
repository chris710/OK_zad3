#include "main.h"

/*		MAIN		*/

/**************
		TODO List		
*	wykonaæ pomiary czasu dla obu algorytmów
*
***************/


int main()
{
	srand(time(NULL));
	int nZadan = liczba_zadan();
	Generator generator(nZadan);
	interfejs(generator);


	cout << "\n\nNacisnij klawisz, aby zakonczyc"; cin.get(); cin.get();
}

