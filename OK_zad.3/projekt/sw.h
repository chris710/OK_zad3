#include<iostream>
#include "generator.h"
#include<algorithm>	
#include<time.h>            //do liczb pseudolosowych


////////////////////////////////////////////////////////
///	PLIK NAG��WKOWY ALGORYTMU SYMULOWANEGO WY�ARZANIA///
////////////////////////////////////////////////////////
/******************************************************
*				PROJEKT/UWAGI/INFORMACJE
*	[INPROG] (?) jakie s� niezb�dne elementy algorytmu
		-wektor/tablica "miejsc potencjalnej poprawy"
		-zmienna przechowywuj�ca najlepszy wynik
		-"temperatura" oraz wsp�czynnik jej obni�ania 
			(po��czy� jako� ten wsp�czynnik z tolerancj� na marnowany czas na przestojach?)
		-
*	[FIXED] (?) w jaki spos�b go zaimplementowa�
		[]Patrz poni�ej
*	- kroki algorytmu (dostosowa�?): 
		- znajd� miejsca gdzie mo�na poprawi� wynik
			"miejca potencjalnej poprawy"
		a) wyb�r losowego miejsca startowego (czyli 
			zamiany w takim losowym miejscu poprawy)
		b) przyj�cie Tmax(albo naszego odpowiednika) 
			co pewnie oznacza czas uszeregowania przed
			wy�arzaniem
		c) wyznaczenie d�ugo�ci uszeregowania w miejscu 
			startowym
		d) znalezienie miejsca(?) odleg�ego od punktu
			startowego o dok�adno�� wy�arzania (T)
		e) wyznaczenie d�ugo�ci uszeregowania dla tego 
			miejsca
		f) sprawdzamy czy ta d�ugo�� uszeregowania jest
			mniejsza ni� zadana temperatura
		g) je�eli tak to zapisujemy lepszy wynik do 
			zmiennej i losowo wybieramy czy zmieni�
			uszeregowanie czy pozosta� przy starym
		h) zmniejszenie "temperatury" (u nas d�ugo�ci 
			uszeregowania)
		i) powtarzamy
*	[FIXED] (?) czym jest "miejsce startowe"?
		[]Miejsce startowe to pocz�tkowe uszeregowanie operacji (za pomoc� algorytmu losowego)
*	[FIXED] (?) w jaki spos�b wyznacza� s�siednie uszeregowania
		[]Dzi�ki przestawianiu operacji wyznaczonych przez s�siednie "miejsca potencjalnej poprawy"

******************************************************/
///////////////////////////////////////////////////////
/******************************************************
*						TODO LIST
*	[FIXED] klasa wy�arzania(czy warto?)
		[]Nie, algorytm opiera si� na procedurach
*	[INPROG] metody/procedury (kt�re potrzebne?) (lista gotowa?)
		[]Patrz poni�ej
*	-weryfikacja i pomiar czasu 
		-u�rednianie co najmniej 3-krotne
		-pami�taj o automatyzacji test�w!
*	-prezentacja wynik�w (kt�rymi parametrami badamy?)(co najmniej 5)
		-wyznaczenie optymalnego czasu wy�arzania (wykres)
		-wykres z�o�ono�ci algorytmu w zale�no�ci od d�ugo�ci instancji(czyli ilo�ci zada�)
			(!opcjonalne/trudne, bo trzeba by liczy� tak d�ugo a� algorytm nie zejdzie 
			poni�ej pewnego pu�apu a nie jak normalnie, pu�ci� na wyznaczony z g�ry czas)
		-zale�no�� ilo�ci/poprawy (stosunku uszeregowania poprawionego do pocz�tkowego) od d�ugo�ci zada�
		-zale�no�� poprawy wynik�w od d�ugo�ci/ilo�ci przestoj�w
		-zale�no�� czas�w/poprawy od krok�w zmniejszania temperatury
******************************************************/

//		kolumna DONE		ZREZYGNOWALEM Z WIELKICH OPISOW
//=========================================================================
//		***					---	glowny algorytm
int wyzarzanie(const Generator& generator,			//generator z danymi
				int tablica[],						//pierwszy element to czas uszeregowania algorytmu losowego, a drugi to optimum ponizej ktorego na pewno nie zejdziemy
				int krok);							//[TODO]OPISZ ARGUMENTY					
	
//	[DONE]		wybiera maszyne do poprawy (z najd�u�szym uszeregowaniem)
int ktora_maszyna(const Generator& generator);									

//	[DONE]		podaje wartosc liczbowa kary na n-tym przestoju
int wartosc_kary(const Maszyna & maszyna,			//maszyna na kt�rej znajduje si� przest�j
				int nr_przestoju);					//numer przestoju
	
//	[DONE]		czas pomiedzy koncem zadania poprzedzaj�cego przest�j a tym przestojem
int czas_do_przestoju(const Maszyna & maszyna,		//maszyna z przestojem
					int nr_przestoju);				//numer przestoju

//	[DONE]		zwraca numer operacji W USZEREGOWANIU, na kt�rej traci si� najwi�cej na przestoju
void operacja_z_max_kara(const Maszyna & maszyna, int przestoj[]);	

//	***[STUB]		zamienia 2 operacje (inf. dod.) na danej maszynie jedna operacja zadania)
void zamiana(	int aaa,										// operacja wczesniejsza
				int bbb,										// operacja pozniejsza
				vector<Operacja*> & kopia_uszeregowania );			// uszeregowanie, w kt�rym zamieniamy operacje

//	***[STUB]		sprawdza czy mozna zamienic dane operacje 
bool mozna_zamienic(int aaa, int bbb, Maszyna & maszyna, int temperatura) ;

//	***[]		wyznacza miesjce w uszeregowaniu oepracji danego zadania
int miejsce_w_uszer(int nr_ZAD);


//	[DONE]		fajna statystyka //moze sie przyda� do poczatkowej optymalizacji
int liczba_zapychaczy(vector<Operacja*> & uszeregowanie); 

//	[DONE]			liczy max czas przestoju na maszynie
int max_zapychacz(vector<Operacja*> & uszeregowanie);

//	[DONE]			liczy laczny czas wszystkich zapychaczy na maszynie
int czas_zapychaczy(vector<Operacja*> & uszeregowanie); 

//	[DONE]		ustawienie zadan po zamianie
void obliczenie_uszeregowania(vector<Operacja*> & uszeregowanie, Maszyna & maszyna);			

//	[DONE]	podaje wynik czasowy uszeregowania 
int czas_uszeregowania(vector<Operacja*> & uszeregowanie);	//badane uszeregowanie

//	[DONE]			posortowane nr zadan wedlug czasu trwania operacji w uszeregowaniu na danej maszynie
void sortowanie(vector<Operacja*> & uszeregowanie,	//	uszeregowanie na danej maszynie
				vector<int*> & zadania);			//  vector z posortowanymi numerami zadan 
//	[DONE]		sprawdza czy operacja w danym miejscu spe�nia warunki uszeregowania w job shopie
bool warunki(const Operacja & bbb,					//sprawdzana operacja
			int czas);								//sprawdzany czas, w kt�rym ma zacz�� si� operacja bbb
