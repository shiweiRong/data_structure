//vector.h
#ifndef VECTOR_H
#define VECTOR_H

#include "light.h"
#include <iostream>
using namespace std;

#define DEFAULT_CAPACITY  3

template <typename T> class Vector
{
private:
	T size; T capacity; Light<T> *elem;

protected:
	bool isEmpty() const;
	void expand();//扩容
	void merge(T lo, T mi, T hi);

public:
	Vector();//构造函数
	void add(const T posi, const T height);//增加元素
	void display()const;
	T getSize()const{return size;};
	void mergeSort(T lo, T hi);
	T invInside(T lo, T hi);
	T invBetween(T lo, T mi,T hi);

};

template <typename T> Vector<T>::Vector()
{
	size = 0;
	capacity = DEFAULT_CAPACITY;
	elem = new Light<T>[capacity];
	for (T i=0;i<capacity;i++)
	{
		elem[i].height = 0;
		elem[i].posi = 0;
	}
}
template <typename T> void Vector<T>::add(const T p, const T h)
{
	expand();
	elem[size].height = h;elem[size].posi = p;
	size++;	
}
template <typename T> bool Vector<T>::isEmpty()const
{
	return size == 0 ? true:false;
}
template <typename T>  void Vector<T>::expand()
{
	if(size < capacity) return;
	Light<T> *oldElem = elem; elem = new Light<T>[capacity <<= 1];//容量加倍
	for(T i=0;i<size;i++)
	{
		elem[i] = oldElem[i];
	}
	delete [] oldElem;
}
template <typename T>  void Vector<T>::display()const
{
	if(isEmpty())
	{
		cout<<"序列为空"<<endl;
		return;
	}
	for (T i=0;i<size;i++)
	{
		cout<<"第"<<i+1<<"元素:("<<elem[i].posi<<", "<<elem[i].height<<")"<<endl;
	}
}

template <typename T> void Vector<T>::mergeSort(T lo, T hi)
{
	if ( hi - lo < 2 ) return; 
    T mi = ( lo + hi ) / 2; 
    mergeSort(lo,mi);mergeSort(mi,hi);
	merge(lo,mi,hi);
}
template <typename T> void Vector<T>::merge(T lo, T mi, T hi)
{
	Light<T> *A = elem + lo;
	T lb = mi - lo; Light<T> *B = new Light<T> [lb];
	for(T i=0;i<lb;i++) B[i] = A[i];//前子向量B
	int lc = hi - mi; Light<T> *C = elem + mi;//后子向量C
	for(T i=0,j=0,k=0;j<lb;)
	{
		if((lc <= k) || (B[j].posi <= C[k].posi))
			A[i++] = B[j++];
		if((k < lc) && (C[k].posi < B[j].posi))
			A[i++] = C[k++];
	}
	delete []B;
}

template <typename T>  T Vector<T>::invInside(T lo, T hi)
{
	if (hi - lo < 2) return 0;
	T mi = (lo + hi)/2;
	T invL = invInside(lo,mi);T invR = invInside(mi,hi);
	T invB = invBetween(lo,mi,hi);
	return invL + invR + invB;
}
template <typename T>  T Vector<T>::invBetween(T lo, T mi, T hi)
{
	//cout<<"invBetween is called "<<lo<<" "<<mi<<" "<<hi<<endl;

	Light<T> *A = elem + lo;
	T lb = mi - lo; Light<T> *B = new Light<T> [lb];
	for(T i=0;i<lb;i++) B[i] = A[i];//前子向量B
	T lc = hi - mi; Light<T> *C = elem + mi;//后子向量C
	
	T b=0;T *c =new T[lc];//*c用于存储每个C元素放入A序列的时候，A中已经存在的B元素的个数
	for ( T i = 0, j = 0, k = 0; (j<lb) || (k<lc);)
	{
		if ((j<lb) && (!(k<lc) || (B[j].height < C[k].height)))
		{
			//cout<<"add B ";
			A[i++] = B[j++];
			b++; 
			//cout<<"b = "<<b<<endl;
		}
		if ((k<lc) && (!(j<lb ) || (C[k].height <=  B[j].height)))
		{
			//cout<<"add C ";
			c[k] = b; 
			//cout<<"s = "<<s[k]<<endl;
			A[i++] = C[k++];
		}
	}
	T sum = 0;
	for (T k=0;k<lc;k++)
	{
		sum += c[k];
	}
	delete []B;delete []c;

	return sum;
}

#endif