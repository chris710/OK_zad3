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
		a) wybór losowego miejsca startowego (?)
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
			mniejsza ni¿ zadana
		g) je¿eli tak to losowo wybieramy czy zmieniæ
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
*	-weryfikacja i pomiar czasu
*	-prezentacja wyników (którymi parametrami badamy?)
*	-wyznaczenie maksymalnego czasu wy¿arzania (wykres)
******************************************************/


