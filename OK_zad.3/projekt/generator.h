#ifndef GENERATOR_H
#define GENERATOR_H

#include<iostream>
#include "zadanie.h"

/**************
		TODO List
I. Generator 
[DONE] Interfejs w konsoli 
[DONE] Funkcja generuj�ca liczby losowe 
* Generowanie instancji problemu od 50 do n (ilo�� zada�) 
* Generowanie 3 opcji d�ugo�ci zada� - od 1 do 20 - od 1 do 100 (200) - mieszane, np. po�owa zada� od 1 do 20, po�owa od 1 do 200, itd. 
* Generowanie d�ugo�ci i ilo�ci przestoj�w (d�ugo�� od 5 do 200) 
* Generowanie miejsc przestoj�w dla wszystkich maszyn 
* Eksport do pliku .txt 
* Optymalizacja generowanych wynik�w (limiter)
***************/

#include<fstream>			//do operacji na plikach
#include<time.h>			//do liczb losowych
#include "zadanie.h"		//do do 
#include "maszyna.h"		//do generowania przestoj�w



/// Klasa generatora
class Generator
{
public:
	//TODO pola generatora
	int liczbaZadan;		//rozmiar instancji


	//TODO konstruktory

	//TODO destruktor

	//TODO metody

	/********
	*	@ generujZadanie
	*		Funkcja generuj�ca d�ugo�ci operacji poszczeg�lnego zadania
	*	@Argumenty:	
	*		int minDlugosc	-	minimalna d�ugo�� operacji
	*		int maxDlugosc	-	maksymalna d�ugo�� operacji zadania
	*		int delay		-	minimalny czas przed wykonaniem pierwszej operacji zadania	
	*	@Zwraca:
	*		Zadanie	Result	-	objekt klasy	Zadanie	, zawieraj�cy tablic� 3 podklas		operacja	, z wygenerowanymi danymi
	*							spe�niaj�cymi kryteria podane w argumentach funkcji
	*********/
	Zadanie generujZadanie(int minDlugosc, int maxDlugosc, int delay);


	/********
	*	@ generujMaszyne
	*		Funkcja generuj�ca przestoje w maszynie
	*	@Argumenty:
	*		int nPrzestojow		-	liczba przestoj�w w maszynie
	*		int czasPrzestojow	-	maksymalny czas trwania przestoj�w
	*	@Zwraca
	*		Maszyna Result	-	objekt klasy	Maszyna	,	z tablicami		rozpoczecie i	dlugosc	z wygenerowanymi losowo danymi
	********/
	Maszyna generujMaszyne(int nPrzestojow, int czasPrzestojow);
};

/**************
*	@random
*		Funkcja losuj�ca liczby z przedzia�u
*	@Argumenty:
*		int min		-	dolny pr�g losowanego przedzia�u 
*		int max		-	g�ryny pr�g losowanego przedzia�u
*	@Zwraca:
*		int result	-	wylosowana liczba z przedzia�u
**************/
int random(int min, int max);
#endif