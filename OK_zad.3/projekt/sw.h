#include<iostream>
#include "generator.h"


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
		-zale�no�� poprawy (stosunku uszeregowania poprawionego do pocz�tkowego) od d�ugo�ci zada�
		-zale�no�� poprawy od ilo�ci zada� (po��czy� te 2?)
		-zale�no�� poprawy wynik�w od d�ugo�ci przestoj�w
		-zale�no�� poprawy wynik�w od ilo�ci przestoj�w (po��czy� te 2?)
******************************************************/

																				//		kolumna DONE		ZREZYGNOWALEM Z WIELKICH OPISOW
																				//=========================================================================
void wyrzazanie(const Generator& generator);									//		***					---	glowny algorytm
	
int ktora_maszyna(const Generator& generator);									//		DONE				wybiera maszyne do poprawy (z najd�u�szym uszeregowaniem)

int wartosc_kary(const Maszyna & maszyna, int nr_przestoju);					//		DONE				podaje wartosc liczbowa kary na n-tym przestoju
	
int czas_do_przestoju(const Maszyna & maszyna, int nr_przestoju);				//		DONE				czas pomiedzy koncem zadania poprzedzaj�cego przest�j a tym przestojem

int max_kara_od_przestoju(const Maszyna & maszyna);								//							zwraca czas miejsca, gdzie traci si� najwi�cej na przestoju

bool czy_mozna(int zad_1, int zad_2, int nr_masz, const Generator& generator);	//							sprawdza czy mozna zamienic dane operacje 

void zamiana(int zad_1, int zad_2, vector<Operacja*> & uszeregowanie);			//							zamienia 2 operacje (inf. dod.) na danej maszynie jedna operacja zadania)

int liczba_zapychaczy(vector<Operacja*> & uszeregowanie); 						//		DONE				fajna statystyka //moze sie przyda� do poczatkowej optymalizacji

vector<Operacja*> obliczenie_uszeregowania(const Maszyna & maszyna);			//							ustawienie zadan po zamianie

int czas_uszeregowania(vector<Operacja*> & uszeregowanie);						//		DONE				podaje wynik czasowy uszeregowania (czemu nie podajemy maszyny?)

void sortowanie(vector<Operacja*> & uszeregowanie, vector<int*> & zadania);		//		przydatne ?			posortowane nr zadan wedlug czasu trwania operacji w uszeregowaniu na danej maszynie







