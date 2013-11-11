#ifndef GENERATOR_H
#define GENERATOR_H

/*
I. Generator 
[DONE] 1) Interfejs w konsoli 
[DONE] 2) Funkcja generuj¹ca liczby losowe 
3) Generowanie instancji problemu od 50 do n (iloœæ zadañ) 
4) Generowanie 3 opcji d³ugoœci zadañ - od 1 do 20 - od 1 do 100 (200) - mieszane, np. po³owa zadañ od 1 do 20, po³owa od 1 do 200, itd. 
5) Generowanie d³ugoœci i iloœci przestojów (d³ugoœæ od 5 do 200) 
6) Generowanie miejsc przestojów dla wszystkich maszyn 
7) Eksport do pliku .txt 
8) Optymalizacja generowanych wyników (limiter)
*/

#include "zadanie.h"


/// Klasa generatora
class Generator
{
	//TODO pola generatora
	int liczbaZadan;		//rozmiar instancji
	int liczbaPrzestojow;	//liczba przestojów
	int dlugoscZadan;		//opcja d³ugoœci zadañ
	int dlugosc przestojow;	//opcja d³ugoœci przestojów

public:
	//TODO metody
	void maszyna_losowanie(int liczba_przest, maszyna m1, maszyna m2, maszyna m3);
	void zadanie_losowanie(int liczba_zadan, int czas_wyk, zadanie gotowosc, zadanie op1, zadanie op2, zadanie op3);
}

#endif