#ifndef GENERATOR_H
#define GENERATOR_H



/**************
		TODO List
I. Generator 
[DONE] Interfejs w konsoli 
[DONE] Funkcja generuj¹ca liczby losowe 
[DONE] Generowanie instancji problemu od 50 do n (iloœæ zadañ) 
[DONE] Generowanie 3 opcji d³ugoœci zadañ - od 1 do 20 - od 1 do 100 (200) - mieszane, np. po³owa zadañ od 1 do 20, po³owa od 1 do 200, itd. 
[DONE] Generowanie d³ugoœci i iloœci przestojów (d³ugoœæ od 5 do 200) 
[DONE] Generowanie miejsc przestojów dla wszystkich maszyn 
* Eksport do pliku .txt 
[DONE] Optymalizacja generowanych wyników (limiter)
***************/

#include<iostream>
#include<fstream>			//do operacji na plikach
#include<time.h>			//do liczb losowych

#include "zadanie.h"		//do generowania danych
#include "maszyna.h"		//do generowania przestojów
#include "operacja.h"		//do sprawdzania poprawnoœci



/// Klasa generatora
class Generator
{
public:
	//TODO pola generatora
	int liczbaZadan;			//rozmiar instancji
	int dlugoscInstancji;		//d³ugoœæ wszystkich zadañ i przestojów
	vector<Zadanie*> zadania;	//wektor zawieraj¹cy wszystkie zadania
	vector<Maszyna*> maszyny;	//wektor zawieraj¹cy wszystkie maszyny


	//TODO konstruktory
	/********
	*	@Konstruktor
	*	@Argumenty
	*		int nZadan	-	liczba zadañ do wygenerowania
	********/
	Generator(int nZadan);


	//TODO destruktor


	//TODO metody


	/********
	*	@ generujZadanie
	*		Funkcja generuj¹ca d³ugoœci operacji poszczególnego zadania
	*	@Argumenty:	
	*		int minDlugosc	-	minimalna d³ugoœæ operacji
	*		int maxDlugosc	-	maksymalna d³ugoœæ operacji zadania
	*		int delay		-	minimalny czas przed wykonaniem pierwszej operacji zadania	(czas gotowoœci)
	*	@Zwraca:
	*		nic-------Zadanie	Result	-	objekt klasy	Zadanie	, zawieraj¹cy tablicê 3 podklas		Operacja	, z wygenerowanymi danymi
	*							spe³niaj¹cymi kryteria podane w argumentach funkcji
	*********/
	void generujZadanie(int minDlugosc, int maxDlugosc, int delay, int nrZad);


	/********
	*	@ generujMaszyne
	*		Funkcja generuj¹ca przestoje w maszynie
	*	@Argumenty:
	*		int nPrzestojowMin/Max	-	maksymalna/minimalna liczba przestojów w maszynie
	*		int czasPrzestojow		-	maksymalny czas trwania przestojów
	*	@Zwraca:
	*		Maszyna Result	-	objekt klasy	Maszyna	,	z tablicami		rozpoczecie i	dlugosc	z wygenerowanymi losowo danymi
	********/
	Maszyna generujMaszyne(int nPrzestojowMin, int nPrzestojowMax, int czasPrzestojow);


	/********
	*	@ czyWejdzie
	*		Funkcja sprawdzaj¹ca, czy operacja mo¿e zostaæ umieszczona w maszynie bez kolizji z przestojem maszyny
	*	@Argumenty:
	*		Maszyna maszyna			-	maszyna, na której sprawdzamy czy jest miejsce
	*		Operacja operacja		-	operacja, której poprawnoœæ sprawdzamy
	*	@Zwraca:
	*		bool	-	czy operacja mo¿e wejœæ na nastêpne miejsce bez kolizji z przestojem maszyny
	********/
	bool czyWejdzie(const Maszyna & maszyna, const Operacja & operacja) const;


	/********
	*	@ czyMozna
	*		Funkcja sprawdzaj¹ca, czy poprzednia operacja zadania zosta³a ju¿ ukoñczona i mo¿na spokojnie ju¿ dodaæ nastêpn¹ na dan¹ maszynê
	*	@Argumenty:
	*		Operacja operacja		-	operacja, której poprawnoœæ sprawdzamy
	*		Maszyna maszyna			-	maszyna na której sprawdzamy miejsce
	*	@Zwraca:
	*		bool	-	czy operacja mo¿e wejœæ bo poprzednia zosta³a ju¿ ukoñczona
	********/
	bool czyMozna(const Operacja & operacja, const Maszyna & maszyna) const;


	/**************
	*	@ dlugosc
	*		funkcja licz¹ca obecn¹ d³ugoœæ uszeregowania na danej maszynie
	*	@Argumenty
	*		Maszyna maszyna			-	maszyna na której liczymy obecn¹ d³ugoœæ uszeregowania
	*	@Zwraca
	*		int		-	d³ugoœæ uszeregowania
	**************/
	int dlugosc(const Maszyna & maszyna) const;


	/************
	*	@ getTime
	*		funkcja licz¹ca czas zakoñczenia siê operacji
	*	@Argumenty
	*		Operacja operacja		-	operacja, której czasu szukamy
	*	@Zwraca
	*		int		-	czas zakoñczenia siê operacja
	**************/
	int getTime(const Operacja & operacja) const;


	/********
	*	@ czysc
	*		Funkcja usuwaj¹ca czas oczekiwania z koñca uszeregowania
	*	@Argumenty:
	*		Maszyna maszyna			-	maszyna na której usuwamy œmieci
	*	@Zwraca:
	*		nic
	********/
	void czysc(Maszyna & maszyna) const;

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