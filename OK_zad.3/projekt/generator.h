#ifndef GENERATOR_H
#define GENERATOR_H

#include<iostream>
#include "zadanie.h"

/**************
		TODO List
I. Generator 
[DONE] Interfejs w konsoli 
[DONE] Funkcja generuj¹ca liczby losowe 
* Generowanie instancji problemu od 50 do n (iloœæ zadañ) 
* Generowanie 3 opcji d³ugoœci zadañ - od 1 do 20 - od 1 do 100 (200) - mieszane, np. po³owa zadañ od 1 do 20, po³owa od 1 do 200, itd. 
* Generowanie d³ugoœci i iloœci przestojów (d³ugoœæ od 5 do 200) 
* Generowanie miejsc przestojów dla wszystkich maszyn 
* Eksport do pliku .txt 
* Optymalizacja generowanych wyników (limiter)
***************/

#include<fstream>			//do operacji na plikach
#include<time.h>			//do liczb losowych
#include "zadanie.h"		//do do 
#include "maszyna.h"		//do generowania przestojów



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
	*		Funkcja generuj¹ca d³ugoœci operacji poszczególnego zadania
	*	@Argumenty:	
	*		int minDlugosc	-	minimalna d³ugoœæ operacji
	*		int maxDlugosc	-	maksymalna d³ugoœæ operacji zadania
	*		int delay		-	minimalny czas przed wykonaniem pierwszej operacji zadania	
	*	@Zwraca:
	*		Zadanie	Result	-	objekt klasy	Zadanie	, zawieraj¹cy tablicê 3 podklas		operacja	, z wygenerowanymi danymi
	*							spe³niaj¹cymi kryteria podane w argumentach funkcji
	*********/
	Zadanie generujZadanie(int minDlugosc, int maxDlugosc, int delay);


	/********
	*	@ generujMaszyne
	*		Funkcja generuj¹ca przestoje w maszynie
	*	@Argumenty:
	*		int nPrzestojow		-	liczba przestojów w maszynie
	*		int czasPrzestojow	-	maksymalny czas trwania przestojów
	*	@Zwraca
	*		Maszyna Result	-	objekt klasy	Maszyna	,	z tablicami		rozpoczecie i	dlugosc	z wygenerowanymi losowo danymi
	********/
	Maszyna generujMaszyne(int nPrzestojow, int czasPrzestojow);
};

/**************
*	@random
*		Funkcja losuj¹ca liczby z przedzia³u
*	@Argumenty:
*		int min		-	dolny próg losowanego przedzia³u 
*		int max		-	góryny próg losowanego przedzia³u
*	@Zwraca:
*		int result	-	wylosowana liczba z przedzia³u
**************/
int random(int min, int max);
#endif