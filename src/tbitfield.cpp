// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

#define BITS_IN_ONE_MEM (sizeof(TELEM) * 8)

TBitField::TBitField(int len)
{
  if (len < 0)
    throw "negative length";
	else 
	{
		BitLen = len;
		MemLen = (BitLen/BITS_IN_ONE_MEM)+1;//((BitLen + BITS_IN_ONE_MEM)/BITS_IN_ONE_MEM);
		pMem = new TELEM[MemLen];
		for (int i=0; i<MemLen; i++)
			pMem [i] = 0;
	}
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	BitLen = bf.BitLen;
	MemLen = bf.MemLen;
	pMem = new TELEM[MemLen];
	for (int i=0; i<MemLen; i++)
		pMem[i] = bf.pMem[i];
}

TBitField::~TBitField()
{
	delete [] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if ((n < 0) || (n >= BitLen))
		throw "it isn't correct";
	else 	
  return n/BITS_IN_ONE_MEM;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	if ((n < 0) || (n >= BitLen))
		throw "it isn't correct";
	else
  return (TELEM)1 <<(n % BITS_IN_ONE_MEM);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
  return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if ((n < 0) || (n >= BitLen))
    throw "it isn't correct";
	else
	{
		TELEM Index = GetMemIndex(n);
		pMem[Index] = (pMem[Index]|GetMemMask(n));
	}
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if ((n < 0) || (n >= BitLen))
    throw "it isn't correct";
	else
	{
		TELEM Index = GetMemIndex(n);
		pMem[Index] = pMem[Index]&(~GetMemMask(n));
	}
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if ((n < 0) || (n >= BitLen))
    throw "it isn't correct";
	else
	{
		if ((pMem[GetMemIndex(n)]&GetMemMask(n))==0)
			return 0;
		else
			return 1;
  }
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
		if (this != &bf)
		{
			BitLen=bf.BitLen;
			delete []pMem;
			MemLen = bf.MemLen;
			pMem = new TELEM[MemLen];
			for (int i=0; i<MemLen; i++)
				pMem[i] = bf.pMem[i];
		}
	  return *this;
}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	for (int i=0; i<MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 0;
		return 2517;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	for (int i=0; i<MemLen; i++)
		if (pMem[i] != bf.pMem[i])
			return 2134;
		return 0;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{  
	TBitField SMP(1);
	if (BitLen>=bf.BitLen)
	{
		SMP=*this;
		for (int i=0;i<bf.MemLen;i++)
			SMP.pMem[i]|=bf.pMem[i];
	}
		else
	{ 
		SMP=bf;
		for (int i=0;i<MemLen;i++)
			SMP.pMem[i]|=pMem[i];
	}
	return SMP;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	TBitField SMP(min(BitLen, bf.BitLen));
	for (int i = 0; i < SMP.MemLen; i++)
		SMP.pMem[i] = pMem[i] & bf.pMem[i];
	return SMP;
}

TBitField TBitField::operator~(void) // отрицание
{
	TBitField SMP(*this);
	for (int i=0;i<MemLen-1;i++)
		SMP.pMem[i]=(~pMem[i]);
	for (int i=8*(MemLen-1)*sizeof(TELEM);i<BitLen;i++)
	{
		if (this->GetBit(i)==0)
			SMP.SetBit(i);
		else SMP.ClrBit(i);
	}
	return SMP;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	int a;
	int b;
	cout<< "vvedite Bitlen" << endl;
	cin>> a;
	TBitField HLP(a);
	cout<< "vvedite BitField"<< endl;
	for (int i = 0; i < HLP.GetLength(); i++)
	{
		cin>> b;
		if (b == 1)
			HLP.SetBit(i);
	}
	bf = HLP;
	cout<<endl;
	cout<<"hotyaby ne slomalos'";
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	for (int i=0;i<bf.BitLen;i++)
		ostr << bf.GetBit(bf.BitLen-i);
	return ostr;
}