#include "generator.h"


Generator::Generator(int nZadan)
{
	this->liczbaZadan = nZadan;
	this->dlugoscInstancji = 0;

}



void Generator::generujZadanie(int minDlugosc, int maxDlugosc, int delay, int nrZad)
{
	Zadanie* Result = new Zadanie();
	this->zadania.push_back(Result);
	Result->delay = random(0,delay);
	Result->operacje[0] = new Operacja(random(minDlugosc, maxDlugosc), 0, Result, nrZad);
	Result->operacje[1] = new Operacja(random(minDlugosc, maxDlugosc), 1, Result, nrZad);
	Result->operacje[2] = new Operacja(random(minDlugosc, maxDlugosc), 2, Result, nrZad);
	
	//return Result;
}


Maszyna Generator::generujMaszyne(int nPrzestojowMin,int nPrzestojowMax, int czasPrzestojow)
{
	int numer = this->maszyny.size();
	Maszyna* Result = new Maszyna(numer);
	this->maszyny.push_back(Result);
	Result->nPrzestojow = random(nPrzestojowMin, nPrzestojowMax);
	for (int i = 0; i < Result->nPrzestojow; ++i)
	{
		Result->dlugosc.push_back(random(5,czasPrzestojow));
	}
	//oszacowanie d�ugo�ci instancji
	for(int i = 0; i<this->liczbaZadan; ++i)
	{
		for(int j=0; j<3; ++j)
			(this->dlugoscInstancji) += this->zadania[i]->operacje[j]->czas;
	}
	/*for(int j = 0; j < Result->dlugosc.size(); ++j)
			this->dlugoscInstancji += Result->dlugosc[j];*/

	int przedzial = (this->dlugoscInstancji/3)/Result->nPrzestojow;			//d�ugo�� na jednej maszynie podzielona przez ilo�� przestoj�w
	for(int i = 1; i<=Result->nPrzestojow; ++i)
	{
		Result->rozpoczecie.push_back(i*przedzial);
	}
	return *Result;
}



bool Generator::czyWejdzie(const Maszyna & maszyna, const Operacja & operacja, int czas) const
{
	bool flag = true;		//wynik
	//obliczanie obecnej d�ugo�ci uszeregowania
	int rozmiar = czas;
	//this->dlugosc(maszyna);
	//sprawdzenie
	for( int i = 0; i<maszyna.rozpoczecie.size(); ++i)
	{
		if(maszyna.rozpoczecie[i] < rozmiar && (maszyna.rozpoczecie[i]+maszyna.dlugosc[i] > rozmiar+operacja.czas) ||
			maszyna.rozpoczecie[i] > rozmiar && (maszyna.rozpoczecie[i]+maszyna.dlugosc[i] < rozmiar+operacja.czas))
			flag = false;
	}
	return flag;
}


bool Generator::czyMozna(const Operacja & operacja, const Maszyna & maszyna) const
{
	bool flag = true;
	if(operacja.numer == 0) return flag;
	if(this->getTime(*operacja.parent->operacje[operacja.numer-1])-operacja.czas > this->dlugosc(maszyna))
		flag = false;

	return flag;
}


int Generator::dlugosc(const Maszyna & maszyna) const
{
	int result = 0;				//liczenie czasu, wska�nik na obecny jego kwant
	int j = 0;					//iterowanie przestoj�w
	int delay;					//ile pozosta�o czasu gotowo�ci dla danego zadania

	//dodawanie d�ugo�ci operacji
	for(int i = 0; i < maszyna.uszeregowanie.size(); ++i)
	{
		if(maszyna.uszeregowanie[i]->numer == 0)					//dodawanie czasu gotowo�ci
		{
			delay = maszyna.uszeregowanie[i]->parent->delay - result;
			if(delay > 0)
				result += delay;
		}
		
		//dodawanie czas�w przestoj�w
		if( maszyna.rozpoczecie[j] > result							//je�eli pierwszy niewykonany przest�j zaczyna si� za chwil�
			&& (maszyna.rozpoczecie[j]+maszyna.dlugosc[j] < result+maszyna.uszeregowanie[i]->czas))	//oraz ko�czy si� przed wykonaniem obecnej operacji
		{													
			result += maszyna.dlugosc[j];			//dodajemy ten przest�j oraz
			if(j<maszyna.rozpoczecie.size()-1)		//przechodzimy na nast�pny przest�j je�eli jaki� zosta�
				++j;
		}
		
		//dodawanie czasu operacji
		if(this->czyWejdzie(maszyna,*maszyna.uszeregowanie[i],result))
			result += maszyna.uszeregowanie[i]->czas;		//operacja nie zawadza o przest�j
		else
			result += maszyna.uszeregowanie[i]->czas*1.3;	//je�eli zawadza to dodajemy jej d�ugo�� z kar�
	}
		
	return result;
}


int Generator::getTime(const Operacja & operacja) const
{
	int rozmiar = 0, i = 0, j = 0, delay;
	Maszyna* maszyna = operacja.maszyna;
	//for(int i = 0; i<maszyna.uszeregowanie.size(); ++i)
	while(maszyna->uszeregowanie[i] != &operacja)
	{
		if(maszyna->uszeregowanie[i]->numer == 0)	
		{
			delay = maszyna->uszeregowanie[i]->parent->delay - rozmiar;
			if(delay > 0)
				rozmiar += delay;
		}
		rozmiar += maszyna->uszeregowanie[i]->czas;
		++i;
	}
	while(rozmiar > maszyna->rozpoczecie[j] && j<maszyna->rozpoczecie.size()-1)
	{
		rozmiar += maszyna->dlugosc[j];
		++j;
	}
	rozmiar += operacja.czas;
	return rozmiar;
}


void Generator::czysc(Maszyna & maszyna) const
{
	int i = maszyna.uszeregowanie.size()-1;
	while( maszyna.uszeregowanie[i])
	{
		if(maszyna.uszeregowanie[i]->numer > 2)
			maszyna.uszeregowanie.pop_back();
		else
			break;
		i--;
	}
}


void Generator::zlacz(vector<Operacja*> & uszeregowanie) const
{
	
	vector<Operacja*>::iterator it = uszeregowanie.end()-2;
	vector<Operacja*>::iterator prev = it+1;


	for (int i = uszeregowanie.size()-2; i>=0; --i)
	{
		if(uszeregowanie[i]->numer > 2)
			if(uszeregowanie[i+1]->numer > 2)
			{
				uszeregowanie[i]->czas ++;//= uszeregowanie[i+1]->czas;
				it = uszeregowanie.end()-i;
				uszeregowanie.erase(it);
			}
	}

	/*for(it;	it != uszeregowanie.begin(); it)
	//while(it != uszeregowanie.end())
	{
		prev = it-1;
		if((*it)->numer>2)
		{
			if((*prev)->numer>2)
			{
				(*it)->czas+=(*prev)->czas;

				uszeregowanie.erase(prev);
			}
		}
		else
		++it;
	}*/
}



int random(int min, int max)
{
	int result, lower = max-min;
	if(max == 0) return 0;
	result = rand()%lower + min;
	return result;
}