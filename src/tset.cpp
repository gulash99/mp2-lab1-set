// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tset.cpp - Copyright (c) Гергель В.П. 04.10.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Множество - реализация через битовые поля

#include "tset.h"

TSet::TSet(int mp) : BitField(mp)
{
	MaxPower = mp;
}

// конструктор копирования
TSet::TSet(const TSet &s) : BitField(s.MaxPower)
{
	MaxPower = s.MaxPower;
	BitField = s.BitField;
}

// конструктор преобразования типа
TSet::TSet(const TBitField &bf) : BitField(1)
{
	BitField = bf;
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
	return BitField.GetBit(Elem);
}

void TSet::InsElem(const int Elem) // включение элемента множества
{
	BitField.SetBit(Elem);
}

void TSet::DelElem(const int Elem) // исключение элемента множества
{
	BitField.ClrBit(Elem);
}

// теоретико-множественные операции

TSet& TSet::operator=(const TSet &s) // присваивание
{
	this->MaxPower = s.MaxPower;
	this->BitField = s.BitField;
	return *this;
}

int TSet::operator==(const TSet &s) const // сравнение
{
	if (this->MaxPower == s.MaxPower)
	{
		if (BitField == s.BitField)
			return 1;
		else
			return 0;
	}
	else
		return 0;
}

int TSet::operator!=(const TSet &s) const // сравнение
{
	if (this->MaxPower == s.MaxPower)
	{
		if (BitField == s.BitField)
			return 0;
		else
			return 1;
	}
	else
		return 1;
}

TSet TSet::operator+(const TSet &s) // объединение
{
	int tmp0;
	if (MaxPower > s.MaxPower)
		tmp0 = MaxPower;
	else
		tmp0 = s.MaxPower;
	TSet ts(s.MaxPower);
	ts.BitField = BitField | s.BitField;
	return ts;
}

TSet TSet::operator+(const int Elem) // объединение с элементом
{
	if (Elem > MaxPower)
		throw "Wrong data";
	else
	{
		TSet ts(MaxPower);
		BitField.SetBit(Elem);
		ts.BitField = BitField;
		return ts;
	}
}

TSet TSet::operator-(const int Elem) // разность с элементом
{
	if (Elem > MaxPower)
		throw "Индекс бита не положительный или превышает размер битового поля";
	else
	{
		TSet ts(MaxPower);
		BitField.ClrBit(Elem);
		ts.BitField = BitField;
		return ts;
	}
}

TSet TSet::operator*(const TSet &s) // пересечение
{
	TSet ts(s.MaxPower);
	ts.BitField = this->BitField & s.BitField;
	return ts;
}

TSet TSet::operator~(void) // дополнение
{
	BitField = ~BitField;
	return *this;
}

// перегрузка ввода/вывода

istream &operator>>(istream &istr, TSet &s) // ввод
{
	int n;
	for (int i = 0; i < s.MaxPower; i++) {
		istr >> n;
		s.InsElem(n);
	}
	return istr;
}

ostream& operator<<(ostream &ostr, const TSet &s) // вывод
{
	for (int i = 0; i < s.MaxPower; i++)
		if (s.BitField.GetBit(i) == 1)
			ostr << i << ' ';
	return ostr;
}
