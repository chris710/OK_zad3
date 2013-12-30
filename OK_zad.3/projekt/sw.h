#include<iostream>
#include "generator.h"


////////////////////////////////////////////////////////
///	PLIK NAG��WKOWY ALGORYTMU SYMULOWANEGO WY�ARZANIA///
////////////////////////////////////////////////////////
/******************************************************
*				PROJEKT/UWAGI/INFORMACJE
*	-(?) jakie s� niezb�dne elementy algorytmu
*	-(?) w jaki spos�b go zaimplementowa�
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
	-(?) czym jest "miejsce startowe"?
	-(?) w jaki spos�b wyznacza� s�siednie uszeregowania
*
*
******************************************************/
///////////////////////////////////////////////////////
/******************************************************
*						TODO LIST
*	-klasa wy�arzania(czy warto?)
*	-metody/procedury (kt�re potrzebne?)
		-sprawdzenie czy operacja pasuje w dane miejsce
*	-weryfikacja i pomiar czasu
*	-prezentacja wynik�w (kt�rymi parametrami badamy?)
*	-wyznaczenie maksymalnego czasu wy�arzania (wykres)
******************************************************/


