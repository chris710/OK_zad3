#ifndef GENERATOR_H
#define GENERATOR_H

#include<iostream>
#include "zadanie.h"

/**************
		TODO List
I. Generator 
[DONE] 1) Interfejs w konsoli 
[DONE] 2) Funkcja generuj¹ca liczby losowe 
3) Generowanie instancji problemu od 50 do n (iloœæ zadañ) 
4) Generowanie 3 opcji d³ugoœci zadañ - od 1 do 20 - od 1 do 100 (200) - mieszane, np. po³owa zadañ od 1 do 20, po³owa od 1 do 200, itd. 
5) Generowanie d³ugoœci i iloœci przestojów (d³ugoœæ od 5 do 200) 
6) Generowanie miejsc przestojów dla wszystkich maszyn 
7) Eksport do pliku .txt 
8) Optymalizacja generowanych wyników (limiter)
***************/

#include <fstream>			//do operacji na plikach
#include "zadanie.h"		//do do 
#include "maszyna.h"		//do generowania przestojów


/// Klasa generatora
class Generator
{
public:
	//TODO pola generatora
	int liczbaZadan;		//rozmiar instancji
	int liczbaPrzestojow;	//liczba przestojów
	int dlugoscZadan;		//opcja d³ugoœci zadañ
	int dlugoscPrzestojow;	//opcja d³ugoœci przestojów


	//TODO konstruktory
	//TODO destruktor
	//TODO metody

	/********
	*	@ generujZadanie
	*		Funkcja generuj¹ca d³ugoœci operacji poszczególnego zadania
	*	@Argumenty:	
	*		int maxDlugosc	-	maksymalna d³ugoœæ operacji zadania
	*	@Zwraca:
	*		Zadanie	Result	-	objekt klasy	Zadanie	, zawieraj¹cy tablicê 3 podklas		Proces	, z wygenerowanymi danymi
	*							spe³niaj¹cymi kryteria podane w argumentach funkcji
	*********/
	Zadanie generujZadanie(int maxDlugosc);


};

#endif