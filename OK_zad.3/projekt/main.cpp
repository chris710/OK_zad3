#include "main.h"

/*		MAIN		*/

/**************
		TODO List		
*	wykona� pomiary czasu dla obu algorytm�w
*
***************/


int main()
{

	srand(time(NULL));


	int nZadan = liczba_zadan();
	Generator generator(nZadan);
	cout << "======== ZADANIE LOSOWANIE ========\n\n";


	interfejs(generator);


	cout << "\n\nNacisnij klawisz, aby zakonczyc"; cin.get(); cin.get();
}

