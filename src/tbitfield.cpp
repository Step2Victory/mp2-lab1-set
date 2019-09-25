// ННГУ, ВМК, Курс "Методы программирования-2", С++, ООП
//
// tbitfield.cpp - Copyright (c) Гергель В.П. 07.05.2001
//   Переработано для Microsoft Visual Studio 2008 Сысоевым А.В. (19.04.2015)
//
// Битовое поле

#include "tbitfield.h"

TBitField::TBitField(int len)
{
	if (len < 0)
		throw 1;
	MemLen = (len - 1) / BitSize + 1;
	pMem = new TELEM[MemLen];
	BitLen = len;
	for (int i = 0; i < MemLen; ++i)
		pMem[i] = 0;
}

TBitField::TBitField(const TBitField &bf) // конструктор копирования
{
	pMem = new TELEM[bf.MemLen];
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	for (int i = 0; i < bf.MemLen; ++i)
		pMem[i] = bf.pMem[i];

}

TBitField::~TBitField()
{
	delete[] pMem;
}

int TBitField::GetMemIndex(const int n) const // индекс Мем для бита n
{
	if (n >= BitLen || n < 0)
		throw 1;
	else
		return n / BitSize;
}

TELEM TBitField::GetMemMask(const int n) const // битовая маска для бита n
{
	return 1 << (n % BitSize);
}

// доступ к битам битового поля

int TBitField::GetLength(void) const // получить длину (к-во битов)
{
	return BitLen;
}

void TBitField::SetBit(const int n) // установить бит
{
	if (n >= BitLen || n < 0)
		throw 1;
	int k = n / BitSize;
	pMem[k] = pMem[k] | GetMemMask(n);
}

void TBitField::ClrBit(const int n) // очистить бит
{
	if (n >= BitLen || n < 0)
		throw 1;
	int k = n / BitSize;
	pMem[k] = pMem[k] & (~GetMemMask(n));
}

int TBitField::GetBit(const int n) const // получить значение бита
{
	if (n >= BitLen || n < 0)
		throw 1;
	int k = n / BitSize;
	if (pMem[k] & GetMemMask(n))
		return 1;
	return 0;
}

// битовые операции

TBitField& TBitField::operator=(const TBitField &bf) // присваивание
{
	if (bf == *this)
		return *this;
	MemLen = bf.MemLen;
	BitLen = bf.BitLen;
	delete[] pMem;
	pMem = new TELEM[MemLen];
	for (int i = 0; i < MemLen; ++i)
		pMem[i] = bf.pMem[i];
	return *this;

}

int TBitField::operator==(const TBitField &bf) const // сравнение
{
	if (BitLen == bf.BitLen)
	{
		for (int i = 0; i < MemLen; ++i)
			if (pMem[i] != bf.pMem[i])
				return 0;
		return 1;
	}
	return 0;
}

int TBitField::operator!=(const TBitField &bf) const // сравнение
{
	if (bf == *this)
		return 0;
	return 1;
}

TBitField TBitField::operator|(const TBitField &bf) // операция "или"
{
	TBitField ans(BitLen > bf.BitLen ? *this : bf);
	int n = (MemLen < bf.MemLen ? MemLen : bf.MemLen);
	for (int i = 0; i < n; ++i)
		ans.pMem[i] = pMem[i] | bf.pMem[i];
	return ans;
}

TBitField TBitField::operator&(const TBitField &bf) // операция "и"
{
	int n;
	TBitField ans(BitLen > bf.BitLen ? *this : bf);
	if (bf.MemLen > MemLen)
		n = MemLen;
	else
		n = bf.MemLen;
	for (int i = 0; i < n; ++i)
		ans.pMem[i] = pMem[i] & bf.pMem[i];
	return ans;

}

TBitField TBitField::operator~(void) // отрицание
{
	int n = MemLen;
	for (int i = 0; i < n; ++i)
		pMem[i] = ~pMem[i];
	pMem[n - 1] = (pMem[n - 1] << BitSize - (BitLen % BitSize)) >> BitSize - (BitLen % BitSize);
	return *this;
}

// ввод/вывод

istream &operator>>(istream &istr, TBitField &bf) // ввод
{
	return istr;
}

ostream &operator<<(ostream &ostr, const TBitField &bf) // вывод
{
	return ostr;
}
