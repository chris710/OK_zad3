#include<iostream>
#include "generator.h"
#include<algorithm>	


////////////////////////////////////////////////////////
///	PLIK NAG£ÓWKOWY ALGORYTMU SYMULOWANEGO WY¯ARZANIA///
////////////////////////////////////////////////////////
/******************************************************
*				PROJEKT/UWAGI/INFORMACJE
*	[INPROG] (?) jakie s¹ niezbêdne elementy algorytmu
		-wektor/tablica "miejsc potencjalnej poprawy"
		-zmienna przechowywuj¹ca najlepszy wynik
		-"temperatura" oraz wspó³czynnik jej obni¿ania 
			(po³¹czyæ jakoœ ten wspó³czynnik z tolerancj¹ na marnowany czas na przestojach?)
		-
*	[FIXED] (?) w jaki sposób go zaimplementowaæ
		[]Patrz poni¿ej
*	- kroki algorytmu (dostosowaæ?): 
		- znajdŸ miejsca gdzie mo¿na poprawiæ wynik
			"miejca potencjalnej poprawy"
		a) wybór losowego miejsca startowego (czyli 
			zamiany w takim losowym miejscu poprawy)
		b) przyjêcie Tmax(albo naszego odpowiednika) 
			co pewnie oznacza czas uszeregowania przed
			wy¿arzaniem
		c) wyznaczenie d³ugoœci uszeregowania w miejscu 
			startowym
		d) znalezienie miejsca(?) odleg³ego od punktu
			startowego o dok³adnoœæ wy¿arzania (T)
		e) wyznaczenie d³ugoœci uszeregowania dla tego 
			miejsca
		f) sprawdzamy czy ta d³ugoœæ uszeregowania jest
			mniejsza ni¿ zadana temperatura
		g) je¿eli tak to zapisujemy lepszy wynik do 
			zmiennej i losowo wybieramy czy zmieniæ
			uszeregowanie czy pozostaæ przy starym
		h) zmniejszenie "temperatury" (u nas d³ugoœci 
			uszeregowania)
		i) powtarzamy
*	[FIXED] (?) czym jest "miejsce startowe"?
		[]Miejsce startowe to pocz¹tkowe uszeregowanie operacji (za pomoc¹ algorytmu losowego)
*	[FIXED] (?) w jaki sposób wyznaczaæ s¹siednie uszeregowania
		[]Dziêki przestawianiu operacji wyznaczonych przez s¹siednie "miejsca potencjalnej poprawy"

******************************************************/
///////////////////////////////////////////////////////
/******************************************************
*						TODO LIST
*	[FIXED] klasa wy¿arzania(czy warto?)
		[]Nie, algorytm opiera siê na procedurach
*	[INPROG] metody/procedury (które potrzebne?) (lista gotowa?)
		[]Patrz poni¿ej
*	-weryfikacja i pomiar czasu 
		-uœrednianie co najmniej 3-krotne
		-pamiêtaj o automatyzacji testów!
*	-prezentacja wyników (którymi parametrami badamy?)(co najmniej 5)
		-wyznaczenie optymalnego czasu wy¿arzania (wykres)
		-wykres z³o¿onoœci algorytmu w zale¿noœci od d³ugoœci instancji(czyli iloœci zadañ)
			(!opcjonalne/trudne, bo trzeba by liczyæ tak d³ugo a¿ algorytm nie zejdzie 
			poni¿ej pewnego pu³apu a nie jak normalnie, puœciæ na wyznaczony z góry czas)
		-zale¿noœæ poprawy (stosunku uszeregowania poprawionego do pocz¹tkowego) od d³ugoœci zadañ
		-zale¿noœæ poprawy od iloœci zadañ (po³¹czyæ te 2?)
		-zale¿noœæ poprawy wyników od d³ugoœci przestojów
		-zale¿noœæ poprawy wyników od iloœci przestojów (po³¹czyæ te 2?)
******************************************************/

//		kolumna DONE		ZREZYGNOWALEM Z WIELKICH OPISOW
//=========================================================================
//		***					---	glowny algorytm
void wyrzazanie(const Generator& generator, int tablica[]);									
	
//	[DONE]		wybiera maszyne do poprawy (z najd³u¿szym uszeregowaniem)
int ktora_maszyna(const Generator& generator);									

//	[DONE]		podaje wartosc liczbowa kary na n-tym przestoju
int wartosc_kary(const Maszyna & maszyna,			//maszyna na której znajduje siê przestój
				int nr_przestoju);					//numer przestoju
	
//	[DONE]		czas pomiedzy koncem zadania poprzedzaj¹cego przestój a tym przestojem
int czas_do_przestoju(const Maszyna & maszyna,		//maszyna z przestojem
					int nr_przestoju);				//numer przestoju

//	[DONE]		zwraca numer operacji W USZEREGOWANIU, na której traci siê najwiêcej na przestoju
int max_kara_od_przestoju(const Maszyna & maszyna);								

//	[STUB]		sprawdza czy mozna zamienic dane operacje 
bool czy_mozna(int zad_1,							//zadanie pierwsze
				int zad_2,							//zadanie drugie
				int nr_maszyny,						//nr maszyny
				const Generator& generator);		//generator z danymi

//	[DONE]		zamienia 2 operacje (inf. dod.) na danej maszynie jedna operacja zadania)
void zamiana(int zad_1,								//zadanie pierwsze
			int zad_2,								//zadanie drugie
			Maszyna & maszyna,						//maszyna, na której zamieniamy operacje
			Generator& generator);

//	[DONE]		fajna statystyka //moze sie przydaæ do poczatkowej optymalizacji
int liczba_zapychaczy(vector<Operacja*> & uszeregowanie); 

//	[]			liczy laczny czas wszystkich zapychaczy na maszynie
int czas_zapychaczy(vector<Operacja*> & uszeregowanie); 

//	[STUB]		ustawienie zadan po zamianie
void obliczenie_uszeregowania(Maszyna & maszyna);			

//	[DONE]	podaje wynik czasowy uszeregowania 
int czas_uszeregowania(vector<Operacja*> & uszeregowanie);	//badane uszeregowanie

//	przydatne ?			posortowane nr zadan wedlug czasu trwania operacji w uszeregowaniu na danej maszynie
void sortowanie(vector<Operacja*> & uszeregowanie,	//	uszeregowanie na danej maszynie
				vector<int*> & zadania);			//  vector z posortowanymi numerami zadan 







