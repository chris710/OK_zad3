#ifndef GENERATOR_H
#define GENERATOR_H

/*
I. Generator 
[DONE] 1) Interfejs w konsoli 
[DONE] 2) Funkcja generuj�ca liczby losowe 
3) Generowanie instancji problemu od 50 do n (ilo�� zada�) 
4) Generowanie 3 opcji d�ugo�ci zada� - od 1 do 20 - od 1 do 100 (200) - mieszane, np. po�owa zada� od 1 do 20, po�owa od 1 do 200, itd. 
5) Generowanie d�ugo�ci i ilo�ci przestoj�w (d�ugo�� od 5 do 200) 
6) Generowanie miejsc przestoj�w dla wszystkich maszyn 
7) Eksport do pliku .txt 
8) Optymalizacja generowanych wynik�w (limiter)
*/

#include "zadanie.h"


/// Klasa generatora
class Generator
{
	//TODO pola generatora
	int liczbaZadan;		//rozmiar instancji
	int liczbaPrzestojow;	//liczba przestoj�w
	int dlugoscZadan;		//opcja d�ugo�ci zada�
	int dlugosc przestojow;	//opcja d�ugo�ci przestoj�w

public:
	//TODO metody
	void maszyna_losowanie(int liczba_przest, maszyna m1, maszyna m2, maszyna m3);
	void zadanie_losowanie(int liczba_zadan, int czas_wyk, zadanie gotowosc, zadanie op1, zadanie op2, zadanie op3);
}

#endif