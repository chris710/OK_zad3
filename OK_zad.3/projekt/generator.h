#ifndef GENERATOR_H
#define GENERATOR_H

#include<iostream>
#include "zadanie.h"

/**************
		TODO List
I. Generator 
[DONE] 1) Interfejs w konsoli 
[DONE] 2) Funkcja generuj�ca liczby losowe 
3) Generowanie instancji problemu od 50 do n (ilo�� zada�) 
4) Generowanie 3 opcji d�ugo�ci zada� - od 1 do 20 - od 1 do 100 (200) - mieszane, np. po�owa zada� od 1 do 20, po�owa od 1 do 200, itd. 
5) Generowanie d�ugo�ci i ilo�ci przestoj�w (d�ugo�� od 5 do 200) 
6) Generowanie miejsc przestoj�w dla wszystkich maszyn 
7) Eksport do pliku .txt 
8) Optymalizacja generowanych wynik�w (limiter)
***************/

#include <fstream>			//do operacji na plikach
#include "zadanie.h"		//do do 
#include "maszyna.h"		//do generowania przestoj�w


/// Klasa generatora
class Generator
{
public:
	//TODO pola generatora
	int liczbaZadan;		//rozmiar instancji
	int liczbaPrzestojow;	//liczba przestoj�w
	int dlugoscZadan;		//opcja d�ugo�ci zada�
	int dlugoscPrzestojow;	//opcja d�ugo�ci przestoj�w


	//TODO konstruktory
	//TODO destruktor
	//TODO metody

	/********
	*	@ generujZadanie
	*		Funkcja generuj�ca d�ugo�ci operacji poszczeg�lnego zadania
	*	@Argumenty:	
	*		int maxDlugosc	-	maksymalna d�ugo�� operacji zadania
	*	@Zwraca:
	*		Zadanie	Result	-	objekt klasy	Zadanie	, zawieraj�cy tablic� 3 podklas		Proces	, z wygenerowanymi danymi
	*							spe�niaj�cymi kryteria podane w argumentach funkcji
	*********/
	Zadanie generujZadanie(int maxDlugosc);


};

#endif