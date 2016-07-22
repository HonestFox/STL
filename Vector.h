#pragma once

template<class T>
class Vector
{
	typedef T ValueType;
public:
	typedef ValueType* Iterator;
	typedef const ValueType* ConstIterator;
public:
	Vector()
		:_Start(0)
		,_Finish(0)
		,_EndOfStorage(0)
	{}

	~Vector()
	{
		delete [] _Start;
	}
public:
	Iterator Begin()
	{
		return _Start;
	}

	Iterator End()
	{
		return _Finish;
	}

	size_t Size()
	{
		return (_Finish - _Start);
	}

	size_t Capacity()
	{
		return _EndOfStorage - _Start;
	}

	bool empty() const
	{
		return (_Finish == _Start);		//_FInish == 0
	}

public:
	void PushBack(const T &x)
	{
		_CheckStorage();
		*_Finish = x;
		++_Finish;
	}

	void Insert(Iterator pos, const T &x)	//在pos的前面
	{
		_CheckStorage();
		Iterator tmp = _Finish - 1;
		while (pos != (tmp + 1) )
		{
			*(tmp + 1) = *(tmp);
			--tmp;
		}
		*pos = x;
		++_Finish;
	}

	T& operator[](size_t n)
	{
		return *(_Start + n);
	}

protected:
	void _CheckStorage()
	{
		if (_Finish == _EndOfStorage)
		{
			size_t size = Size();
			T *tmp = new T[size * 2 + 1];
			for (size_t i = 0; i < size; ++i)
			{
				*(tmp + i) = *(_Start + i);
			}
			_Finish = tmp + size;
			_EndOfStorage = tmp + size * 2 + 1;
			if (_Start != NULL)
			{
				delete[] _Start;
			}
			_Start = tmp;
		}
	}

protected:
	Iterator _Start;
	Iterator _Finish;
	Iterator _EndOfStorage;
};
