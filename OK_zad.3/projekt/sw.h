#include<iostream>
#include "generator.h"


////////////////////////////////////////////////////////
///	PLIK NAG£ÓWKOWY ALGORYTMU SYMULOWANEGO WY¯ARZANIA///
////////////////////////////////////////////////////////
/******************************************************
*				PROJEKT/UWAGI/INFORMACJE
*	-(?) jakie s¹ niezbêdne elementy algorytmu
*	-(?) w jaki sposób go zaimplementowaæ
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
	-(?) czym jest "miejsce startowe"?
	-(?) w jaki sposób wyznaczaæ s¹siednie uszeregowania
*
*
******************************************************/
///////////////////////////////////////////////////////
/******************************************************
*						TODO LIST
*	-klasa wy¿arzania(czy warto?)
*	-metody/procedury (które potrzebne?)
		-sprawdzenie czy operacja pasuje w dane miejsce
*	-weryfikacja i pomiar czasu
*	-prezentacja wyników (którymi parametrami badamy?)
*	-wyznaczenie maksymalnego czasu wy¿arzania (wykres)
******************************************************/

																				//		kolumna DONE		ZREZYGNOWALEM Z WIELKICH OPISOW
																				//=========================================================================
void wyrzazanie(const Generator& generator);									//		***					---	glowny algorytm
	
int ktora_maszyna(const Generator& generator);									//		DONE				wybiera maszyne do poprawy

int wartosc_kary(const Maszyna & maszyna, int nr_przestoju);					//		DONE				podaje wartosc liczbowa kary na n-tym przestoju
	
int czas_do_przestoju(const Maszyna & maszyna, int nr_przestoju);				//		DONE				czas pomiedzy koncem zadania poprzedniego a przestojem

bool czy_mozna(int zad_1, int zad_2, int nr_masz, const Generator& generator);	//							sprawdza czy mozna zamienic dane operacje 

void zamiana(int zad_1, int zad_2, vector<Operacja*> & uszeregowanie);			//							zamienia 2 operacje (inf. dod.) na danej maszynie jedna operacja zadania)

int liczba_zapychaczy(vector<Operacja*> & uszeregowanie); 						//		DONE				moze sie przydaæ do poczatkowej optymalizacji

vector<Operacja*> obliczenie_uszeregowania(const Maszyna & maszyna);			//							ustawienie zadan po zamianie

int czas_uszeregowania(vector<Operacja*> & uszeregowanie);						//		DONE				podaje wynik czasowy uszeregowania

void sortowanie(vector<Operacja*> & uszeregowanie, vector<int*> & zadania);		//		przydatne ?			posortowane nr zadan wedlug czasu trwania operacji w uszeregowaniu na danej maszynie







