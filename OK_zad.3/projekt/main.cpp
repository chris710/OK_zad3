#include "main.h"

/*		MAIN		*/

/**************
		TODO List		
*
*
***************/


int main()
{

	srand(time(NULL));


	int nZadan = liczba_zadan();
	Generator generator(nZadan);
	cout << "======== ZADANIE LOSOWANIE ========\n\n";
	/*zadanie_losowanie(liczba_zadan, czas_wyk, gotowosc, op1, op2, op3);
	for(int i=0;i<liczba_zadan;i++)
		cout << gotowosc.numer[i] << "  | \t" << op1.numer[i] << "\t" << op2.numer[i] << "\t" << op3.numer[i] << endl;
		*/


	interfejs(generator);

	cout << "\n======== MASZYNA LOSOWANIE ========\n\n";
	//maszyna_losowanie(liczba_przest, m1, m2, m3);


	cout << "\n\nNacisnij klawisz, aby zakonczyc"; cin.get(); cin.get();
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

