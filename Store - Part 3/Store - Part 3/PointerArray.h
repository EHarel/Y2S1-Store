#ifndef __ARRAY_H
#define __ARRAY_H

#include "ValidationHelper.h"
#include <iostream>
using namespace std;

/* 
This is an ARRAY OF POINTERS to T.
The template receives class T, and creats an array of pointers to T.

Object T must support:
	-	<<
	-	Copy c'tor
*/


template<class T>
class PointerArray
{
private:
	T**				m_arr; 
	unsigned int	m_log_size, m_phy_size;
	char			m_delimiter;

public: // Constructors
					PointerArray(int size = 20, char delimiter = ' ');
					PointerArray(const PointerArray& other); // Copy c'tor
					PointerArray(PointerArray && other); // Move c'tor
					~PointerArray();

public:
	void			clear();
	bool			empty()		const { return m_log_size == 0; }
	unsigned int	size()		const { return m_log_size; }
	unsigned int	capacity()	const { return m_phy_size; }

	void			push_back(T&);
	const PointerArray&	operator=(const PointerArray& other); 
	const PointerArray&	operator+=(T& new_val);
	T*				operator[](int i);
	const T*		operator[](int i) const;
	friend ostream& operator<<(ostream& os, const PointerArray& arr)
	{
		for (unsigned int i = 0; i < arr.m_log_size; i++)
			os << typeid(T).name() + 6  << " number " << i + 1 << endl << endl << *(arr.m_arr[i]) << arr.m_delimiter;
		return os;
	}

	friend class System;
private:
	void CheckAndIncreaseIfNeeded();
};//Class



// ----------------- METHODS ----------------- //

template<class T>
PointerArray<T>::PointerArray(int user_size, char delimiter)
{
	int size;

	if (user_size <= 0)
		size = 10;
	else
		size = user_size;

	m_arr = new T*[size];
	m_phy_size = size;
	ValidationHelper::AllocationCheck<T**>(m_arr);

	m_delimiter = delimiter;
	m_log_size = 0;
	m_arr[0] = nullptr;
}

template<class T>
PointerArray<T>::PointerArray(const PointerArray & other) : m_arr(NULL)
{
	*this = other;
}

template<class T>
PointerArray<T>::PointerArray(PointerArray && other)
{
	m_log_size = other.m_log_size;
	m_phy_size = other.m_phy_size;
	m_delimiter = other.m_delimiter;
	m_arr = other.m_arr;
	other.m_arr = nullptr;
}

template<class T>
PointerArray<T>::~PointerArray()
{
	clear();
	delete[]m_arr;
}

template<class T>
void PointerArray<T>::clear() // This method deletes the elements, without releasing the array itself.
{
	for (unsigned int i = 0; i < m_log_size; i++)
	{
		delete m_arr[i];
	}

	m_log_size = 0; 
}

template<class T>
inline void PointerArray<T>::push_back(T & t)
{
	CheckAndIncreaseIfNeeded();
	m_arr[m_log_size++] = &t;
}

template<class T>
const PointerArray<T>& PointerArray<T>::operator=(const PointerArray<T> & other) 
{
	if (this != &other)
	{
		for (int i = 0; i < m_log_size; i++)
			delete m_arr[i];
		delete []m_arr;

		m_log_size = other.m_log_size;
		m_phy_size = other.m_phy_size;
		m_delimiter = other.m_delimiter;

		m_arr = new T*[m_phy_size];
		ValidationHelper::AllocationCheck<T**>(m_arr);

		for (int i = 0; i < m_log_size; i++)
		{
			m_arr[i] = new T(*(other.m_arr[i])); // Go through copy c'tor of T.
			ValidationHelper::AllocationCheck<T*>(m_arr[i]);
		}
	}
	return *this;
}


template<class T>
const PointerArray<T> & PointerArray<T>::operator+=(T & new_val)
{
	CheckAndIncreaseIfNeeded();
	m_arr[m_log_size++] = &new_val;
	return *this;
}

template<class T>
inline T * PointerArray<T>::operator[](int i)
{
	if (i<0 || i>(int)m_log_size)
		return nullptr;
	return m_arr[i];
}

template<class T>
inline const T * PointerArray<T>::operator[](int i) const
{
	if (i<0 || i>(int)m_log_size)
		return nullptr;
	return m_arr[i];
}

template<class T>
void PointerArray<T>::CheckAndIncreaseIfNeeded()
{
	if (m_log_size >= m_phy_size)
	{
		m_phy_size *= 2;
		T** temp = new T*[m_phy_size];
		ValidationHelper::AllocationCheck(temp);
		for (unsigned int i = 0; i < m_log_size; i++)
		{
			temp[i] = m_arr[i];
		}
		delete[] m_arr;
		m_arr = temp;
	}
}

#endif // !__ARRAY_H
