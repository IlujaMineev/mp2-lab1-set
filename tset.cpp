// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower=mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.BitField)
{
	MaxPower=s.MaxPower;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(bf)
{
	MaxPower=bf.GetLength();
}

TSet::operator TBitField()
{
	return BitField;
}

int TSet::GetMaxPower(void) const // получить макс. к-во эл-тов
{
	return MaxPower;
}

int TSet::IsMember(const int Elem) const // элемент множества?
{
	if ((Elem < MaxPower)&&(Elem >= 0))
		return BitField.GetBit(Elem);
	else 
		throw "Negative Elem";
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	if ((Elem < MaxPower)&&(Elem >= 0))
		BitField.SetBit(Elem); 
	else 
		throw "isn't correct";
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	if ((Elem < MaxPower)&&(Elem>=0))
		BitField.ClrBit(Elem); 
	else 
		throw "isn't correct";
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	BitField=s.BitField;
	MaxPower=s.MaxPower;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (s.MaxPower == MaxPower)
		return (BitField==s.BitField);
	else
		return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	return !(*this == s);
}

TSet TSet::operator+(const TSet &s) // объединение
{
	TSet A(BitField|s.BitField );
	return A;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	TSet A(*this);
	A.InsElem(Elem);
	return A;
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	TSet A(*this);
	A.DelElem(Elem);
	return A;
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet A(BitField & s.BitField);
	return A;
}

TSet TSet::operator~(void) // дополнение
{
	TSet A(~BitField);
	return A;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	istr>>s.BitField;
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	ostr<<s.BitField;
	return ostr;
}