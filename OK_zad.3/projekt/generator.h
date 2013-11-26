#ifndef GENERATOR_H
#define GENERATOR_H



/**************
		TODO List
I. Generator 
[DONE] Interfejs w konsoli 
[DONE] Funkcja generuj�ca liczby losowe 
[DONE] Generowanie instancji problemu od 50 do n (ilo�� zada�) 
[DONE] Generowanie 3 opcji d�ugo�ci zada� - od 1 do 20 - od 1 do 100 (200) - mieszane, np. po�owa zada� od 1 do 20, po�owa od 1 do 200, itd. 
[DONE] Generowanie d�ugo�ci i ilo�ci przestoj�w (d�ugo�� od 5 do 200) 
[DONE] Generowanie miejsc przestoj�w dla wszystkich maszyn 
* Eksport do pliku .txt 
[DONE] Optymalizacja generowanych wynik�w (limiter)
***************/

#include<iostream>
#include<fstream>			//do operacji na plikach
#include<time.h>			//do liczb losowych

#include "zadanie.h"		//do generowania danych
#include "maszyna.h"		//do generowania przestoj�w
#include "operacja.h"		//do sprawdzania poprawno�ci



/// Klasa generatora
class Generator
{
public:
	//TODO pola generatora
	int liczbaZadan;			//rozmiar instancji
	int dlugoscInstancji;		//d�ugo�� wszystkich zada� i przestoj�w
	vector<Zadanie*> zadania;	//wektor zawieraj�cy wszystkie zadania
	vector<Maszyna*> maszyny;	//wektor zawieraj�cy wszystkie maszyny


	//TODO konstruktory
	/********
	*	@Konstruktor
	*	@Argumenty
	*		int nZadan	-	liczba zada� do wygenerowania
	********/
	Generator(int nZadan);


	//TODO destruktor


	//TODO metody


	/********
	*	@ generujZadanie
	*		Funkcja generuj�ca d�ugo�ci operacji poszczeg�lnego zadania
	*	@Argumenty:	
	*		int minDlugosc	-	minimalna d�ugo�� operacji
	*		int maxDlugosc	-	maksymalna d�ugo�� operacji zadania
	*		int delay		-	minimalny czas przed wykonaniem pierwszej operacji zadania	(czas gotowo�ci)
	*	@Zwraca:
	*		nic-------Zadanie	Result	-	objekt klasy	Zadanie	, zawieraj�cy tablic� 3 podklas		Operacja	, z wygenerowanymi danymi
	*							spe�niaj�cymi kryteria podane w argumentach funkcji
	*********/
	void generujZadanie(int minDlugosc, int maxDlugosc, int delay, int nrZad);


	/********
	*	@ generujMaszyne
	*		Funkcja generuj�ca przestoje w maszynie
	*	@Argumenty:
	*		int nPrzestojowMin/Max	-	maksymalna/minimalna liczba przestoj�w w maszynie
	*		int czasPrzestojow		-	maksymalny czas trwania przestoj�w
	*	@Zwraca:
	*		Maszyna Result	-	objekt klasy	Maszyna	,	z tablicami		rozpoczecie i	dlugosc	z wygenerowanymi losowo danymi
	********/
	Maszyna generujMaszyne(int nPrzestojowMin, int nPrzestojowMax, int czasPrzestojow);


	/********
	*	@ czyWejdzie
	*		Funkcja sprawdzaj�ca, czy operacja mo�e zosta� umieszczona w maszynie bez kolizji z przestojem maszyny
	*	@Argumenty:
	*		Maszyna maszyna			-	maszyna, na kt�rej sprawdzamy czy jest miejsce
	*		Operacja operacja		-	operacja, kt�rej poprawno�� sprawdzamy
	*	@Zwraca:
	*		bool	-	czy operacja mo�e wej�� na nast�pne miejsce bez kolizji z przestojem maszyny
	********/
	bool czyWejdzie(const Maszyna & maszyna, const Operacja & operacja) const;


	/********
	*	@ czyMozna
	*		Funkcja sprawdzaj�ca, czy poprzednia operacja zadania zosta�a ju� uko�czona i mo�na spokojnie ju� doda� nast�pn� na dan� maszyn�
	*	@Argumenty:
	*		Operacja operacja		-	operacja, kt�rej poprawno�� sprawdzamy
	*		Maszyna maszyna			-	maszyna na kt�rej sprawdzamy miejsce
	*	@Zwraca:
	*		bool	-	czy operacja mo�e wej�� bo poprzednia zosta�a ju� uko�czona
	********/
	bool czyMozna(const Operacja & operacja, const Maszyna & maszyna) const;


	/**************
	*	@ dlugosc
	*		funkcja licz�ca obecn� d�ugo�� uszeregowania na danej maszynie
	*	@Argumenty
	*		Maszyna maszyna			-	maszyna na kt�rej liczymy obecn� d�ugo�� uszeregowania
	*	@Zwraca
	*		int		-	d�ugo�� uszeregowania
	**************/
	int dlugosc(const Maszyna & maszyna) const;


	/************
	*	@ getTime
	*		funkcja licz�ca czas zako�czenia si� operacji
	*	@Argumenty
	*		Operacja operacja		-	operacja, kt�rej czasu szukamy
	*	@Zwraca
	*		int		-	czas zako�czenia si� operacja
	**************/
	int getTime(const Operacja & operacja) const;


	/********
	*	@ czysc
	*		Funkcja usuwaj�ca czas oczekiwania z ko�ca uszeregowania
	*	@Argumenty:
	*		Maszyna maszyna			-	maszyna na kt�rej usuwamy �mieci
	*	@Zwraca:
	*		nic
	********/
	void czysc(Maszyna & maszyna) const;

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